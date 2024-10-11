from dataclasses import dataclass

@dataclass
class taxi:
  __id: int
  __x: int
  __y: str
  __fare: int

  @property
  def x(self):
    return self.__x

  @property
  def y(self):
    return self.__y

  @property
  def id(self):
    return self.__id

  @property
  def fare(self):
    return self.__fare
