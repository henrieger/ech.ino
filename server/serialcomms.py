from comms import *
import serial

class Serial(Comms):
    def __init__(self, port: str, baudrate: int, timeout: int):
        self.port = port
        self.baudrate = baudrate
        self.serial = serial.Serial(port, baudrate)
        self.timeout = timeout

    def read(self, timeout=None) -> bytearray:
        buf = None
    
        if timeout:
            self.serial.timeout = timeout

        while True:
            buf = self.serial.read(4)

            if timeout is not None and len(buf) != 4: return None 

            if buf == bytes(INIT_MARKER):
                buf = self.serial.read_until(END_MARKER)[:-4]
                print('Recv:', buf, flush=True)
                self.serial.timeout = None

                if INIT_MARKER in buf: return None
                return buf

    def write(self, data: bytearray):
        print('Sent:', INIT_MARKER + data + END_MARKER, flush=True)
        self.serial.write(INIT_MARKER + data + END_MARKER)
        self.serial.flush()

    def close(self):
        self.serial.close()
