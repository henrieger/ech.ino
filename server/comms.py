TRIGGER = b'T'
INIT_MARKER = b'<'
END_MARKER = b'>'

class Comms:
    def __init__(self):
        pass

    def read(self) -> bytearray:
        pass

    def write(self, data: bytearray):
        pass

    def close(self):
        pass
