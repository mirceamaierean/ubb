from dataclasses import dataclass

@dataclass
class student:
    __student_id: int
    __student_name: str

    @property
    def id(self):
        return self.__student_id

    @property
    def name(self):
        return self.__student_name

    def __str__(self):
        return str(self.id) + " " + self.name

