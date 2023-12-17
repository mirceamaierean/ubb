from domain.board import Board
import random

class Service:
    def __init__(self):
        self.__board = Board()
        self.__number_of_b = 3
        self.__e_x = None
        self.__e_y = None
        self.__game_over = 0
    
    def get_game_over(self):
      return self.__game_over

    def decrement_number_of_b(self):
      self.__number_of_b -= 1

    def count_stars(self):
      '''
      Input: -
      Output: count - integer
      Returns the number of existing stars on the board
      '''
      count = 0
      for i in range(8):
        for j in range(8):
          if self.__board.board[i][j] == '*':
            count += 1
      return count
  
    def reset_board(self):
      ''''
      Input: -
      Output: -
      Resets the board to the initial state
      '''
      self.__board = Board()
      self.__number_of_b = 3
      self.__e_x = None
      self.__e_y = None
      self.__game_over = 0

    def valid_star_position(self, x: int, y: int):
      '''
      Input:
        x - integer
        y - integer
      Output:
        True - if the position is valid
        False - if the position is not valid
      '''
      if x < 0 or x > 7 or y < 0 or y > 7:
        return False
      if self.__board.board[x][y] != ' ':
         return False
      if x == 0:
        if y == 0:
          if self.__board.board[x+1][y] == '*' or self.__board.board[x][y+1] == '*' or self.__board.board[x + 1][y + 1] == '*':
             return False
        elif y == 7:
          if self.__board.board[x+1][y] == '*' or self.__board.board[x][y-1] == '*' or self.__board.board[x + 1][y - 1] == '*':
            return False
        else:
          if self.__board.board[x+1][y] == '*' or self.__board.board[x][y+1] == '*' or self.__board.board[x][y-1] == '*' or self.__board.board[x + 1][y + 1] == '*' or self.__board.board[x + 1][y - 1] == '*':
            return False
      elif x == 7:
        if y == 0:
          if self.__board.board[x-1][y] == '*' or self.__board.board[x][y+1] == '*' or self.__board.board[x - 1][y + 1] == '*':
            return False
        elif y == 7:
          if self.__board.board[x-1][y] == '*' or self.__board.board[x][y-1] == '*' or self.__board.board[x - 1][y - 1] == '*':
            return False
        else:
          if self.__board.board[x-1][y] == '*' or self.__board.board[x][y+1] == '*' or self.__board.board[x][y-1] == '*' or self.__board.board[x - 1][y + 1] == '*' or self.__board.board[x - 1][y - 1] == '*':
            return False
      else:
        if y == 0:
          if self.__board.board[x - 1][y] == '*' or self.__board.board[x + 1][y] == '*' or self.__board.board[x][y+1] == '*' or self.__board.board[x - 1][y + 1] == '*' or self.__board.board[x + 1][y + 1] == '*':
            return False
        elif y == 7:
          if self.__board.board[x-1][y] == '*' or self.__board.board[x+1][y] == '*' or self.__board.board[x][y-1] == '*' or self.__board.board[x - 1][y - 1] == '*' or self.__board.board[x+1][y-1] == '*':
            return False
        else:
          if self.__board.board[x-1][y] == '*' or self.__board.board[x+1][y] == '*' or self.__board.board[x][y-1] == '*' or self.__board.board[x][y+1] == '*' or self.__board.board[x - 1][y - 1] == '*' or self.__board.board[x - 1][y + 1] == '*' or self.__board.board[x + 1][y - 1] == '*' or self.__board.board[x + 1][y + 1] == '*':
            return False
      return True
    
    def valid_e_position(self, x, y):
      '''
      Input: x - integer, y - integer
      Output: True - if the position is valid for USS Endeavour, False - if the position is not valid for USS Endeavour
      '''
      if self.__board.board[x][y] == ' ':
         return True
      return False
         
    def valid_b_position(self, x, y):
      '''
      Input: x - integer, y - integer
      Output: True - if the position is valid for Blingon cruiser, False - if the position is not valid for Blingon cruiser
      '''
      if self.__board.board[x][y] == ' ':
        return True
      return False
    
    def add_star(self, x, y):
      ''''
      Input:
        x - integer
        y - integer
      Output: -
      Adds a star to the board 
      '''
      self.__board.board[x][y] = '*'

    def generate_random_stars(self):
      '''
      Input: -
      Output: -
      Generates 10 random stars on the board
      '''
      for _ in range(10):
        x = random.randint(0, 7)
        y = random.randint(0, 7)
        while not self.valid_star_position(x, y):
          x = random.randint(0, 7)
          y = random.randint(0, 7)
        self.add_star(x, y)

    def generate_random_e(self):
      '''
      Input: -
      Output: -
      Generates a random position for the USS Endeavour
      '''
      x = random.randint(0, 7)
      y = random.randint(0, 7)
      while not self.valid_e_position(x, y):
        x = random.randint(0, 7)
        y = random.randint(0, 7)
      self.__board.board[x][y] = 'E'
      self.__e_x = x
      self.__e_y = y
    
    def valid_new_e_pos(self, x: int, y: int):
      '''
      Input: x - integer, y - integer
      Output: True - if the new position is valid for USS Endeavour, False - if the new position is not valid for USS Endeavour
      '''
      if x == self.__e_x or y == self.__e_y or abs(x - self.__e_x) == abs(y - self.__e_y):
        return True
      return False

    def proccess_command_wrap(self, cmd: list):
      dict_let = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7}
      dict_nr = {'1': 0, '2': 1, '3': 2, '4': 3, '5': 4, '6': 5, '7': 6, '8': 7}

      new_x = dict_let[cmd[0]]
      new_y = dict_nr[cmd[1]]

      old_x = self.__e_x
      old_y = self.__e_y

      if not self.valid_new_e_pos(new_x, new_y):
        return "Invalid move! Not on the same row, column or diagonal!"
      
      while old_x != new_x or old_y != new_y:
        if old_x < new_x:
          old_x += 1
        elif old_x > new_x:
          old_x -= 1
        if old_y < new_y:
          old_y += 1
        elif old_y > new_y:
          old_y -= 1
        if self.__board.board[old_x][old_y] == '*':
          return "Invalid move! A star is in the way!"
      
      if self.__board.board[new_x][new_y] == 'B':
        self.__game_over = 1
        return "You lost! You stepped on a Blingon Cruiser!"
      
      self.__board.board[self.__e_x][self.__e_y] = ' '
      self.__board.board[new_x][new_y] = 'E'
      self.__e_x = new_x
      self.__e_y = new_y
      return "True"

    def proccess_command_fire(self, cmd: list):
      dict_let = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7}
      dict_nr = {'1': 0, '2': 1, '3': 2, '4': 3, '5': 4, '6': 5, '7': 6, '8': 7}

      new_x = dict_let[cmd[0]]
      new_y = dict_nr[cmd[1]]
      
      if new_x == self.__e_x and new_y == self.__e_y:
        return "Invalid Move. Why would you shot yourself?"

      if new_x >= self.__e_x - 1 and new_x <= self.__e_x + 1 and new_y >= self.__e_y - 1 and new_y <= self.__e_y + 1:
        if self.__board.board[new_x][new_y] != 'B':
          return "Not a ship on this position to be fired"
        else:
          self.get_new_configuration_for_ships()
          return "True"
      return "Invalid move! You can only fire on the adjacent squares to your ship!"

    def get_new_configuration_for_ships(self):
      self.__number_of_b -= 1
      if self.__number_of_b == 0:
        self.__game_over = 2
      for i in range(8):
        for j in range(8):
          if self.__board.board[i][j] == 'B':
            self.__board.board[i][j] = ' '
      self.generate_random_b()

    def adjacent_e(self, x: int, y: int):
      if x == 0:
        if y == 0:
          if self.__board.board[x+1][y] == 'E' or self.__board.board[x][y+1] == 'E' or self.__board.board[x + 1][y + 1] == 'E':
             return True
        elif y == 7:
          if self.__board.board[x+1][y] == 'E' or self.__board.board[x][y-1] == 'E' or self.__board.board[x + 1][y - 1] == 'E':
            return True
        else:
          if self.__board.board[x+1][y] == 'E' or self.__board.board[x][y+1] == 'E' or self.__board.board[x][y-1] == 'E' or self.__board.board[x + 1][y + 1] == 'E' or self.__board.board[x + 1][y - 1] == 'E':
            return True
      elif x == 7:
        if y == 0:
          if self.__board.board[x-1][y] == 'E' or self.__board.board[x][y+1] == 'E' or self.__board.board[x - 1][y + 1] == 'E':
            return True
        elif y == 7:
          if self.__board.board[x-1][y] == 'E' or self.__board.board[x][y-1] == 'E' or self.__board.board[x - 1][y - 1] == 'E':
            return True
        else:
          if self.__board.board[x-1][y] == 'E' or self.__board.board[x][y+1] == 'E' or self.__board.board[x][y-1] == 'E' or self.__board.board[x - 1][y + 1] == 'E' or self.__board.board[x - 1][y - 1] == 'E':
            return True
      else:
        if y == 0:
          if self.__board.board[x-1][y] == 'E' or self.__board.board[x+1][y] == 'E' or self.__board.board[x][y+1] == 'E' or self.__board.board[x - 1][y + 1] == 'E' or self.__board.board[x + 1][y + 1] == 'E':
            return True
        elif y == 7:
          if self.__board.board[x-1][y] == 'E' or self.__board.board[x+1][y] == 'E' or self.__board.board[x][y-1] == 'E' or self.__board.board[x - 1][y - 1] == 'E' or self.__board.board[x + 1][y - 1] == 'E':
            return True
        else:
          if self.__board.board[x-1][y] == 'E' or self.__board.board[x+1][y] == 'E' or self.__board.board[x][y-1] == 'E' or self.__board.board[x][y+1] == 'E' or self.__board.board[x - 1][y - 1] == 'E' or self.__board.board[x - 1][y + 1] == 'E' or self.__board.board[x + 1][y - 1] == 'E' or self.__board.board[x + 1][y + 1] == 'E':
            return True
      return False

    def generate_random_b(self):
      for _ in range(self.__number_of_b):
        x = random.randint(0, 7)
        y = random.randint(0, 7)
        while not self.valid_b_position(x, y):
          x = random.randint(0, 7)
          y = random.randint(0, 7)
        self.__board.board[x][y] = 'B'

    def get_board(self, cheat: bool):
      new_board = [[' ' for _ in range(9)] for _ in range(9)]

      new_board[0][0] = '0'
      new_board[0][1] = '1'
      new_board[0][2] = '2'
      new_board[0][3] = '3'
      new_board[0][4] = '4'
      new_board[0][5] = '5'
      new_board[0][6] = '6'
      new_board[0][7] = '7'
      new_board[0][8] = '8'

      new_board[1][0] = 'A'
      new_board[2][0] = 'B'
      new_board[3][0] = 'C'
      new_board[4][0] = 'D'
      new_board[5][0] = 'E'
      new_board[6][0] = 'F'
      new_board[7][0] = 'G'
      new_board[8][0] = 'H'

      for i in range(8):
        for j in range(8):
          if self.__board.board[i][j] == 'B':
            if cheat or self.adjacent_e(i, j):
              new_board[i + 1][j + 1] = 'B'
            else:
              new_board[i + 1][j + 1] = ' '
          else:
            new_board[i + 1][j + 1] = self.__board.board[i][j]

      return new_board