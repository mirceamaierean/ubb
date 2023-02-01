import random

from src.domain.discipline import discipline
from src.repository.repository import Repository


class DisciplineService:
  def __init__(self):
    self._repo = Repository()
    self.generate_random_values()

  def generate_random_values(self):
    list_of_disciplines = ["Mathematical Analysis", "Computational Logic", "Algebra", "Fundamentals of Programming", "Computer System Architecture", "Object Oriented Programming", "Dynamical Systems", "Geometry", "Operating Systems", "Data Structures and Algorithms", "Graphs", "Advanced Programming Methods", "Databases", "Statistics"]
    for i in range(14):
      id = random.randint(i * 10 + 1, (i + 1) * 10)
      self.add_discipline(id, list_of_disciplines[i])

  def check_if_discipline_is_valid(self, id: int):
    self._repo.check_if_not_present(id)

  def add_discipline(self, id: int, name: str):
    new_discipline = discipline(id, name)
    self._repo.add(new_discipline)

  def get_discipline_by_id(self, id: int):
    return self._repo.get_element_by_id(id)

  def get_all_disciplines(self):
    return self._repo.get_all()

  def get_all_discipline_ids(self):
    return self._repo.get_all_ids()

  def update_discipline(self, id: int, name: str):
    updated_discipline = discipline(id, name)
    self._repo.update(updated_discipline)

  def delete_discipline(self, id: int):
    self._repo.remove(id)

  def delete_all_disciplines(self):
    self._repo.delete_all()
  
  def search_discipline_based_on_id(self, id: int):
    return self._repo.search_after_id(id)
  
  def search_discipline_based_on_name(self, name: str):
    return self._repo.search_after_name(name)