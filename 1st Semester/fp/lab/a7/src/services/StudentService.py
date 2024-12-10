import random
from domain.student import student


class StudentService:
  def __init__(self, repo):
    self._repo = repo
    self.generate_random_values()

  def generate_random_values(self):
    list_of_names = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
    for i in range(10):
      id = random.randint((i + 1) * 500 + 1, (i + 2) * 500)
      name = random.choice(list_of_names)
      group = random.randint(1, 1000)
      self.add_student(id, name, group, False)

  def clear_students(self):
    self._repo.erase_data()

  def add_student(self, id: int, name: str, group: int, appnd: bool):
    new_student = student(id, name, group)
    self._repo.add(new_student, appnd)
  
  def filter_students(self, group: int):
      self._repo.filter(group)

  def get_all_students(self):
    return self._repo.get_all()

  def undo_last_operation(self):
    self._repo.undo_last_operation()

