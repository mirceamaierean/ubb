class Board:
    def __init__(self):
        self._board = [[' ' for _ in range(8)] for _ in range(8)]
    
    @property
    def board(self):
        return self._board
    
    @board.setter
    def board(self, x, y, c):
        self.__board[x][y] = c