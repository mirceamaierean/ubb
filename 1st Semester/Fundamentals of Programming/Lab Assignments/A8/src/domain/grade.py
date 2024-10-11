from dataclasses import dataclass

@dataclass
class grade:
    __discipline_id: int
    __student_id: int
    __grade_value: float

    @property
    def discipline_id(self):
        return self.__discipline_id

    @property
    def student_id(self):
        return self.__student_id

    @property
    def grade_value(self):
        return self.__grade_value

    def __str__(self):
        return str(self.discipline_id) + " " + str(self.student_id) + " " + str(self.grade_value)

