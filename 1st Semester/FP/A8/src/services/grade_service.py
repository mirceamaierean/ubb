import random
import statistics

from src.domain.grade import grade
from src.repository.grade_repository import GradeRepository


class GradeService:
  def __init__(self):
    self._repo = GradeRepository()
    self._statistics = {}

  def generate_random_grades(self, studs: list, disciplines: list):
    for _ in range(50):
      stud = random.choice(studs)
      disc = random.choice(disciplines)
      grade = random.uniform(2, 10)
      self.add_grade(disc, stud, grade)

  def check_of_grade_is_valid(self, grade: float):
    self._repo.check_if_input_is_valid(grade)

  def add_grade(self, discipline_id: int, student_id: int, grade_value: float):
    new_grade = grade(discipline_id, student_id, grade_value)
    self._repo.add(new_grade)

  def get_all_grades(self):
    return self._repo.get_all()

  def delete_grades_based_on_discipline(self, discipline_id: int):
    self._repo.delete_grades_based_on_discipline(discipline_id)

  def delete_grades_based_on_student(self, student_id: int):
    self._repo.delete_grades_based_on_student(student_id)

  def process_data(self):
    for grade in self.get_all_grades():
      key = (grade.student_id, grade.discipline_id)

      if key not in self._statistics:
        self._statistics.update({key: []})

      self._statistics[key].append(grade.grade_value)

  def failing_students(self):
    self.process_data()
    failing_students = []
    
    for key in self._statistics:
      avg = statistics.mean(self._statistics[key])
      if avg < 5:
        failing_students.append([key, avg])

    return failing_students

  def best_students(self):
    self.process_data()
    students_grades = {}
    best_students = {}
     
    for key in self._statistics:
      avg = statistics.mean(self._statistics[key])
      
      if key[0] not in students_grades: 
        students_grades.update({key[0]: []})

      students_grades[key[0]].append(avg)
    
    for key in students_grades:
      avg = statistics.mean(students_grades[key])
      best_students[key] = avg

    return dict(sorted(best_students.items(), key=lambda item: item[1], reverse=True))

  def descending_avg_disciplines(self):
    self.process_data()
    discipline_grades = {}
    descending_avg_disciplines = {}
     
    for key in self._statistics:
      avg = statistics.mean(self._statistics[key])
      
      if key[1] not in discipline_grades: 
        discipline_grades.update({key[1]: []})

      discipline_grades[key[1]].append(avg)
    
    for key in discipline_grades:
      avg = statistics.mean(discipline_grades[key])
      descending_avg_disciplines[key] = avg

    return dict(sorted(descending_avg_disciplines.items(), key=lambda item: item[1], reverse=True))