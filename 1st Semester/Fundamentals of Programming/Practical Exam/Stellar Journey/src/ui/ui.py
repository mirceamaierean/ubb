from services.service import Service
import texttable

class UI:
    def __init__(self):
        self.__service = Service()
        self.__service.generate_random_stars()
        self.__service.generate_random_e()
        self.__service.generate_random_b()
    
    def print_ui(self, cheat = False):
        board = self.__service.get_board(cheat)
        table = texttable.Texttable()
        table.add_rows(board)
        print(table.draw())

    def play(self):
        self.print_ui()
        while not self.__service.get_game_over():
            command = input("Available Comands\n 1) warp <coordinate> (e.g. warp G5) \n 2) fire <coordinate (e.g. fire B4) \n 3) cheat \n")
            command_separated = command.split()
            if len(command_separated) ==  1:
                if command_separated[0] == 'cheat':
                    self.print_ui(True)
                else:
                    print("Invalid command! Please try again!")
            elif len(command_separated) == 2:
                if len(command_separated[1]) != 2 or not (command_separated[1][0] >= 'A' and command_separated[1][0] <= 'H') or not (command_separated[1][1] >= '1' and command_separated[1][1] <= '8'):
                    print("Invalid pair of coordinates! Please try again!")
                elif command_separated[0] == 'warp':
                    response = self.__service.proccess_command_wrap(command_separated[1])
                    if response != "True":
                        print(response)
                    if self.__service.get_game_over() != 0:
                        break
                    self.print_ui()
                elif command_separated[0] == 'fire':
                    response = self.__service.proccess_command_fire(command_separated[1])
                    if response != "True":
                        print(response)
                    if self.__service.get_game_over() != 0:
                        break
                    self.print_ui()
                else:
                    print("Invalid command! Please try again!")
            else:
                print("Invalid command! Please try again!")
        if self.__service.get_game_over() == 2:
            print("You destroyed all the ships. You won!!!!")
