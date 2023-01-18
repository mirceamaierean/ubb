from services.StudentService import StudentService


class UI:
  def __init__(self, repo):
    self.__student_service = StudentService(repo)

  def print_ui(self):
    while True:
      print ("1. Add a student")
      print ("2. Disaply all students")
      print ("3. Filter students by group. All the students from that respective group will be deleted")
      print ("4. Undo the last operation you have performed")
      print ("5. Exit the application")
      option = input("Choose your option: ")
      if option == "1":
          id = int(input("What is the ID of the student? "))
          name = input("What is the name of the student? ")
          group = int(input("In which group is the student? "))
          self.__student_service.add_student(id, name, group, True)
      elif option == "2":
          students = self.__student_service.get_all_students()
          for stud in students:
            print(stud)
      elif option == "3":
        group = int(input("Which group would you like to remove? "))
        self.__student_service.filter_students(group)
      elif option == "4":
        self.__student_service.undo_last_operation()
      elif option == "5":
        print("Goodbye")
        return
      else:
        print("Your input is not valid")
