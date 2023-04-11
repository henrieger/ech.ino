from comms import *
from datetime import datetime

import struct

class Datum:
    def __init__(self, info: bytearray, measurement_type: str):
        if len(info) != 6:
            print(len(info))
            raise Exception('Invalid info bytearray')

        print(info[2:6] ,len(info[2:6]))
        self.tank_id = int.from_bytes(info[0:2], 'little')
        [self.measurement] = struct.unpack(measurement_type, info[2:6])

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
    def __init__(self, comms: Comms, tank_id: int):
        self.comms = comms
        self.tank_id = tank_id

    def read_data(self, measurement_type: str) -> Datum:
        byte_info = self.comms.read()
        datum = Datum(byte_info, measurement_type)
        datum.mark_as_now()
        return datum

    def trigger_measurement(self):
        self.comms.write(TRIGGER)
