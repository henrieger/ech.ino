TRIGGER = b'T'
DATA_REQUEST = b'DR'
INIT_MARKER = bytearray.fromhex('00ff00ff')
END_MARKER = bytearray.fromhex('ff00ff00')

class Comms:
    def __init__(self):
        pass

    def read(self) -> bytearray:
        pass

    def write(self, data: bytearray):
        pass

    def close(self):
        pass
