from domain.student import student
from repository.MemoryRepository import MemoryRepository
import pickle

class BinaryFileRepository(MemoryRepository):
  # this class inherits from MemoryRepository
  # => has all the mathods and attributes in MemoryRepository
  def __init__(self, file_name = "students.bin"):
    """
    file_name: string
    """
    # call superclass constructor
    super(BinaryFileRepository, self).__init__()
    # remember the name of the file we're working with
    self._file_name = file_name
    # load the students from the file
    self._load_file()

  def erase_data(self):
    super().erase_data()
    open(self._file_name, "w").close()

  def _load_file(self):
    """
    Loads the students from a binary file
    """
    # In order to read from a binary, we use rb
    try:
      fin = open(self._file_name, 'rb')
      obj = pickle.load(fin)
    except EOFError:
      return

    for new_student in obj:
      super().add(new_student, False)

    fin.close()

  def _save_file(self):
    """
    Saves all students to our binary file
    """
    # In order to print to a binary file, we use wb
    fout = open(self._file_name, "wb")
    pickle.dump(self.get_all(), fout)
    
    # We close the file after we are done writing to it
    fout.close()

  # We are overriding our initial function of adding
  def add(self, new_student: student, appnd: bool):
    """
    new_student: student
    appnd: bool
    """
    # call the add() method on the super class
    # we want to do everything the superclass add() already does
    super().add(new_student, appnd)
    # save all the students in the binary file
    self._save_file()
  
  def filter(self, group: int):
    """
    group: int
    """

    super().filter(group)
    # save all the students in the binary file
    self._save_file()
  
  def undo_last_operation(self):
    super().undo_last_operation()
    # save all the students in the binary file
    self._save_file()
