import copy
import math
from domain.board import HEIGHT, WIDTH, Board

class AI:
  def __init__(self, depth: int):
    self.__depth = depth
    self.__columns_array = [3, 2, 4, 1, 5, 0, 6]
    self.__AI = 2
    self.__HUMAN = 1
    self.__MAX_VALUE = (1 << 63) - 1

  # This function sets the depth for the alpha beta pruning algorithm
  def set_depth(self, depth: int):
    self.__depth = depth

  # This function checks if the game has been won by one either of the human or the AI
  def winning_move(self, board: Board, player: int):
    # Look after horizontal locations for win
    for row in range(HEIGHT):
      for col in range(WIDTH - 3):
        if board.board[row][col] == board.board[row][col + 1] == board.board[row][col + 2] == board.board[row][col + 3] == player:
            return True

    for row in range(HEIGHT - 3):
    # Look after vertical locations for win
      for col in range(WIDTH):
        if board.board[row][col] == board.board[row + 1][col] == board.board[row + 2][col] == board.board[row + 3][col] == player:
            return True
      # Look after diagonals for win
      for col in range(WIDTH - 1, 2, -1):
        if board.board[row][col] == board.board[row + 1][col - 1] == board.board[row + 2][col - 2] == board.board[row + 3][col - 3] == player:
            return True
      for col in range(WIDTH - 3):
        if board.board[row][col] == board.board[row + 1][col + 1] == board.board[row + 2][col + 2] == board.board[row + 3][col + 3] == player:
            return True
    return False
  
  # This function returns the score for a certain made by AI
  def get_tokens_score(self, tokens: list):
    score = 0

    cnt = tokens.count(self.__AI)
    opponent_cnt = tokens.count(self.__HUMAN)

    if cnt == 4:
      score += 1000
    elif opponent_cnt == 0:
      if cnt == 3:
        score += 100
      elif cnt == 2:
        score += 1
    if opponent_cnt == 3 and cnt == 0:
      score -= 10
    
    return score
  
  # This function returns the score for a certain board
  def get_board_score(self, board: Board):
    score = 0

    # Check score for vertical alignment
    # The more a column is close to the center, the more it's valuable
    for col in self.__columns_array:
      col_array = [i for i in list(board.board[:, col])]
      for row in range(HEIGHT - 3):
        tokens = col_array[row:row + 4]
        score += self.get_tokens_score(tokens)
    
    # Check score for horizontal alignment
    for row in range(HEIGHT):
      row_array = [i for i in list(board.board[row, :])]
      for col in range(WIDTH - 3):
        tokens = row_array[col:col + 4]
        score += self.get_tokens_score(tokens)
    
    # Check score for diagonals alignment
    for row in range(HEIGHT - 3):
      for col in range(WIDTH - 3):
        tokens = [board.board[row + i][col + i] for i in range(4)]
        score += self.get_tokens_score(tokens)

    for row in range(HEIGHT - 3):
      for col in range(WIDTH - 3):
        tokens = [board.board[row + 3 - i][col + i] for i in range(4)]
        score += self.get_tokens_score(tokens) 
    
    return score
  
  # This function returns the next open row for a certain column
  def get_next_open_row(self, board: Board, col: int):
    for row in range(HEIGHT):
      if board.board[row][col] == 0:
        return row
    return 0

  # This function checks if a certain column is valid
  def is_valid_location(self, board: Board, col: int):
    return board.board[HEIGHT - 1][col] == 0

  # This function returns all the valid columns
  def get_valid_columns(self, board: Board):
    return [int(col) for col in self.__columns_array if self.is_valid_location(board, col)]
  
  # This function performs the move for a certain column
  def drop_piece(self, board: Board, col: int, player: int):
    board.board[self.get_next_open_row(board, col)][col] = player

  # This function checks if the game is over
  def terminal(self, board: Board):
    return self.winning_move(board, self.__AI) or self.winning_move(board, self.__HUMAN) or len(self.get_valid_columns(board)) == 0

  # This function returns the best move for the AI, based on the minimax algorithm, with alpha-beta pruning. A pair of numbers is returned, composed by the column and the scoreß
  def minimax(self, board: Board, depth: int, alpha: int, beta: int, maximizingPlayer: bool):
    valid_columns = self.get_valid_columns(board)
    
    terminal = self.terminal(board)

    if depth == 0 or terminal:
      if terminal: 
        if self.winning_move(board, self.__AI):
          return (None, self.__MAX_VALUE)

        elif self.winning_move(board, self.__HUMAN):
          return (None, -self.__MAX_VALUE)
        
        else:
          return (None, 0)
      else: 
        return (None, self.get_board_score(board))      
    
    if maximizingPlayer:
      value = -math.inf
      column = valid_columns[0]

      if depth == self.__depth:
        for col in valid_columns:
          new_board = copy.deepcopy(board)
          self.drop_piece(new_board, col, self.__AI)
          if self.winning_move(new_board, self.__AI):
            return col, None

      for col in valid_columns:
        new_board = copy.deepcopy(board)
        self.drop_piece(new_board, col, self.__AI)
        new_score = self.minimax(new_board, depth - 1, alpha, beta, False)[1]

        if new_score > value:
          value = new_score
          column = col
          
        alpha = max(alpha, value)
        if alpha >= beta:
          break
      return column, value

    else:
      value = math.inf
      column = valid_columns[0]
      for col in valid_columns:
        new_board = copy.deepcopy(board)
        self.drop_piece(new_board, col, self.__HUMAN)
        new_score = self.minimax(new_board, depth - 1, alpha, beta, True)[1]
        if new_score < value:
          value = new_score
          column = col
        beta = min(beta, value)
        if alpha >= beta:
          break
      return column, value  