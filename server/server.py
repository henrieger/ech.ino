from environment import *
from database import Table
from sqlite import SQLite
from serialcomms import Serial
from arduino import Arduino
from datetime import datetime

def main():
    db = SQLite(DB_DIRNAME, DB_FILENAME)

    table_schema = {'tank_id': int, 'measurements': float, 'timestamp': float}
    table = Table(db, 'test_table', schema=table_schema)

    ser = Serial(USB_PORT, 9600)
    tank_id = int.from_bytes(ser.read()[0:1], 'big')
    arduino = Arduino(ser, tank_id)

    data = []
    for _ in range(10):
        arduino.trigger_measurement()
        data.append(arduino.read_data('f').as_dict())
    
    #data = [
    #        {'tank_id': 1, 'measurements': 65.54, 'timestamp': now},
    #        {'tank_id': 1, 'measurements': 20, 'timestamp': now},
    #        {'tank_id': 2, 'measurements': 34.98, 'timestamp': now}
    #       ]

    table.insert(data)

    res = [(reg[0], reg[1], datetime.fromtimestamp(reg[2])) for reg in table.select_all()]
    print(res)

if __name__ == '__main__':
    main()
