from dataclasses import dataclass

@dataclass
class discipline:
    __discipline_id: int
    __discipline_name: str

    @property
    def id(self):
        return self.__discipline_id

    @property
    def name(self):
        return self.__discipline_name

    def __str__(self):
        return str(self.id) + " " + self.name

