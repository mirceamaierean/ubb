from pathlib import Path
import sys
path_root = Path(__file__).parents[2]
sys.path.append(str(path_root))
print(sys.path)

import random

from src.domain.student import student
from src.repository.repository import Repository


class StudentService:
  def __init__(self):
    self._repo = Repository()
    self.generate_random_values()

  def generate_random_values(self):
    list_of_names = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
    for i in range(20):
      id = random.randint(i * 10 + 1, (i + 1) * 10)
      name = random.choice(list_of_names)
      self.add_student(id, name)

  def check_if_student_is_valid(self, id: int):
    self._repo.check_if_not_present(id)

  def add_student(self, id: int, name: str):
    new_student = student(id, name)
    self._repo.add(new_student)

  def get_student_by_id(self, id: int):
    return self._repo.get_element_by_id(id)

  def get_all_students(self):
    return self._repo.get_all()

  def get_all_student_ids(self):
    return self._repo.get_all_ids()

  def update_student(self, id: int, name: str):
    updated_student = student(id, name)
    self._repo.update(updated_student)

  def delete_student(self, id: int):
    self._repo.remove(id)

  def delete_all_students(self):
    self._repo.delete_all()
  
  def search_student_based_on_id(self, id: int):
    return self._repo.search_after_id(id)
  
  def search_student_based_on_name(self, name: str):
    return self._repo.search_after_name(name)