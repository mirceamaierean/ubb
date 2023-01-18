from domain.board import Board, WIDTH, HEIGHT
import numpy as np

class Game:
  def __init__(self):
    self.__board = Board()
    # turn: int
    # self.__turn = 0 - The first player's turn
    # self.__turn = 1 - The second player's turn
    self.__turn = 0 
    self.__game_over = False

  @property
  def game_over(self):
    return self.__game_over

  @game_over.setter
  def game_over(self, value):
    self.__game_over = value

  @property
  def turn(self):
    return self.__turn

  @property
  def board(self):
    return self.__board

  def get_board(self):
    return np.flip(self.__board.board, 0)

  def change_turn(self):
    self.__turn = self.__turn ^ 1

  # This function drops a piece in a certain column
  def drop_piece(self, col: int):
    self.__board.board[self.get_free_row(col)][col] = self.__turn + 1
    self.change_turn()

  # This function checks if a certain column is valid
  def is_valid_column(self, col: int):
    return col >= 0 and col < WIDTH and self.__board.board[HEIGHT - 1][col] == 0

  # This function returns the next open row for a certain column
  def get_free_row(self, col: int):
    for row in range(HEIGHT):
      if self.board.board[row][col] == 0:
        return row
    return HEIGHT
  
  # This function checks if the game ends as a draw
  def is_draw(self):
    return np.all(self.__board.board != 0)

  # This function checks if a certain move is a winning move
  def winning_move(self, col: int):
    row = self.get_free_row(col) - 1
    if row == -1:
      return False

    if row >= 3 and self.__board.board[row][col] == self.__board.board[row - 1][col] == self.__board.board[row - 2][col] == self.__board.board[row - 3][col]:
      self.__game_over = True
      return True
    
    for gap in range(4):
      top_x = row - gap
      top_y = col + gap

      if top_y < WIDTH and top_y - 3 >= 0:
        if self.__board.board[row][top_y] == self.__board.board[row][top_y - 1] == self.__board.board[row][top_y - 2] == self.__board.board[row][top_y - 3]:
          self.__game_over = True
          return True
        if top_x >= 0 and top_x + 3 < HEIGHT:
          if self.__board.board[top_x][top_y] == self.__board.board[top_x + 1][top_y - 1] == self.__board.board[top_x + 2][top_y - 2] == self.__board.board[top_x + 3][top_y - 3]:
            self.__game_over = True
            return True
          
      top_y = col - gap

      if top_x >= 0 and top_y >= 0 and top_x + 3 < HEIGHT and top_y + 3 < WIDTH:
        if self.__board.board[top_x][top_y] == self.__board.board[top_x + 1][top_y + 1] == self.__board.board[top_x + 2][top_y + 2] == self.__board.board[top_x + 3][top_y + 3]:
          self.__game_over = True
          return True 

    return False