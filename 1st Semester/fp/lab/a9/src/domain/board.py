WIDTH = 7
HEIGHT = 6
import numpy as np

class Board:
    def __init__(self):
        self.__board = np.zeros((HEIGHT, WIDTH), dtype=int)
      
    @property
    def board(self):
        return self.__board        