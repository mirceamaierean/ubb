from services.service import Service

class Test:
    def __init__(self):
        self.__service = Service()
    
    def test_valid_star_position(self):
        '''
        Initial Board
        +---+---+---+---+---+---+---+---+---+
        | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
        +===+===+===+===+===+===+===+===+===+
        | A |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | B |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | C |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | D |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | E |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | F |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | G |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | H |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        '''
        # Cells have to be put inside the board, we check the position to be inside the board
        assert self.__service.valid_star_position(-1, 4) == False 
        assert self.__service.valid_star_position(4, -1) == False 
        assert self.__service.valid_star_position(10, 4) == False 
        assert self.__service.valid_star_position(4, 12) == False 
        # Add a star
        assert self.__service.valid_star_position(4, 4) == True # Since we have started indexing from 0, the actual position for (4, 4) i E5

        self.__service.add_star(4, 4)
        '''
        Board after adding a star
        +---+---+---+---+---+---+---+---+---+
        | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
        +===+===+===+===+===+===+===+===+===+
        | A |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | B |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | C |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | D |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | E |   |   |   |   | * |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | F |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | G |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | H |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        For that position, we have 9 restricted cells (including itself) in which we can't add a star
        Those are E5, D5, F5, E4, E6, D4, D6, F4, F6
        The corresponding indexes for those cells are:
        (4, 4), (4, 3), (4, 5), (3, 3), (5, 4), (3, 3), (5, 5), (3, 5), (5, 3) 
        '''
        assert self.__service.valid_star_position(4, 4) == False 
        assert self.__service.valid_star_position(4, 3) == False 
        assert self.__service.valid_star_position(4, 5) == False 
        assert self.__service.valid_star_position(3, 3) == False 
        assert self.__service.valid_star_position(5, 4) == False 
        assert self.__service.valid_star_position(3, 3) == False 
        assert self.__service.valid_star_position(5, 5) == False 
        assert self.__service.valid_star_position(3, 5) == False 
        assert self.__service.valid_star_position(5, 3) == False 
        # The rest of the cells are valid, so we try to add one star in G7
        assert self.__service.valid_star_position(6, 6) == True
        self.__service.add_star(6, 6)
        '''
        Board after adding the second star
        +---+---+---+---+---+---+---+---+---+
        | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
        +===+===+===+===+===+===+===+===+===+
        | A |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | B |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | C |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | D |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | E |   |   |   |   | * |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | F |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        | G |   |   |   |   |   |   | * |   |
        +---+---+---+---+---+---+---+---+---+
        | H |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+---+
        '''
        assert self.__service.count_stars() == 2
        # Now, we reset the board, and check if there are exactly 10 generated stars
        self.__service.reset_board()
        # We generate 10 random stars
        self.__service.generate_random_stars()
        # We check if there are exactly 10 stars
        assert self.__service.count_stars() == 10