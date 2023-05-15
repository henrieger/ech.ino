from environment import *
from database import Table
from sqlite import SQLite
from serialcomms import Serial
from arduino import Arduino
from datetime import datetime
from time import sleep

def main():
    db = SQLite(DB_DIRNAME, DB_FILENAME)

    table_schema = {'tank_id': int, 'measurements': float, 'timestamp': float}
    table = Table(db, 'test_table', schema=table_schema)

    arduinos = []

    ser = Serial(USB_PORT, 9600)

    while True:
        arduino = Arduino(ser)
        if not arduino.read_id(): break
        arduinos.append(arduino)

    if len(arduinos) == 0:
        print('ERROR: No tanks connected', flush=True)
        quit()

    print('Tanks connected:', [a.tank_id for a in arduinos], flush=True)

    data = []
    for _ in range(10):
        Arduino.trigger_measurements(ser)
        for arduino in arduinos:
            arduino.request_data()
            data.extend([d.as_dict() for d in arduino.read_data()])
            print('Data:', data, flush=True)
            arduino.acknowledge()
        sleep(3)
    
    table.insert(data)

    res = [(reg[0], reg[1], datetime.fromtimestamp(reg[2])) for reg in table.select_all()]
    print(res, flush=True)

if __name__ == '__main__':
    main()
