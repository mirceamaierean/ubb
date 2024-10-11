import random
import math


class Board:
    def __init__(self, tiles):
        """
        Default constructor of our puzzle module. It initializes the following fields:

        self.size: the size of the table
        self.tiles: the tiles of the puzzle
        """
        self.size = 4
        self.tiles = tiles

    def __str__(self):
        """
        This function returns a string representation of the puzzle
        """
        pretty_print = ""
        for i in range(self.size):
            for j in range(self.size):
                pretty_print += self.tiles[i * self.size + j] + " "
            pretty_print += "\n"
        pretty_print = pretty_print[:-1]
        return pretty_print

    def execute_action(self, action):
        """
        :param action: the action that we want to execute
        :return: a new Board object that represents the new state of the puzzle after executing the action
        """
        new_tiles = self.tiles[:]
        empty_index = new_tiles.index("0")
        if action == 'l':
            if empty_index % self.size > 0:
                new_tiles[empty_index -
                          1], new_tiles[empty_index] = new_tiles[empty_index], new_tiles[empty_index - 1]
        elif action == 'r':
            if empty_index % self.size < (self.size - 1):
                new_tiles[empty_index +
                          1], new_tiles[empty_index] = new_tiles[empty_index], new_tiles[empty_index + 1]

        elif action == 'u':
            if empty_index - self.size >= 0:
                new_tiles[empty_index -
                          self.size], new_tiles[empty_index] = new_tiles[empty_index], new_tiles[empty_index - self.size]

        elif action == 'd':
            if empty_index + self.size < self.size * self.size:
                new_tiles[empty_index+self.size], new_tiles[empty_index] = new_tiles[empty_index], new_tiles[empty_index+self.size]

        return Board(new_tiles)


class Node:
    def __init__(self, state, parent, action):
        """
        Default constructor of our Node class. It initializes the following fields:
        self.state: the state of the node
        self.parent: the parent of the node
        self.action: the action that we execute to get to the current state
        """
        self.state = state
        self.parent = parent
        self.action = action

    def __str__(self):
        """
        Returns a string representation of the node
        """
        return str(self.state)

    def __eq__(self, other):
        """
        Checks if two nodes are equal
        """
        return self.state.tiles == other.state.tiles


def check_if_solvable(initial_list):
    """
    In order to be solvable, the invariant (number of inversions + row of empty tile) must be even
    We check if the invariant is even, if it is, the puzzle is solvable
    Before that, all the numbers must be unique, the length of the list must be 16, and the list must contain all the numbers from 0 to 15
    """
    if len(initial_list) != 16:
        return False
    for i in range(16):
        if str(i) not in initial_list:
            return False
    inversions = 0
    index_of_empty_tile = initial_list.index("0")
    for i in range(len(initial_list)):
        for j in range(i+1, len(initial_list)):
            if initial_list[i] > initial_list[j]:
                inversions += 1
    return (index_of_empty_tile // 4 + inversions) % 2 == 0


def test_if_solution(current_tiles):
    """
    Checks if the current state is the final configuration
    """
    return current_tiles == ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '0']


def get_children(parent_node):
    """
    Returns a list of all the children of a node
    """
    children = []
    # left,right, up, down ; actions define direction of movement of empty tile
    actions = ['l', 'r', 'u', 'd']
    for action in actions:
        child_state = parent_node.state.execute_action(action)
        child_node = Node(child_state, parent_node, action)
        children.append(child_node)
    return children


def find_path(node):
    """
    Returns the path from the root to the current node
    """
    path = []
    while (node.parent is not None):
        path.append(node)
        node = node.parent
    return path


def run_bfs(node):
    """
    Runs the BFS algorithm to find the solution of the puzzle
    """
    queue = []
    queue.append(node)
    visited = []
    while queue:
        current_node = queue.pop(0)
        visited.append(current_node)
        if test_if_solution(current_node.state.tiles):
            path = find_path(current_node)
            path.append(node)
            path.reverse()
            return path
        for child in get_children(current_node):
            if child not in visited:
                queue.append(child)
    return None


def solve(initial_list):
    """
    Solves the puzzle
    """
    if not check_if_solvable(initial_list):
        return None
    root = Node(Board(initial_list), None, None)
    return run_bfs(root)
