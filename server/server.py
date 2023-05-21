from environment import *
from database import Table
from sqlite import SQLite
from serialcomms import Serial
from arduino import * 
from datetime import datetime
from time import sleep

def main():
    db = SQLite(DB_DIRNAME, DB_FILENAME)

    water_table_schema = {'tank_id': int, 'measurements': int, 'timestamp': datetime}
    water_table = Table(db, 'water', schema=water_table_schema, reflect=True)

    temperature_table_schema = {'tank_id': int, 'measurements': float, 'timestamp': datetime}
    temperature_table = Table(db, 'temperature', schema=temperature_table_schema, reflect=True)

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

    while True:
        water_data = []
        temperature_data = []
        Arduino.trigger_measurements(ser)
        for arduino in arduinos:
            arduino.request_data()
            data = arduino.read_data()

            arduino.acknowledge()

            water_data.extend([d.as_dict() for d in data if d.sensor == WATER])
            temperature_data.extend([d.as_dict() for d in data if d.sensor == TEMPERATURE])

        print('Water:', water_data, flush=True)
        print('Temperature:', temperature_data, flush=True)
    
        water_table.insert(water_data)
        temperature_table.insert(temperature_data)
        
        sleep(10)

    # res = [(reg[0], reg[1], datetime.fromtimestamp(reg[2])) for reg in water_table.select_all()]
    # print(res, flush=True)

    # res = [(reg[0], reg[1], datetime.fromtimestamp(reg[2])) for reg in temperature_table.select_all()]
    # print(res, flush=True)

if __name__ == '__main__':
    main()
