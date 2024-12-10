from pathlib import Path
import sys

path_root = Path(__file__).parents[2]
sys.path.append(str(path_root))

import PySimpleGUI as sg
from src.services.student_service import StudentService
from src.services.discipline_service import DisciplineService
from src.services.grade_service import GradeService
from src.domain.student import student

class GUI:
  def __init__(self):
    self.__student_service = StudentService()
    self.__discipline_service = DisciplineService()
    self.__grades_service = GradeService()
    self.__grades_service.generate_random_grades(self.__student_service.get_all_student_ids(), self.__discipline_service.get_all_discipline_ids())

  def run_main_window(self):
    main_layout = [[sg.Text("Welcome to Students Register Management")], [sg.Button("Manage Students"), sg.Button("Manage Disciplines"), sg.Button("Grade Students"), sg.Button("Search Students"), sg.Button("Search Disciplines"), sg.Button("Display Statistics")]]
    
    main_window = sg.Window(title="Students Register Management", layout = main_layout, margins=(100, 50))

    while True:
      event, values = main_window.read()
      if event == sg.WIN_CLOSED:
        break
      if event == "Manage Students":
        self.run_manage_students_window()
      if event == "Manage Disciplines":
        self.run_manage_disciplines_window()
      if event == "Grade Students":
        self.run_grade_student()
      if event == "Search Students":
        self.run_search_students()
      if event == "Search Disciplines":
        self.run_search_disciplines()
      if event == "Display Statistics":
        self.run_display_statistics()

    main_window.close()

  def run_manage_students_window(self):
    student_layout = [[sg.Text("Manage Students")], [sg.Button("Add a student"), sg.Button("Remove a student"), sg.Button("Update name of student"), sg.Button("List all students")], [sg.pin(sg.Text('', key = '_text_', visible = True))], [[sg.pin(sg.Text("Student ID", key = '__s_id', visible = False)), sg.pin(sg.InputText(key = "_student_id_", visible = False))]], [[sg.pin(sg.Text("Student Name", key = '__s_name', visible = False)), sg.pin(sg.InputText(key = "_student_name_", visible = False))]], [sg.pin(sg.Button("Commit Add", visible = False)), sg.pin(sg.Button("Commit Remove", visible = False)), sg.pin(sg.Button("Commit Update", visible = False))]]
    
    student_window = sg.Window(title="Manage Students", layout = student_layout, margins=(100, 50))
    while True:
      event, values = student_window.read()
      # End program if user closes window or
      # presses the OK button
      if event == sg.WIN_CLOSED:
        break
      if event == "Add a student":
        student_window["_text_"].update("")
        student_window["__s_id"].update(visible = True)
        student_window["_student_id_"].update(visible = True)
        student_window["__s_name"].update(visible = True)
        student_window["_student_name_"].update(visible = True)
        student_window["Commit Add"].update(visible = True)
        student_window["Commit Update"].update(visible = False)
        student_window["Commit Remove"].update(visible = False)
      if event == "Update name of student":
        student_window["_text_"].update("")
        student_window["__s_id"].update(visible = True)
        student_window["_student_id_"].update(visible = True)
        student_window["__s_name"].update(visible = True)
        student_window["_student_name_"].update(visible = True)
        student_window["Commit Add"].update(visible = False)
        student_window["Commit Update"].update(visible = True)
        student_window["Commit Remove"].update(visible = False)
      if event == "Remove a student":
        student_window["_text_"].update("")
        student_window["__s_id"].update(visible = True)
        student_window["_student_id_"].update(visible = True)
        student_window["__s_name"].update(visible = False)
        student_window["_student_name_"].update(visible = False)
        student_window["Commit Add"].update(visible = False)
        student_window["Commit Update"].update(visible = False)
        student_window["Commit Remove"].update(visible = True)
      if event == "List all students":
        student_window["__s_id"].update(visible = False)
        student_window["_student_id_"].update(visible = False)
        student_window["__s_name"].update(visible = False)
        student_window["_student_name_"].update(visible = False)
        student_window["Commit Add"].update(visible = False)
        student_window["Commit Update"].update(visible = False)
        student_window["Commit Remove"].update(visible = False)
        all_students = self.__student_service.get_all_students()
        s = "The students registered are: \n"
        for stud in all_students:
          s += str(stud)
          s += "\n"
        student_window["_text_"].update(s)
      if event == "Commit Add":
        self.__student_service.add_student(int(values["_student_id_"]), values["_student_name_"])
        student_window["_text_"].update("Student has been added")
      if event == "Commit Update":
        self.__student_service.update_student(int(values["_student_id_"]), values["_student_name_"])
        student_window["_text_"].update("Student has been updated")
      if event == "Commit Remove":
        self.__student_service.delete_student(int(values["_student_id_"]))
        student_window["_text_"].update("Student has been remvoed")

    student_window.close()

  def run_manage_disciplines_window(self):
    discipline_layout = [[sg.Text("Manage Disciplines")], [sg.Button("Add a discipline"), sg.Button("Remove a discipline"), sg.Button("Update name of discipline"), sg.Button("List all disciplines")], [sg.pin(sg.Text('', key = '_text_', visible = True))], [[sg.pin(sg.Text("Discipline ID", key = '__d_id', visible = False)), sg.pin(sg.InputText(key = "_discipline_id_", visible = False))]], [[sg.pin(sg.Text("Discipline Name", key = '__d_name', visible = False)), sg.pin(sg.InputText(key = "_discipline_name_", visible = False))]], [sg.pin(sg.Button("Commit Add", visible = False)), sg.pin(sg.Button("Commit Remove", visible = False)), sg.pin(sg.Button("Commit Update", visible = False))]]
    
    discipline_window = sg.Window(title="Manage Discipline", layout = discipline_layout, margins=(100, 50))
    while True:
      event, values = discipline_window.read()
      # End program if user closes window or
      # presses the OK button
      if event == sg.WIN_CLOSED:
        break
      if event == "Add a discipline":
        discipline_window["_text_"].update("")
        discipline_window["__d_id"].update(visible = True)
        discipline_window["_discipline_id_"].update(visible = True)
        discipline_window["__d_name"].update(visible = True)
        discipline_window["_discipline_name_"].update(visible = True)
        discipline_window["Commit Add"].update(visible = True)
        discipline_window["Commit Update"].update(visible = False)
        discipline_window["Commit Remove"].update(visible = False)
      if event == "Update name of discipline":
        discipline_window["_text_"].update("")
        discipline_window["__d_id"].update(visible = True)
        discipline_window["_discipline_id_"].update(visible = True)
        discipline_window["__d_name"].update(visible = True)
        discipline_window["_discipline_name_"].update(visible = True)
        discipline_window["Commit Add"].update(visible = False)
        discipline_window["Commit Update"].update(visible = True)
        discipline_window["Commit Remove"].update(visible = False)
      if event == "Remove a discipline":
        discipline_window["_text_"].update("")
        discipline_window["__d_id"].update(visible = True)
        discipline_window["_discipline_id_"].update(visible = True)
        discipline_window["__d_name"].update(visible = False)
        discipline_window["_discipline_name_"].update(visible = False)
        discipline_window["Commit Add"].update(visible = False)
        discipline_window["Commit Update"].update(visible = False)
        discipline_window["Commit Remove"].update(visible = True)
      if event == "List all disciplines":
        discipline_window["_text_"].update("")
        discipline_window["__d_id"].update(visible = False)
        discipline_window["_discipline_id_"].update(visible = False)
        discipline_window["__d_name"].update(visible = False)
        discipline_window["_discipline_name_"].update(visible = False)
        discipline_window["Commit Add"].update(visible = False)
        discipline_window["Commit Update"].update(visible = False)
        discipline_window["Commit Remove"].update(visible = True)
        all_discipline = self.__discipline_service.get_all_disciplines()
        s = "The discipline registered are: \n"
        for disc in all_discipline:
          s += str(disc)
          s += "\n"
        discipline_window["_text_"].update(s)
      if event == "Commit Add":
        self.__discipline_service.add_discipline(int(values["_discipline_id_"]), values["_discipline_name_"])
        discipline_window["_text_"].update("Discipline has been added")
      if event == "Commit Update":
        self.__discipline_service.update_discipline(int(values["_discipline_id_"]), values["_discipline_name_"])
        discipline_window["_text_"].update("Discipline has been updated")
      if event == "Commit Remove":
        self.__discipline_service.delete_discipline(int(values["_discipline_id_"]))
        discipline_window["_text_"].update("Discipline has been remvoed")

    discipline_window.close()

  def run_grade_student(self):
    grade_layout = [[sg.Text("Grade a student")], [[sg.Text("Discipline ID"), sg.InputText()], [sg.Text("Student ID"), sg.InputText()], [sg.Text("Grade"), sg.InputText()]], [sg.Button("Grade the student")], [sg.pin(sg.Text('', key = '_text_', visible = True))]]

    grade_window = sg.Window(title="Grade a Students", layout = grade_layout, margins=(100, 50))
    while True:
      event, values = grade_window.read()
      # End program if user closes window or
      # presses the OK button
      if event == sg.WIN_CLOSED:
        break
      if event == "Grade the student":
        self.__grades_service.add_grade(int(values[0]), int(values[1]), float(values[2]))
        grades = self.__grades_service.get_all_grades()
        s = "The grade of the students are: \n"
        for gr in grades:
          s += self.__student_service.get_student_by_id(gr.student_id).name + "(" + str(gr.student_id) + ") " + self.__discipline_service.get_discipline_by_id(gr.discipline_id).name + "(" + str(gr.discipline_id) + ") " + str(gr.grade_value) + "\n"
        grade_window["_text_"].update(s)
    grade_window.close()

  def run_search_students(self):
    search_students_layout = [[sg.Text("Search students")], [sg.Button("Search based on ID"), sg.Button("Search based on name")], [sg.pin(sg.Text('', key = '_text_', visible = True))], [[sg.pin(sg.Text("Student ID", key = '_id_', visible = False)), sg.pin(sg.InputText(key = "_s_id_", visible = False))]], [[sg.pin(sg.Text("Student Name", key = '_name_', visible = False)), sg.pin(sg.InputText(key = "_s_name_", visible = False))]], [sg.pin(sg.Button("Search after ID", visible = False)), sg.pin(sg.Button("Search after name", visible = False))]]

    search_students_window = sg.Window(title="Search students", layout = search_students_layout, margins=(100, 50))
    while True:
      event, values = search_students_window.read()
      # End program if user closes window or
      # presses the OK button
      if event == "Search based on ID":
        search_students_window["_text_"].update("")
        search_students_window["_id_"].update(visible = True)
        search_students_window["_s_id_"].update(visible = True)
        search_students_window["_name_"].update(visible = False)
        search_students_window["_s_name_"].update(visible = False)
        search_students_window["Search after ID"].update(visible = True)
        search_students_window["Search after name"].update(visible = False)

      if event == "Search based on name":
        search_students_window["_text_"].update("")
        search_students_window["_id_"].update(visible = False)
        search_students_window["_s_id_"].update(visible = False)
        search_students_window["_name_"].update(visible = True)
        search_students_window["_s_name_"].update(visible = True)
        search_students_window["Search after ID"].update(visible = False)
        search_students_window["Search after name"].update(visible = True)
      
      if event == "Search after ID":
        s = ""
        id = int(values["_s_id_"])
        students = self.__student_service.search_student_based_on_id(id)
        for stud in students:
            s += str(stud) + "\n"
        search_students_window["_text_"].update(s)
      
      if event == "Search after name":
        s = ""
        name = values["_s_name_"]
        students = self.__student_service.search_student_based_on_name(name)
        for stud in students:
            s += str(stud) + "\n"
        search_students_window["_text_"].update(s)

      if event == sg.WIN_CLOSED:
        break
      # if event == "Grade the student":
      #   print(int(values[0]), int(values[1]), float(values[2]))
    search_students_window.close()

  def run_search_disciplines(self):
    search_disciplines_layout = [[sg.Text("Search disciplines")], [sg.Button("Search based on ID"), sg.Button("Search based on name")], [sg.pin(sg.Text('', key = '_text_', visible = True))], [[sg.pin(sg.Text("Discipline ID", key = '_id_', visible = False)), sg.pin(sg.InputText(key = "_s_id_", visible = False))]], [[sg.pin(sg.Text("Discipline Name", key = '_name_', visible = False)), sg.pin(sg.InputText(key = "_s_name_", visible = False))]], [sg.pin(sg.Button("Search after ID", visible = False)), sg.pin(sg.Button("Search after name", visible = False))]]

    search_disciplines_window = sg.Window(title="Search disciplines", layout = search_disciplines_layout, margins=(100, 50))
    while True:
      event, values = search_disciplines_window.read()
      # End program if user closes window or
      # presses the OK button
      if event == "Search based on ID":
        search_disciplines_window["_text_"].update("")
        search_disciplines_window["_id_"].update(visible = True)
        search_disciplines_window["_s_id_"].update(visible = True)
        search_disciplines_window["_name_"].update(visible = False)
        search_disciplines_window["_s_name_"].update(visible = False)
        search_disciplines_window["Search after ID"].update(visible = True)
        search_disciplines_window["Search after name"].update(visible = False)

      if event == "Search based on name":
        search_disciplines_window["_text_"].update("")
        search_disciplines_window["_id_"].update(visible = False)
        search_disciplines_window["_s_id_"].update(visible = False)
        search_disciplines_window["_name_"].update(visible = True)
        search_disciplines_window["_s_name_"].update(visible = True)
        search_disciplines_window["Search after ID"].update(visible = False)
        search_disciplines_window["Search after name"].update(visible = True)
      
      if event == "Search after ID":
        s = ""
        id = int(values["_s_id_"])
        disciplines = self.__discipline_service.search_discipline_based_on_id(id)
        for disc in disciplines:
            s += str(disc) + "\n"
        search_disciplines_window["_text_"].update(s)
      
      if event == "Search after name":
        s = ""
        name = values["_s_name_"]
        disciplines = self.__discipline_service.search_discipline_based_on_name(name)
        for disc in disciplines:
            s += str(disc) + "\n"
        search_disciplines_window["_text_"].update(s)

      if event == sg.WIN_CLOSED:
        break
      # if event == "Grade the student":
      #   print(int(values[0]), int(values[1]), float(values[2]))
    search_disciplines_window.close()

  def run_display_statistics(self):
    
    statistics_layout = [[sg.Text("Display Statistics")], [sg.Button("Students failing at one or more disciplines"), sg.Button("Students with the best school situation"), sg.Button("All disciplines at which there is at least one grade")], [sg.pin(sg.Text('', key = '_text_', visible = True))]]
    statistics_window = sg.Window(title="Search disciplines", layout = statistics_layout, margins=(100, 50))
    while True:
      event, values = statistics_window.read()
      if event == "Students failing at one or more disciplines":
        s = "The students who are failing are:\n"
        failing_students = self.__grades_service.failing_students()
        for obj in failing_students:
          s += self.__student_service.get_student_by_id(obj[0][0]).name + "(" + str(obj[0][0]) + ") " + self.__discipline_service.get_discipline_by_id(obj[0][1]).name + "(" + str(obj[0][1]) + ") " + str(obj[1]) + "\n"
        statistics_window["_text_"].update(s)

      if event == "Students with the best school situation":
        s = "The best students are:\n"
        best_students = self.__grades_service.best_students()
        for stud in best_students:
          s += str(self.__student_service.get_student_by_id(stud)) + " " + str(best_students[stud]) + "\n"
        statistics_window["_text_"].update(s)

      if event == "All disciplines at which there is at least one grade":
        s = "The discipline are:\n"
        descending_avg_disciplines = self.__grades_service.descending_avg_disciplines()
        for desc in descending_avg_disciplines:
          s += str(self.__discipline_service.get_discipline_by_id(desc)) + " " + str(descending_avg_disciplines[desc]) + "\n"
        statistics_window["_text_"].update(s)

      if event == sg.WIN_CLOSED:
        break
    statistics_window.close()

gui = GUI()

gui.run_main_window()