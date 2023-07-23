class Database:
    '''Execute a CREATE OR REPLACE TABLE statement'''
    def create_or_replace(self, table: str, schema: dict, pk=None):
        pass

    '''Execute a DROP TABLE IF EXISTS statement'''
    def drop_if_exists(self, table: str):
        pass

    '''Execute a SELECT statement'''
    def select(self, table: str, columns: list, where=None):
        pass

    '''Execute an INSERT statement'''
    def insert(self, table: str, data: list):
        pass

    '''Check if table exists'''
    def table_exists(self, table: str):
        pass

    '''Get list of columns from table'''
    def get_columns(self, table: str):
        pass

class Table:
    '''Create new Table object'''
    def __init__(self, db: Database, name: str, reflect=False, schema=None):
        self.db = db
        self.name = name
        
        if reflect and db.table_exists(name):
            self.columns = self.db.get_columns(name)
            return

        self.columns = list(schema.keys())
        db.drop_if_exists(name)
        db.create_or_replace(name, schema)

    ''' Insert data into table'''
    def insert(self, data: list):
        if data and len(data) > 0:
            return self.db.insert(self.name, data)

    '''Retrieve all data from table'''
    def select_all(self):
        return self.db.select(self.name, self.columns)
