from domain import taxi

class RepoException(Exception):
    pass

class MemoryRepository:
  def __init__(self):
    self.__taxis = []

  def add_taxi(self, new_taxi: taxi):
    self.__taxis.append(new_taxi)

  def get_taxis(self):
    return self.__taxis

  def modify_taxi(self, new_taxi: taxi):
    self.__taxis[new_taxi.id] = new_taxi
