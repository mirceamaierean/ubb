from pathlib import Path
import sys, unittest
path_root = Path(__file__).parents[2]
sys.path.append(str(path_root))

from src.repository.repository_exception import RepositoryException
from src.services.discipline_service import DisciplineService
from src.services.student_service import StudentService
from src.services.grade_service import GradeService

class TestDisciplines(unittest.TestCase):
    def test_generate_random_values_disciplines(self):
        discipline_service = DisciplineService()
        self.assertEqual(len(discipline_service.get_all_disciplines()), 14)

    def test_get_ids(self):
        discipline_service = DisciplineService()
        self.assertEqual(len(discipline_service.get_all_discipline_ids()), 14)

    def test_add_discipline(self):
        id = 16437892578239
        name = "D1"
        discipline_service = DisciplineService()
        discipline_service.add_discipline(id, name)
        self.assertEqual(len(discipline_service.get_all_disciplines()), 15)

    def test_add_discipline_duplicate(self):
        id = 156243785623784
        name = "D1"
        discipline_service = DisciplineService()
        discipline_service.add_discipline(id, name)
        with self.assertRaises(RepositoryException): discipline_service.add_discipline(id, name)

    def test_update_discipline(self):
        discipline_service = DisciplineService()
        disciplines = discipline_service.get_all_disciplines()
        
        discipline_service.update_discipline(disciplines[0].id, "Discipline1")
        disciplines = discipline_service.get_all_disciplines()

        self.assertEqual(disciplines[0].name, "Discipline1")

    def test_update_discipline_not_found(self):
        discipline_service = DisciplineService()
        id = 12738621
        name = "Discipline1"
        with self.assertRaises(RepositoryException): discipline_service.update_discipline(id, name)

    def test_remove_discipline(self):
        discipline_service = DisciplineService()
        disciplines = discipline_service.get_all_disciplines()
        
        discipline_service.delete_discipline(disciplines[0].id)
        self.assertEqual(len(discipline_service.get_all_disciplines()), 13)

    def test_update_discipline_not_found(self):
        discipline_service = DisciplineService()
        id = 12738621
        with self.assertRaises(RepositoryException): discipline_service.delete_discipline(id)

    def test_delete_all_disciplines(self):
        discipline_service = DisciplineService()
        discipline_service.delete_all_disciplines()
        self.assertEqual(len(discipline_service.get_all_disciplines()), 0)

    def test_search_after_id(self):
        discipline_service = DisciplineService()
        discipline_service.delete_all_disciplines()
        discipline_service.add_discipline(1, "M1")
        discipline_service.add_discipline(2, "M2")
        discipline_service.add_discipline(3, "M3")
        discipline_service.add_discipline(10, "M4")
        discipline_service.add_discipline(13, "M5")
        discipline_service.add_discipline(15, "M6")
        discipline_service.add_discipline(27, "M7")
        discipline_service.add_discipline(31, "M8")
        discipline_service.add_discipline(38, "M9")
        discipline_service.add_discipline(1101, "M10")

        disc = discipline_service.search_discipline_based_on_id(1)

        self.assertEqual(len(disc), 6)

    def test_search_after_name(self):
        discipline_service = DisciplineService()
        discipline_service.delete_all_disciplines()
        discipline_service.add_discipline(1, "A1")
        discipline_service.add_discipline(2, "A2")
        discipline_service.add_discipline(3, "A3")
        discipline_service.add_discipline(10, "B4")
        discipline_service.add_discipline(13, "B5")
        discipline_service.add_discipline(15, "B6")
        discipline_service.add_discipline(27, "A7")
        discipline_service.add_discipline(31, "B8")
        discipline_service.add_discipline(38, "C9")
        discipline_service.add_discipline(1101, "M10")

        disc = discipline_service.search_discipline_based_on_name("A")

        self.assertEqual(len(disc), 4)

class TestStudents(unittest.TestCase):
    def test_generate_random_values_students(self):
        student_service = StudentService()
        self.assertEqual(len(student_service.get_all_students()), 20)

    def test_get_ids(self):
        student_service = StudentService()
        self.assertEqual(len(student_service.get_all_student_ids()), 20)

    def test_add_students(self):
        id = 1326489234
        name = "S1"
        student_service = StudentService()
        student_service.add_student(id, name)
        self.assertEqual(len(student_service.get_all_students()), 21)

    def test_add_student_duplicate(self):
        id = 1
        name = "D1"
        student_service = StudentService()
        student_service.add_student(id, name)
        with self.assertRaises(RepositoryException): student_service.add_student(id, name)

    def test_update_student(self):
        student_service = StudentService()
        students = student_service.get_all_students()
        
        student_service.update_student(students[0].id, "S1")
        students = student_service.get_all_students()

        self.assertEqual(students[0].name, "S1")

    def test_update_student_not_found(self):
        student_service = StudentService()
        id = 12738621
        name = "S1"
        with self.assertRaises(RepositoryException): student_service.update_student(id, name)

    def test_remove_student(self):
        student_service = StudentService()
        students = student_service.get_all_students()
        
        student_service.delete_student(students[0].id)
        self.assertEqual(len(student_service.get_all_students()), 19)

    def test_update_student_not_found(self):
        student_service = StudentService()
        id = 12738621
        with self.assertRaises(RepositoryException): student_service.delete_student(id)
    
    def test_delete_all_students(self):
        students_service = StudentService()
        students_service.delete_all_students()
        self.assertEqual(len(students_service.get_all_students()), 0)
    

    def test_search_after_id(self):
        student_service = StudentService()
        student_service.delete_all_students()
        student_service.add_student(1, "Matei")
        student_service.add_student(2, "Petru")
        student_service.add_student(3, "Pavel")
        student_service.add_student(10, "Andrei")
        student_service.add_student(13, "Ioan")
        student_service.add_student(15, "Iuda")
        student_service.add_student(27, "Toma")
        student_service.add_student(31, "Luca")
        student_service.add_student(38, "Iosif")
        student_service.add_student(1101, "Melisa")

        studs = student_service.search_student_based_on_id(1)

        self.assertEqual(len(studs), 6)

    def test_search_after_name(self):
        student_service = StudentService()
        student_service.delete_all_students()
        student_service.add_student(1, "Marcu")
        student_service.add_student(2, "Melisa")
        student_service.add_student(3, "Matei")
        student_service.add_student(10, "Amalia")
        student_service.add_student(13, "Olimpia")
        student_service.add_student(15, "Mariana")
        student_service.add_student(27, "Ioana")
        student_service.add_student(31, "Coman")
        student_service.add_student(38, "Malina")
        student_service.add_student(1101, "Andrei")
        studs = student_service.search_student_based_on_name("MA")
        self.assertEqual(len(studs), 7)

class TestGrades(unittest.TestCase):
    def test_generate_random_values_grades(self):
        grades_service = GradeService()
        student_service = StudentService()
        discipline_service = DisciplineService()

        grades_service.generate_random_grades(student_service.get_all_student_ids(), discipline_service.get_all_discipline_ids())

        grades = grades_service.get_all_grades()

        self.assertEqual(len(grades), 50)

    def test_add_grade_invalid_discipline(self):
        discipline_service = DisciplineService()
        discipline_id = 12364972378943
        with self.assertRaises(RepositoryException): discipline_service.check_if_discipline_is_valid(discipline_id)

    def test_add_grade_invalid_student(self):
        student_service = StudentService()
        student_id = 13478234823
        with self.assertRaises(RepositoryException): student_service.check_if_student_is_valid(student_id)

    def test_add_grade_invalid_grade(self):
        grade_service = GradeService()
        grade_value = 57498234.23
        with self.assertRaises(RepositoryException): grade_service.check_of_grade_is_valid(grade_value)

    def test_add_grade(self):
        discipline_service = DisciplineService()
        student_service = StudentService()
        grade_service = GradeService()

        discipline_ids = discipline_service.get_all_discipline_ids()
        student_ids = student_service.get_all_student_ids()
        grade_value = 7.2
        
        grade_service.add_grade(discipline_ids[0], student_ids[0], grade_value)

        self.assertEqual(len(grade_service.get_all_grades()), 1)

    def test_delete_grades_based_on_discipline(self):
        grade_service = GradeService()

        grade_service.add_grade(1, 1, 6.5)
        grade_service.add_grade(10, 19, 10)
        grade_service.add_grade(1, 27, 2.3)
        grade_service.add_grade(1012, 27, 2.3)
        grade_service.add_grade(110, 27, 2.3)
        grade_service.add_grade(1, 27, 2.3)
        grade_service.add_grade(1, 1, 6.5)

        grade_service.delete_grades_based_on_discipline(1)

        self.assertEqual(len(grade_service.get_all_grades()), 3)

    def test_delete_grades_based_on_student(self):
        grade_service = GradeService()

        grade_service.add_grade(1, 1, 6.5)
        grade_service.add_grade(10, 19, 10)
        grade_service.add_grade(1, 27, 2.3)
        grade_service.add_grade(1012, 27, 2.3)
        grade_service.add_grade(110, 27, 2.3)
        grade_service.add_grade(1, 27, 2.3)
        grade_service.add_grade(1, 1, 6.5)

        grade_service.delete_grades_based_on_student(27)

        self.assertEqual(len(grade_service.get_all_grades()), 3)

    def test_failing_students(self):
        grade_service = GradeService()

        grade_service.add_grade(1, 1, 1.5)
        grade_service.add_grade(2, 2, 5.5)
        grade_service.add_grade(3, 3, 2.5)
        grade_service.add_grade(4, 4, 5.5)
        grade_service.add_grade(5, 5, 5.5)
        grade_service.add_grade(6, 6, 3.5)
        grade_service.add_grade(7, 7, 4.5)
        grade_service.add_grade(8, 8, 4.7)
        grade_service.add_grade(9, 9, 4.9999)
        grade_service.add_grade(10, 9, 4.9999)

        self.assertEqual(len(grade_service.failing_students()), 7)

    def test_best_student(self):
        grade_service = GradeService()

        grade_service.add_grade(1, 1, 9)
        grade_service.add_grade(2, 1, 9.5)
        grade_service.add_grade(3, 1, 10)

        grade_service.add_grade(1, 2, 8)
        grade_service.add_grade(2, 2, 9)
        grade_service.add_grade(3, 2, 10)

        grade_service.add_grade(1, 3, 4)
        grade_service.add_grade(2, 3, 5)
        grade_service.add_grade(3, 3, 6)

        best_students = grade_service.best_students()
        best_avg = list(best_students.values())[0]
        self.assertEqual(best_avg, 9.5)

    def test_discplines_desc(self):
        grade_service = GradeService()

        grade_service.add_grade(1, 1, 9)
        grade_service.add_grade(1, 2, 8)
        grade_service.add_grade(1, 3, 4)

        grade_service.add_grade(2, 1, 9.5)
        grade_service.add_grade(2, 2, 9)
        grade_service.add_grade(2, 3, 5.5)
        
        grade_service.add_grade(3, 1, 10)
        grade_service.add_grade(3, 2, 10)        
        grade_service.add_grade(3, 3, 7)

        descending_avg_disciplines = grade_service.descending_avg_disciplines()
        best_avg = list(descending_avg_disciplines.values())[0]
        self.assertEqual(best_avg, 9)

if __name__ == '__main__':
    unittest.main()
