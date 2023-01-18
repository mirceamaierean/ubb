from dataclasses import dataclass

@dataclass
class student:
    __student_id: int
    __student_name: str
    __student_group: int

    @property
    def id(self):
        return self.__student_id

    @property
    def name(self):
        return self.__student_name

    @property
    def group(self):
        return self.__student_group

    def __str__(self):
        return str(self.id) + " " + self.name + " " + str(self.group)

