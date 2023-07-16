import math
import sys
import pygame
from services.ai import AI
from services.game import Game
from domain.board import WIDTH, HEIGHT


class UI:
    def __init__(self):
        self.__game = Game()
        self.__ai = AI(5)
        self.__depth = 5
        self.__tokens = ["\U000026aa", "\U0001f534", "\U0001f7e1"]

    def print_board(self):
        board = self.__game.get_board()
        for row in board:
            for col in row:
                print(self.__tokens[col], end="")
            print()

    def player_turn(self):
        col = int(input("Player " + str(self.__game.turn + 1) +
                  "\nMake your selection(1-7): ")) - 1
        if self.__game.is_valid_column(col):
            self.__game.drop_piece(col)
            self.print_board()
            if self.__game.winning_move(col):
                print("Player " + str((self.__game.turn ^ 1) + 1) + " wins!")
            if self.__game.is_draw():
                print("Draw!")
        else:
            print("Invalid column! Please try again.")
            self.player_turn()

    def ai_turn(self):
        print("AI's turn... \U000023F3")
        ai_col = self.__ai.minimax(
            self.__game.board, self.__depth, -math.inf, math.inf, True)[0]
        self.__game.drop_piece(ai_col)
        self.print_board()
        if self.__game.winning_move(ai_col):
            print("AI won!")
        if self.__game.is_draw():
            print("Draw!")

    def play(self):
        while not self.__game.game_over:
            self.player_turn()
            if not self.__game.game_over:
                self.player_turn()

    def play_with_ai(self):
        self.__ai.set_depth(self.__depth)
        while not self.__game.game_over:
            self.player_turn()
            if not self.__game.game_over:
                self.ai_turn()

    def run(self):
        print("Welcome to Connect 4! \n Select an option: \n 1. Play with AI \n 2. Play with another player \n 3. Exit")
        option = int(input())
        if option == 1:
            print(
                "You selected to play with AI. \n Select a difficulty: \n 1. Easy \n 2. Medium \n 3. Hard")
            difficulty = int(input())
            if difficulty == 1:
                self.__depth = 2
            elif difficulty == 2:
                self.__depth == 4
            self.play_with_ai()
        elif option == 2:
            print("You selected to play with another player.")
            self.play()
        elif option == 3:
            print("Goodbye!")
            sys.exit()
        else:
            print("Invalid option! Please try again.")
            self.run()


class GUI:
    def __init__(self):
        self.__game = Game()
        self.__ai = AI(3)
        self.__depth = 5
        self.init_window()
        self.SQUARESIZE = 100
        self.BLUE = (0, 102, 204)
        self.BUTTON = (0, 51, 204)
        self.FILL_COLOR = (233, 233, 233)
        self.RADIUS = int((self.SQUARESIZE >> 1) - 12)
        self.__screen = pygame.display.set_mode(
            (WIDTH * self.SQUARESIZE, (HEIGHT + 1) * self.SQUARESIZE))
        self.__font = pygame.font.SysFont("comic sans", 65)
        self.__images = [pygame.transform.scale(pygame.image.load("../src/static/images/red.png"), (
            90, 90)), pygame.transform.scale(pygame.image.load("../src/static/images/yellow.png"), (90, 90))]

    def init_window(self):
        pygame.init()
        pygame.display.set_caption('Connect 4')

    def get_appropriate_coordinates(self, x, y):
        return (y * self.SQUARESIZE + 5, x * self.SQUARESIZE)

    def draw_board(self):
        self.__screen.fill(self.FILL_COLOR)

        for col in range(WIDTH):
            for row in range(HEIGHT + 1):
                pygame.draw.rect(self.__screen, self.BLUE, (col * self.SQUARESIZE, row *
                                 self.SQUARESIZE + self.SQUARESIZE, self.SQUARESIZE, self.SQUARESIZE))
                if row > 0:
                    pygame.draw.circle(self.__screen, self.FILL_COLOR, (int(col * self.SQUARESIZE + (
                        self.SQUARESIZE >> 1)), int(row * self.SQUARESIZE + (self.SQUARESIZE >> 1))), self.RADIUS)

        for col in range(WIDTH):
            for row in range(HEIGHT):
                if self.__game.board.board[row][col] >= 1:
                    self.__screen.blit(
                        self.__images[self.__game.board.board[row][col] - 1], self.get_appropriate_coordinates(HEIGHT - row, col))

        pygame.display.update()

    def display_message(self, message: str, position: int):
        pygame.draw.rect(self.__screen, self.FILL_COLOR,
                         (0, 0, WIDTH * self.SQUARESIZE, self.SQUARESIZE))
        label = self.__font.render(message, 1, self.BLUE)
        self.__screen.blit(label, (position, 0))
        pygame.display.update()
        pygame.time.wait(2517)

    def falling_piece(self, col):
        clock = pygame.time.Clock()
        limit = (HEIGHT - self.__game.get_free_row(col)) * self.SQUARESIZE
        x = col * self.SQUARESIZE + 5
        y = 0
        while y < limit:
            self.draw_board()
            clock.tick(60)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()
            y += 100
            self.__screen.blit(self.__images[self.__game.turn], (x, y))
            pygame.display.update()
            pygame.time.wait(50)

    def draw_start_menu(self):
        self.__screen.fill(self.FILL_COLOR)
        for col in range(WIDTH):
            for row in range(HEIGHT + 1):
                pygame.draw.rect(self.__screen, self.BLUE, (col * self.SQUARESIZE, row *
                                 self.SQUARESIZE + self.SQUARESIZE, self.SQUARESIZE, self.SQUARESIZE))
        self.display_message("Welcome to Connect 4!", 0)

        self.__screen.blit(self.__images[0], (50, 550))
        self.__screen.blit(self.__images[1], (575, 550))

        pygame.display.update()

    def draw_button(self, message: str, rect_start_height: int, label_width: int, label_height: int):
        font = pygame.font.SysFont("comic sans", 20)
        label = font.render(message, 1, self.FILL_COLOR)
        pygame.draw.rect(self.__screen, self.FILL_COLOR,
                         (270, rect_start_height, 180, 35))
        pygame.draw.rect(self.__screen, self.BUTTON,
                         (273, rect_start_height + 2, 174, 31))
        self.__screen.blit(label, (label_width, label_height))

    def draw_start_buttons(self):
        self.draw_button("Play with a friend", 200, 276, 201)
        self.draw_button("Play against AI", 250, 288, 251)
        pygame.display.update()

    def draw_ai_buttons(self):
        self.draw_button("Easy AI", 300, 320, 301)
        self.draw_button("Medium AI", 350, 306, 351)
        self.draw_button("Hard AI", 400, 320, 401)

        pygame.display.update()

    def draw_piece(self, col):
        self.falling_piece(col)
        self.__game.drop_piece(col)
        if self.__game.winning_move(col):
            self.__game.game_over = True
            self.display_message(
                "Player " + str((self.__game.turn ^ 1) + 1) + " wins!", 150)
        if self.__game.is_draw():
            self.__game.game_over = True
            self.display_message("Draw!", 250)

    def move_piece(self, event):
        x_pos = event.pos[0]
        pygame.draw.rect(self.__screen, self.FILL_COLOR,
                         (0, 0, WIDTH * self.SQUARESIZE, self.SQUARESIZE))
        self.__screen.blit(self.__images[self.__game.turn], (x_pos, 0))
        pygame.display.update()

    def run(self):
        self.draw_start_menu()
        self.draw_start_buttons()
        ai_buttons = False
        while not self.__game.game_over:
            for event in pygame.event.get():
                mouse = pygame.mouse.get_pos()
                if event.type == pygame.QUIT:
                    sys.exit()
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if mouse[0] > 270 and mouse[0] < 450 and mouse[1] > 200 and mouse[1] < 235:
                        self.play()
                    elif mouse[0] > 270 and mouse[0] < 450 and mouse[1] > 250 and mouse[1] < 285:
                        self.draw_ai_buttons()
                        ai_buttons = True
                    elif ai_buttons:
                        if mouse[0] > 270 and mouse[0] < 450 and mouse[1] > 300 and mouse[1] < 330:
                            self.play_with_ai(2)
                        elif mouse[0] > 270 and mouse[0] < 450 and mouse[1] > 350 and mouse[1] < 380:
                            self.play_with_ai(4)
                        elif mouse[0] > 270 and mouse[0] < 450 and mouse[1] > 400 and mouse[1] < 430:
                            self.play_with_ai(5)

    def play(self):
        self.draw_board()
        pygame.display.update()

        while not self.__game.game_over:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()

                if event.type == pygame.MOUSEBUTTONDOWN:
                    col = event.pos[0] // self.SQUARESIZE
                    self.draw_piece(col)

                if event.type == pygame.MOUSEMOTION:
                    self.move_piece(event)

    def play_with_ai(self, depth: int):
        self.draw_board()

        self.__depth = depth
        self.__ai.set_depth(depth)

        while not self.__game.game_over:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()

                if event.type == pygame.MOUSEMOTION:
                    self.move_piece(event)

                if event.type == pygame.MOUSEBUTTONDOWN:
                    if self.__game.turn == 0:
                        col = event.pos[0] // self.SQUARESIZE
                        self.draw_piece(col)

            if self.__game.turn == 1 and not self.__game.game_over:
                col = self.__ai.minimax(
                    self.__game.board, self.__depth, -math.inf, math.inf, True)[0]
                self.draw_piece(col)
