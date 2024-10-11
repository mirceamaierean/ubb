import math
import random
from domain import taxi
from repository import MemoryRepository


class TaxisService:
  def __init__(self, length: int):
    self.__repo = MemoryRepository()
    self.__length = length
  
  def validate_coordinate(self, x: int, y: int):
    return x >= 0 and x <= 100 and y >= 0 and y <= 100

  def manhattan_distance(self, x1: int, x2: int, y1: int, y2: int):
    return abs(x1 - x2) + abs(y1 - y2) 

  def add_taxi(self, new_taxi: taxi):
    self.__repo.add_taxi(new_taxi)

  def generate_random_taxis(self):
    for i in range(self.__length):
      ok = False
      while not ok:
        ok = True
        x = random.randint(0, 100)
        y = random.randint(0, 100)
        for ex_taxi in self.__repo.get_taxis():
          if self.manhattan_distance(x, ex_taxi.x, y, ex_taxi.y) <= 5:
            ok = False
            break
        if ok:
          self.__repo.add_taxi(taxi(i, x, y, 0))
  
  def get_taxis(self):
    return self.__repo.get_taxis()

  def ride(self, start_x: int, start_y: int, end_x: int, end_y: int):
    minimum_distance = 201
    fare = self.manhattan_distance(start_x, end_x, start_y, end_y)
    for ex_taxi in self.__repo.get_taxis():
      distance = self.manhattan_distance(start_x, ex_taxi.x, start_y, ex_taxi.y)
      if distance < minimum_distance:
        minimum_distance = distance
        taxi_id = ex_taxi.id
    self.__repo.modify_taxi(taxi(taxi_id, end_x, end_y, self.__repo.get_taxis()[taxi_id].fare + fare))

  def simulate_ride(self):
    start_x = random.randint(0, 100)
    start_y = random.randint(0, 100)
    end_x = random.randint(0, 100)
    end_y = random.randint(0, 100)
    while self.manhattan_distance(start_x, end_x, start_y, end_y) < 10:
      start_x = random.randint(0, 100)
      start_y = random.randint(0, 100)
      end_x = random.randint(0, 100)
      end_y = random.randint(0, 100)
    self.ride(start_x, start_y, end_x, end_y)
    return start_x, start_y, end_x, end_y
    
  def sort_taxis(self):
    taxis = self.get_taxis()
    for i in range(len(taxis)):
      for j in range(i, len(taxis)):
        if taxis[i].fare < taxis[j].fare:
          taxis[i], taxis[j] = taxis[j], taxis[i]
    return taxis