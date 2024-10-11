from domain.student import student
from repository.MemoryRepository import MemoryRepository

class TextFileRepository(MemoryRepository):
  # this class inherits from MemoryRepository
  # => has all the mathods and attributes in MemoryRepository
  def __init__(self, file_name = "students.txt"):
    # call superclass constructor
    super(TextFileRepository, self).__init__()
    # remember the name of the file we're working with
    self._file_name = file_name
    # load the students from the file
    self._load_file()

  def erase_data(self):
    super().erase_data()
    open(self._file_name, "w").close()

  def _load_file(self):
    """
    Loads the students from a text file
    """
    lines = []

    try:
      # In order to read from a text file, we use rt
      fin = open(self._file_name, "rt")
      # each students HAS TO BE on its own line
      lines = fin.readlines()
      # we have to close the file after we are done reading from it
      fin.close()
    except IOError:
      pass

    for line in lines:
      current_line = line.split(",")
      # current_line: student_id, student_name, student_group
      # We use strip to remove the white spaces before or after the word
      new_student = student(int(current_line[0].strip()), current_line[1].strip(), int(current_line[2].strip()))
      # NOTE call super() so that we don't write the file we're reading from
      super().add(new_student, False)

  def _save_file(self):
    """
    Saves all students to our text file
    """
    # In order to print to a text file, we use wt
    fout = open(self._file_name, "wt")

    for stud in self.get_all():
      student_string = str(stud.id) + "," + stud.name + "," + str(stud.group) + "\n"
      fout.write(student_string)
    
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
