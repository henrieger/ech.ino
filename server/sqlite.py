from database import *
import sqlite3

def py2sqlitetype(t):
    if t == int:
        return 'INTEGER'
    if t == float:
        return 'REAL'
    if t == str:
        return 'TEXT'
    if t == None:
        return 'NULL'
    return 'BLOB'

def sqlite2pytype(t: str):
    if t == 'INTEGER':
        return int
    if t == 'REAL':
        return float
    if t == 'TEXT':
        return str
    if t == 'NULL':
        return None
    if t == 'BLOB':
        return object
    return False

class SQLite(Database):
    '''Create a new SQLite object and connect to database'''
    def __init__(self, dirname, filename):
        self.connection = sqlite3.connect(dirname+filename)
        
    '''Execute a CREATE OR REPLACE TABLE statement'''
    def create_or_replace(self, table: str, schema: dict, pk=None):
        schema_str = ", ".join((f"{cname} {py2sqlitetype(ctype)} {' PRIMARY KEY' if cname == pk else ''}" for cname, ctype in schema.items()))
        create_str = f"CREATE TABLE IF NOT EXISTS {table}({schema_str})"
        return self.connection.execute(create_str)

    '''Execute a DROP TABLE IF EXISTS statement'''
    def drop_if_exists(self, table: str):
        return self.connection.execute(f"DROP TABLE IF EXISTS {table}")

    '''Execute a SELECT statement'''
    def select(self, table: str, columns: list, where=None):
        select_str = f"SELECT {', '.join(columns)} FROM {table}"
        return self.connection.execute(select_str).fetchall()

    '''Execute an INSERT statement'''
    def insert(self, table: str, data: list):
        insert_str = f"INSERT INTO {table} VALUES (:{', :'.join(data[0].keys())})"
        self.connection.executemany(insert_str, data)
        return self.connection.commit()
    
    '''Check if table exists'''
    def table_exists(self, table: str):
        try:
            data = self.select(table, ['*'])
        except sqlite3.OperationalError:
            return False
        return len(data) > 0

    '''Get list of columns from table'''
    def get_columns(self, table: str):
       pragma_str = f"PRAGMA table_info({table});"
       data = self.connection.execute(pragma_str).fetchall()
       return {d[1]: sqlite2pytype(d[2]) for d in data}
