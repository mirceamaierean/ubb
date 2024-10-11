import sqlite3
from sqlite3 import Error
from domain.student import student
from repository.MemoryRepository import MemoryRepository

class DBRepository(MemoryRepository):
  # this class inherits from MemoryRepository
  # => has all the mathods and attributes in MemoryRepository
  def __init__(self, db_path = "/Users/mirceamaierean/a7-914maiereanmircea/students.sqlite"):
    """
    file_name: string
    """
    # call superclass constructor
    super(DBRepository, self).__init__()
    self._db_path = db_path
    self._stack = []
    self._connection = self._create_connection()
    
    self._create_table()

  def _create_connection(self):
    """
    Loads the students from the database
    """
    connection = None
    try:
        connection = sqlite3.connect(self._db_path)
    except Error as e:
        return e

    return connection

  def _execute_query(self, query):
    cursor = self._connection.cursor()
    try:
      cursor.execute(query)
      self._connection.commit()
    except Error as e:
        raise e(e)

  def _create_table(self):
    create_students_tabel = """
      CREATE TABLE IF NOT EXISTS students (
        id INTEGER PRIMARY KEY,
        name TEXT,
        gr INTEGER
      );
      """
    self._execute_query(create_students_tabel)  

  def _execute_read_query(self, query):
    cursor = self._connection.cursor()
    result = None
    try:
        cursor.execute(query)
        result = cursor.fetchall()
        return result

    except Error as e:
        print(f"The error '{e}' occurred")

  # We are overriding our initial function of adding
  def add(self, new_student: student, appnd: bool):
    """
    new_student: student
    appnd: bool
    """
    # call the add() method on the super class
    # we want to do everything the superclass add() already does
    
    check_existing_id = self._execute_read_query("SELECT * from students WHERE id=" + str(new_student.id))

    if len(check_existing_id) == 0:
      add_student = "INSERT INTO students (id, name, gr) VALUES (" + str(new_student.id) + ", '" + new_student.name + "', " + str(new_student.group) + ")"

      self._execute_query(add_student)
      delete_student = ["DELETE * from students WHERE id=" + str(new_student.id)]
      self._stack.append(delete_student)   

  def get_all(self):
    q = "SELECT * from students"
    select_students = self._execute_read_query(q)
    return select_students

  def filter(self, group: int):
    """
    group: int
    """
    undo_ops = []
    q = "SELECT * from students WHERE gr=" + str(group)
    select_students = self._execute_read_query(q)

    for stud in select_students:
      undo_ops.append("INSERT INTO students (id, name, gr) VALUES " + str(stud) + ")")

    select_students_query = "DELETE FROM students WHERE gr = " + str(group)
    self._execute_query(select_students_query)
    self._stack.append(undo_ops)
  
  def undo_last_operation(self):
    # save all the students in the binary file
    if len(self._stack) > 0:
      redo_ops = self._stack[-1]
      for op in redo_ops:
        print(op)
        self._execute_query(op)  
