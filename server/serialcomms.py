from comms import *
import serial

class Serial(Comms):
    def __init__(self, port: str, baudrate: int):
        self.port = port
        self.baudrate = baudrate
        self.serial = serial.Serial(port, baudrate)

    def read(self) -> bytearray:
        recv_bytes = []

        while True:
            c = self.serial.read(1)
            if c == INIT_MARKER:
                c = self.serial.read(1)
                while c != INIT_MARKER and c != END_MARKER:
                    recv_bytes.append(c)
                    c = self.serial.read(1)
                if c == INIT_MARKER:
                    recv_bytes.clear()
                    continue
                if c == END_MARKER:
                    break
        
        return b''.join(recv_bytes)

    def write(self, data: bytearray):
        self.serial.write(data)
        self.serial.flush()

    def close(self):
        self.serial.close()
