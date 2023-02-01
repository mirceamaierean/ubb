from services.student_service import StudentService
from services.grade_service import GradeService
from services.discipline_service import DisciplineService

class UI:
  def __init__(self):
    self.__student_service = StudentService()
    self.__discipline_service = DisciplineService()
    self.__grades_service = GradeService()
    self.__grades_service.generate_random_grades(self.__student_service.get_all_student_ids(), self.__discipline_service.get_all_discipline_ids())

  def print_ui(self):
    while True:
      print ("1. Manage students")
      print ("2. Manage disciplines")
      print ("3. Grade a student")
      print ("4. Search for students")
      print ("5. Search for disciplines")
      print ("6. Display statistics")
      option = input("Choose your option: ")

      if option == "1":
        print ("1. Add a student")
        print ("2. Update information about the student")
        print ("3. Remove student")
        print ("4. List all students")
        option = input("Choose your option: ")
      
        if option == "1":
          id = int(input("What is the ID of the student? "))
          name = input("What is the name of the student? ")
          self.__student_service.add_student(id, name)
      
        elif option == "2":
          id = int(input("What is the ID of the student you want to update? "))
          name = input("What is the new name of the student? ")
          self.__student_service.update_student(id, name)
      
        elif option == "3":
          id = int(input("What is the ID of the student you want to delete? "))
          self.__grades_service.delete_grades_based_on_student(id)
          self.__student_service.delete_student(id)
      
        elif option == "4":
            students = self.__student_service.get_all_students()
            for stud in students:
              print(stud)
      
        else:
          print("Your input is not valid")
      
      elif option == "2":
        print ("1. Add a discipline")
        print ("2. Update information about the discipline")
        print ("3. Remove discipline")
        print ("4. List all disciplines")
        option = input("Choose your option: ")
      
        if option == "1":
          id = int(input("What is the ID of the discipline? "))
          name = input("What is the name of the discipline? ")
          self.__discipline_service.add_discipline(id, name)
      
        elif option == "2":
          id = int(input("What is the ID of the discipline you want to update? "))
          name = input("What is the new name of the discipline? ")
          self.__discipline_service.update_discipline(id, name)
      
        elif option == "3":
          id = int(input("What is the ID of the discipline you want to delete? "))
          self.__grades_service.delete_grades_based_on_discipline(id)
          self.__discipline_service.delete_discipline(id)
      
        elif option == "4":
          disciplines = self.__discipline_service.get_all_disciplines()
          for disc in disciplines:
            print(disc)
      
        else:
          print("Your input is not valid")

      elif option == "3":
        discipline_id = int(input("What is the ID of the discipline? "))
        self.__discipline_service.check_if_discipline_is_valid(discipline_id)

        student_id = int(input("What is the ID of the student? "))
        self.__student_service.check_if_student_is_valid(student_id)

        grade_value = float(input("What is the grade of the student? "))
        self.__grades_service.add_grade(discipline_id, student_id, grade_value)
        
        grades = self.__grades_service.get_all_grades()
        for grade in grades:
          print(grade)

      elif option == "4":
        print ("1. Search student based on id")
        print ("2. Search student based on name")
        option = input("Choose your option: ")
        
        if option == "1":
          id = int(input("What is the ID of the student? "))
          students = self.__student_service.search_student_based_on_id(id)
          for stud in students:
            print(stud)
        
        elif option == "2":
          name = input("What is the name of the student? ")
          students = self.__student_service.search_student_based_on_name(name)
          for stud in students:
            print(stud)
        
        else:
          print("Your input is not valid")
      
      elif option == "5":
        print ("1. Search discipline based on id")
        print ("2. Search discipline based on name")
        option = input("Choose your option: ")
      
        if option == "1":
          id = int(input("What is the ID of the discipline? "))
          disciplines = self.__discipline_service.search_discipline_based_on_id(id)
          for disc in disciplines:
            print(disc)
      
        elif option == "2":
          name = input("What is the name of the discipline? ")
          disciplines = self.__discipline_service.search_discipline_based_on_name(name)
          for disc in disciplines:
            print(disc)
      
        else:
          print("Your input is not valid")
      
      elif option == "6":
        print ("1. Display all the students that are failing at one or more disciplines")
        print ("2. Display the best students, based on aggregate average")
        print ("3. Display all the disciplines based on the grades received by the students")
        option = input("Choose your option: ")
      
        if option == "1":
          failing_students = self.__grades_service.failing_students()
          for obj in failing_students:
            print(self.__student_service.get_student_by_id(obj[0][0]).name, self.__discipline_service.get_discipline_by_id(obj[0][1]).name, obj[1])
      
        elif option == "2":
          best_students = self.__grades_service.best_students()
          for stud in best_students:
            print(self.__student_service.get_student_by_id(stud), best_students[stud])
      
        elif option == "3":
          descending_avg_disciplines = self.__grades_service.descending_avg_disciplines()
          for desc in descending_avg_disciplines:
            print(self.__discipline_service.get_discipline_by_id(desc), descending_avg_disciplines[desc])
      
      else:
        print("Your input is not valid")