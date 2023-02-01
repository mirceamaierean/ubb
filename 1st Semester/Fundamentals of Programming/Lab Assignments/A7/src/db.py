# EXAMPLE TO CONNECT A SQLITE DATABASE
# import sqlite3
# from sqlite3 import Error

# def create_connection(path):
#     connection = None
#     try:
#         connection = sqlite3.connect(path)
#         print("Connection to SQLite DB successful")
#     except Error as e:
#         print(f"The error '{e}' occurred")

#     return connection

# connection = create_connection("/Users/mirceamaierean/a7-914maiereanmircea/students.sqlite")

# def execute_query(connection, query):
#     cursor = connection.cursor()
#     try:
#         cursor.execute(query)
#         connection.commit()
#         print("Query executed successfully")
#     except Error as e:
#         print(f"The error '{e}' occurred")

# create_users_table = """
# CREATE TABLE IF NOT EXISTS studs (
#   id INTEGER PRIMARY KEY AUTOINCREMENT,
#   name TEXT NOT NULL,
#   gr INTEGER
# );
# """

# execute_query(connection, create_users_table)  

# # create_users = """
# # INSERT INTO
# #   users (name, age, gender, nationality)
# # VALUES
# #   ('James', 25, 'male', 'USA'),
# #   ('Leila', 32, 'female', 'France'),
# #   ('Brigitte', 35, 'female', 'England'),
# #   ('Mike', 40, 'male', 'Denmark'),
# #   ('Elizabeth', 21, 'female', 'Canada');
# # """

# # execute_query(connection, create_users)   

# # def execute_read_query(connection, query):
# #     cursor = connection.cursor()
# #     result = None
# #     try:
# #         cursor.execute(query)
# #         result = cursor.fetchall()
# #         return result
# #     except Error as e:
# #         print(f"The error '{e}' occurred")

# # select_users = "SELECT * from users WHERE name='James'"
# # users = execute_read_query(connection, select_users)

# # for user in users:
# #     print(str(user))

# drop_comment = "DROP TABLE studs"

# execute_query(connection, drop_comment)
