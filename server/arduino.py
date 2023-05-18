from comms import *
from datetime import datetime

import struct

# Sensor types
WATER = 0
TEMPERATURE = 1
LIGHT = 2
PH = 3
OXYGEN = 4

class Datum:
    def __init__(self, tank_id: int, info: bytearray):
        if len(info) != 6:
            print(len(info))
            raise Exception('Invalid info bytearray')

        # Get measurement type
        if info[0] & 0xff >= 0x80:
            measurement_type = '>f'
        else:
            measurement_type = '>i'

        header = bytearray(info[0:2])
        header[0] = header[0] & 0x7f

        self.tank_id = tank_id

        self.sensor = int.from_bytes(header, 'big')
        [self.measurement] = struct.unpack_from(measurement_type, info, 2)

    def mark_with_timestamp(self, timestamp: int):
        self.datetime = datetime.fromtimestamp(timestamp)

    def mark_as_now(self):
        self.datetime = datetime.now()

    def as_tuple(self) -> tuple:
        return (self.tank_id, self.measurement, self.datetime.timestamp())

    def as_dict(self) -> dict:
        return {
                'tank_id': self.tank_id,
                'measurement': self.measurement,
                'timestamp': self.datetime.timestamp()
               }

class Arduino:
    def __init__(self, comms: Comms, tank_id=0):
        self.comms = comms
        self.tank_id = tank_id


    def read_id(self) -> bool:
        data = self.comms.read(timeout=5)
        if data is None: return False

        self.tank_id = int.from_bytes(data, 'big')
        return True

    def read_data(self) -> list:
        byte_info = self.comms.read()
        if int.from_bytes(byte_info[0:2], 'big') != self.tank_id:
            return None

        print(byte_info)
        packets = [byte_info[i:i+6] for i in range(2, len(byte_info), 6)]
        print(packets)

        data = []
        for packet in packets:
            datum = Datum(self.tank_id, packet)
            datum.mark_as_now()
            data.append(datum)

        return data

    @staticmethod
    def trigger_measurements(comms: Comms):
        comms.write(TRIGGER)

    def request_data(self):
        data = bytearray(DATA_REQUEST) 
        data.extend(self.tank_id.to_bytes(2, 'big'))
        self.comms.write(data)

    def acknowledge(self):
        ack_msg = bytearray(b'AK')
        ack_msg.extend(self.tank_id.to_bytes(2, 'big'))
        self.comms.write(ack_msg)
