from environment import *
from database import Table
from sqlite import SQLite
from datetime import datetime

def main():
    db = SQLite(DB_DIRNAME, DB_FILENAME)

    table_schema = {'tank_id': int, 'measurements': float, 'timestamp': float}
    table = Table(db, 'test_table', schema=table_schema)

    now = datetime.now().timestamp()
    data = [
            {'tank_id': 1, 'measurements': 65.54, 'timestamp': now},
            {'tank_id': 1, 'measurements': 20, 'timestamp': now},
            {'tank_id': 2, 'measurements': 34.98, 'timestamp': now}
           ]

    table.insert(data)

    res = [(reg[0], reg[1], datetime.fromtimestamp(reg[2])) for reg in table.select_all().fetchall()]
    print(res)

if __name__ == '__main__':
    main()
