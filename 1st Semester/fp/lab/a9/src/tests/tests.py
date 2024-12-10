import math
import unittest
from services.ai import AI

from services.game import Game

class TestBoard(unittest.TestCase):
    def testDraw(self):
      game = Game()
      for col in range(3):
        for _ in range(6):
          game.drop_piece(col)
      for col in range(4, 6):
        for _ in range(6):
          game.drop_piece(col)
      game.drop_piece(6)
      for _ in range(6):
        game.drop_piece(3)
      for _ in range(5):
        game.drop_piece(6)
      self.assertEqual(game.is_draw(), True)

    def testWinHorizontal(self):
      game = Game()
      for col in range(3):
        for _ in range(2):
          game.drop_piece(col)
      game.drop_piece(3)
      self.assertEqual(game.winning_move(3), True)
    
    def testWinVertical(self):
      game = Game()
      for _ in range(3):
        game.drop_piece(0)
        game.drop_piece(1)
      game.drop_piece(0)
      self.assertEqual(game.winning_move(0), True)
    
    def testWin1stDiagonal(self):
      game = Game()
      for i in range(2):
        for col in range(i, 4 + i):
          game.drop_piece(col)
      game.drop_piece(2)
      game.drop_piece(3)
      game.drop_piece(3)
      self.assertEqual(game.winning_move(3), True)
    
    def testWin2ndDiagonal(self):
      game = Game()
      for i in range(2):
        for col in range(6 - i, 2 - i, -1):
          game.drop_piece(col)
      game.drop_piece(4)
      game.drop_piece(3)
      game.drop_piece(3)
      self.assertEqual(game.winning_move(3), True)
    
    def testBlockAi(self):
      game = Game()
      ai = AI(5)
      game.drop_piece(3)
      game.drop_piece(3)
      game.drop_piece(4)
      game.drop_piece(2)
      game.drop_piece(5)
      col = ai.minimax(game.board, 5, -math.inf, math.inf, True)[0]
      self.assertEqual(col, 6)

    def testAll(self):
      self.testDraw()
      self.testWinHorizontal()
      self.testWinVertical()
      self.testWin1stDiagonal()
      self.testWin2ndDiagonal()
      self.testBlockAi()
    