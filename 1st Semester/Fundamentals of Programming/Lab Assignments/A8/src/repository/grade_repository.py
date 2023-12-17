import grade as grade

from src.repository.repository_exception import RepositoryException


class GradeRepository:
  def __init__(self):
    self._data = []

  def check_if_input_is_valid(self, grade_value: float):
    if not (grade_value >= 0 and grade_value <= 10):
      raise RepositoryException("This grade is not valid!")
  
  def add(self, grade: grade):
    self.check_if_input_is_valid(grade.grade_value)
    self._data.append(grade)

  def get_all(self):
    return self._data

  def delete_grades_based_on_discipline(self, discipline_id: int):
    # for obj in list(self._data):
    #   if obj.discpline_id == discipline_id:
    #         self._data.remove(obj)
    self._data = [obj for obj in self._data if obj.discipline_id != discipline_id ]

  def delete_grades_based_on_student(self, student_id: int):
    # for obj in list(self._data):
    #   if obj.student_id == student_id:
    #         self._data.remove(obj)
    self._data = [obj for obj in self._data if obj.student_id != student_id ]