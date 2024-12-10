import json
import os
from domain.student import student
from repository.MemoryRepository import MemoryRepository

class JSONRepository(MemoryRepository):
  # this class inherits from MemoryRepository
  # => has all the mathods and attributes in MemoryRepository
  def __init__(self, file_name = "students.json"):
    # call superclass constructor
    super(JSONRepository, self).__init__()
    # remember the name of the file we're working with
    self._file_name = file_name
    # load the students from the file
    self._init_file()
    self._load_file()

  def reset_file(self):
    fout = open(self._file_name, "w")
    fout.write("{}")
    fout.close()

  def erase_data(self):
    super().erase_data()
    self.reset_file()

  def _init_file(self):
    filesize = os.path.getsize(self._file_name)
    if filesize == 0:
      self.reset_file()

  def _load_file(self):
    """
    Loads the students from a json file
    """
    data = {}

    try:
      # In order to read from a json file, we use open(file_name)
      fin = open(self._file_name)
      # each students HAS TO BE on its own line
      data = json.load(fin)
      # we have to close the file after we are done reading from it
      fin.close()
    except IOError:
      pass
    
    for stud in data:
      # We use strip to remove the white spaces before or after the word
      new_student = student(stud["_student__student_id"], stud["_student__student_name"], stud["_student__student_group"])
      # NOTE call super() so that we don't write the file we're reading from
      super().add(new_student, False)

  def _save_file(self):
    """
    Saves all students to our json file
    """
    # In order to print to a text file, we use wt
    students = []

    fout = open(self._file_name, "w")


    for stud in self.get_all():
      students.append(stud.__dict__)
    
    json.dump(students, fout, indent=1)
    
    # We close the file after we are done writing to it
    fout.close()
  # We are overriding our initial function of adding
  def add(self, new_student: student, appnd: bool):
    # call the add() method on the super class
    # we want to do everything the superclass add() already does
    super().add(new_student, appnd)
    # save all the students in the text file
    self._save_file()
  
  def filter(self, group: int):
    super().filter(group)
    # save all the students in the text file
    self._save_file()
  
  def undo_last_operation(self):
    super().undo_last_operation()
    # save all the students in the text file
    self._save_file()
