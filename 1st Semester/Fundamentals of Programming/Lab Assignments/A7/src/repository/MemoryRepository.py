from domain.student import student

class RepoException(Exception):
    pass

class MemoryRepository:
  def __init__(self):
    # keys are student ids, values are student objects
    self._data = {}
    self._stack = []

  def erase_data(self):
    self._data.clear()

  def add(self, new_student: student, appnd: bool):
    """
    new_student: student
    appnd: bool
    """
    if new_student.id in self._data:
      return RepoException("Student is already in this repo")
    self._data[new_student.id] = new_student
    if appnd == True:
      operation = [2, new_student]
      self._stack.append(operation)

  def get_all(self):
    return list(self._data.values())
  
  def filter(self, group: int):
    """
    group: int
    """
    operation = [1]
    filtered_dict = {}
    for el in self._data.values():
      if el.group != group:
        filtered_dict[el.id] = el
      else:
        operation.append(el)
    self._data = filtered_dict.copy()
    self._stack.append(operation)

  def delete_student(self, existing_student: student):
    """
    existing_student: student
    """
    del self._data[existing_student.id]

  def add_students(self, list_of_students: list):
    """
    list_of_student: list of students
    """
    for new_student in list_of_students:
      self._data[new_student.id] = new_student

  def undo_last_operation(self):
    if len(self._stack) == 0:
      return

    operation = self._stack[-1]
    self._stack.pop()

    if operation[0] == 1: # The last performed operation was filter, we have deleted students, so we have to add them back
      self.add_students(operation[1:])
    
    else: # The last performed operation was add, we have added a student, so we have to erase it
      self.delete_student(operation[1])