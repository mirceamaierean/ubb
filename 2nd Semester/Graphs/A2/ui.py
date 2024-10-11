from service import Service
import wolf_goat_cabbage
import puzzle


class UI:
    def __init__(self):
        self.__service = Service()
        pass

    def print_graph(self):
        """
        Prints the graph to the console
        """
        print(str(self.__service.graph.get_number_of_vertices()) +
              " " + str(self.__service.graph.get_number_of_edges()))
        out_edges = self.__service.graph.get_out_edges()
        for x in out_edges:
            for y in out_edges[x]:
                print(str(out_edges[x][y]) + ") " + str(x) + " " + str(y) + " " +
                      str(self.__service.graph.get_cost_of_edge(out_edges[x][y])))

    def print_vertices(self):
        """
        Prints the vertices of the graph
        """
        vertices = self.__service.graph.get_set_of_vertices()
        print("The vertices of the graph are: ")
        for v in vertices:
            print(str(v))

    def check_if_edge_exists(self):
        """
        Displays console menu for checking if an edge exists in the graph
        """
        x, y = input("Please enter the 2 vertices: ").split()
        try:
            x, y = int(x), int(y)
        except ValueError:
            print("Invalid input! Please try again!")
            return
        if self.__service.graph.check_if_edge_exists(x, y):
            print("There is an edge from " + str(x) + " to " + str(y))
        else:
            print("There is no edge from " + str(x) + " to " + str(y))

    def get_in_degree_and_out_degree(self):
        """
        Displays console menu for getting the in degree and out degree of a vertex
        """
        try:
            v = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input!")
            return
        print("The in degree of " + str(v) + " is " +
              str(self.__service.graph.get_in_degree(v)))
        print("The out degree of " + str(v) + " is " +
              str(self.__service.graph.get_out_degree(v)))

    def parse_outbound_edges(self):
        """
        Parses the outbound edges of a vertex
        """
        try:
            v = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input!")
            return
        out_edges = self.__service.graph.get_out_edges()
        if v in out_edges:
            if len(out_edges[v]) == 0:
                print("There are no outbound edges for " + str(v))
            else:
                print("The outbound edges of " + str(v) + " are: ")
                for y in out_edges[v]:
                    print(str(v) + " " + str(y) + " " + str(out_edges[v][y]))
        else:
            print("There are no outbound edges for " + str(v))

    def parse_inbound_edges(self):
        """
        Parses the inbound edges of a vertex
        """
        try:
            v = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input!")
            return
        in_edges = self.__service.graph.get_in_edges()
        if v in in_edges:
            if len(in_edges[v]) == 0:
                print("There are no inbound edges for " + str(v))
            else:
                print("The inbound edges of " + str(v) + " are: ")
                for x in in_edges[v]:
                    print(str(x) + " " + str(v) + " " + str(in_edges[v][x]))
        else:
            print("There are no inbound edges for " + str(v))

    def get_endpoints_of_edge(self):
        """
        Prints the endpoint of an edge
        """
        try:
            e = int(input("Please enter the edge: "))
        except ValueError:
            print("Invalid input!")
            return
        x, y = self.__service.graph.get_endpoints_of_edge(e)
        if x == -1:
            print("There is no edge with ID " + str(e))
        else:
            print("The endpoints of edge " + str(e) +
                  " are " + str(x) + " and " + str(y))

    def modify_cost_of_edge(self):
        """
        Interactive User Menu for modifying the cost of an edge
        """
        try:
            id = int(input("Cost of which edge do you want to modify? "))
        except ValueError:
            print("Invalid input!")
            return
        try:
            new_cost = int(input("What is the new cost? "))
        except ValueError:
            print("Invalid input!")
            return
        self.__service.graph.modify_cost_of_edge(id, new_cost)
        print("The cost of the edge has been modified to " + str(new_cost))

    def add_edge(self):
        """
        Menu to add an edge to the graph. If the graph is empty, the user MUST provide the number of vertices first. In case the user adds an edge with a vertex that does not exist, the vertex will be added to the graph. The vertices MUST BE smaller than n - 1 and greater than 0.
        """
        if self.__service.graph.get_number_of_vertices() == 0:
            print("First, you have to add vertices before you can add an edge!")
            return
        try:
            x, y, cost = input(
                "Please enter the 2 vertices and the cost: ").split()
            x, y, cost = int(x), int(y), int(cost)
        except ValueError:
            print("Invalid input!")
            return
        if x >= self.__service.graph.get_number_of_vertices() or y >= self.__service.graph.get_number_of_vertices():
            print("The provided vertices MUST BE between 0 and n - 1. Try again!")
        elif self.__service.graph.check_if_edge_exists(x, y):
            print("There is already an edge from " + str(x) + " to " + str(y))
        else:
            self.__service.graph.add_edge_to_graph(x, y, cost)
            print("The edge from " + str(x) +
                  " to " + str(y) + " has been added")

    def remove_edge(self):
        """
        Menu to remove an edge from the graph. If the graph is empty, operation can not be performed.
        """
        if self.__service.graph.get_number_of_vertices() == 0:
            print("First, you have to add vertices before you can remove an edge!")
            return
        try:
            x, y = input("Please enter the 2 vertices: ").split()
            x, y = int(x), int(y)
        except ValueError:
            print("Invalid input!")
            return
        if self.__service.graph.check_if_edge_exists(x, y):
            self.__service.graph.remove_edge_from_graph(x, y)
            print("The edge from " + str(x) + " to " +
                  str(y) + " has been removed!")
        else:
            print("There is no edge from " + str(x) + " to " + str(y))

    def add_vertex(self):
        """
        Menu to add a vertex to the graph. If the graph is empty, the user MUST provide the number of vertices first. In case the user adds a vertex that already exists, the operation will have no effect on the graph.
        """
        if self.__service.graph.get_number_of_vertices() == 0:
            try:
                v = int(
                    input("The graph is empty! Please provide the number of vertices first: "))
            except ValueError:
                print("Invalid input!")
                return
            self.__service.graph.set_number_of_vertices(v)
        try:
            v = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input!")
            return
        self.__service.graph.add_vertex_in_graph(v)
        print("Done!")

    def remove_vertex(self):
        """
        Menu to remove a vertex from the graph. No extra requirements.
        """
        try:
            v = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input!")
            return
        self.__service.graph.remove_vertex_from_graph(v)
        print("Done!")

    def copy_graph(self):
        """
        Function to copy the graph
        """
        copy_of_graph = self.__service.graph.get_copy_of_graph()
        print("Done!")

    def print_the_cost(self):
        """
        Function to print the cost of the graph
        """
        try:
            id = int(input("Please enter the id of the edge: "))
        except ValueError:
            print("Invalid input!")
            return
        print("The cost of the graph is " +
              str(self.__service.graph.get_cost_of_edge(id)))

    def read_graph_from_file(self):
        """
        User Interface for reading a graph from a file. The user has to provide the filename.
        """
        filename = input("Please enter the filename: ")
        self.__service.read_graph_from_file(filename)
        print("Done!")

    def write_graph_to_file(self):
        """
        User Interface for writing a graph to the file. The user has to provide the filename.
        """
        filename = input("Please enter the filename: ")
        self.__service.write_graph_to_file(filename)
        print("Done!")

    def generate_random_graph(self):
        """
        Function to generate a random graph. The user has to provide the number of vertices and edges.
        """
        try:
            n, m = input(
                "Please enter the number of vertices and edges: ").split()
            n, m = int(n), int(m)
        except ValueError:
            print("Invalid input!")
            return
        self.__service.generate_random_graph(n, m)
        print("Done!")

    def find_shortest_path(self):
        try:
            x, y = input("Please enter the 2 vertices: ").split()
            x, y = int(x), int(y)
        except ValueError:
            print("Invalid input!")
            return
        if x >= self.__service.graph.get_number_of_vertices() or y >= self.__service.graph.get_number_of_vertices():
            print("The provided vertices MUST BE between 0 and n - 1. Try again!")
            return
        path = self.__service.backwards_bfs(x, y)
        if len(path) == 0:
            print("There is no path from " + str(x) + " to " + str(y))
        else:
            print("The length of the shortest path is " + str(len(path) - 1))
            print("The shortest path from " +
                  str(x) + " to " + str(y) + " is: ")
            print(path)

    def print_strongly_connected_components(self):
        """
        Function to print the strongly connected components of the graph.
        """
        list_of_strongly_connected_components = self.__service.get_strongly_connected_components_of_the_graph()
        print("The number of strongly connected components is: " +
              str(len(list_of_strongly_connected_components)))
        print("The strongly connected components are: ")
        for component in list_of_strongly_connected_components:
            print(component)

    def print_biconnected_components(self):
        """
        Function to print the biconnected components of the graph.
        """
        list_of_biconnected_components = self.__service.get_biconnected_components_of_the_graph()
        print("The number of biconnected components is: " +
              str(len(list_of_biconnected_components)))
        print("The biconnected components are: ")
        for component in list_of_biconnected_components:
            print(component)

    def show_wolf_goat_cabbage(self):
        """
        Function to show the wolf-goat-cabbage problem.
        """
        solution = self.__service.solve_wolf_goat_cabbage_problem()
        for state in solution:
            print(state)

    def solve_15_puzzle(self):
        """
        Function to solve the 15 puzzle.
        """
        initial_list = ["1", "0", "2", "4", "5", "7", "3",
                        "8", "9", "6", "11", "12", "13", "10", "14", "15"]
        # print(
        #     "Provide numbers from 0 to 15, separated by space. 0 represents the empty tile.")

        # initial_list = []
        # for _ in range(16):
        #     tile = input("Please enter the tile: ")
        #     initial_list.append(tile)
        solution = puzzle.solve(initial_list)
        if solution is None:
            print("There is no solution!")
            return
        print("The solution is: ")
        for state in solution:
            if state.action == 'r':
                print("Move Right")
            elif state.action == 'l':
                print("Move Left")
            elif state.action == 'u':
                print("Move Up")
            elif state.action == 'd':
                print("Move Down")
            print(state)

    def print_menu(self):
        """
        Function to print the menu of the application. The user will choose an option from the menu.
        """
        print("Menu:")
        print("1. Get the number of vertices and edges")
        print("2. Print the graph in the console")
        print("3. Given 2 vertices, find out whether there is an edge from the first one to the second one")
        print("4. Get the in degree and out degree of a vertex")
        print("5. Parse the set of outbound edges of a vertex")
        print("6. Parse the set of inbound edges of a vertex")
        print("7. Get the endpoints of an edge (given its ID)")
        print("8. Modify the cost of an edge")
        print("9. Add an edge")
        print("10. Remove an edge")
        print("11. Add a vertex")
        print("12. Remove a vertex")
        print("13. Copy the graph")
        print("14. Read graph from file")
        print("15. Write graph to file")
        print("16. Generate random graph")
        print("17. Print vertices of graph")
        print("18. Print the cost of the edge")
        print("19. Find the shortest path between 2 vertices, using a backwards breadth-first search")
        print("20. Get the strongly connected components of the graph")
        print("21. Get the biconnected components of the graph")
        print("22. Solve the Wolf Goat Cabbage problem")
        print("23. Solve the 15 puzzle problem")
        print("24. Exit")

    def run(self):
        self.__service.solve_wolf_goat_cabbage_problem()
        """
        Main function that performs all the jobs
        """
        print("Welcome to the graph application!")
        while True:
            self.print_menu()
            command = input("Please enter a command: ")
            if command == "1":
                print("The number of vertices is: " +
                      str(self.__service.graph.get_number_of_vertices()))
                print("The number of edges is: " +
                      str(self.__service.graph.get_number_of_edges()))
            elif command == "2":
                self.print_graph()
            elif command == "3":
                self.check_if_edge_exists()
            elif command == "4":
                self.get_in_degree_and_out_degree()
            elif command == "5":
                self.parse_outbound_edges()
            elif command == "6":
                self.parse_inbound_edges()
            elif command == "7":
                self.get_endpoints_of_edge()
            elif command == "8":
                self.modify_cost_of_edge()
            elif command == "9":
                self.add_edge()
            elif command == "10":
                self.remove_edge()
            elif command == "11":
                self.add_vertex()
            elif command == "12":
                self.remove_vertex()
            elif command == "13":
                self.copy_graph()
            elif command == "14":
                self.read_graph_from_file()
            elif command == "15":
                self.write_graph_to_file()
            elif command == "16":
                self.generate_random_graph()
            elif command == "17":
                self.print_vertices()
            elif command == "18":
                self.print_the_cost()
            elif command == "19":
                self.find_shortest_path()
            elif command == "20":
                self.print_strongly_connected_components()
            elif command == "21":
                self.print_biconnected_components()
            elif command == "22":
                self.show_wolf_goat_cabbage()
            elif command == "23":
                self.solve_15_puzzle()
            elif command == "24":
                filename = "graph" + \
                    str(self.__service.graph.get_number_of_vertices()) + "_modif.txt"
                self.__service.write_graph_to_file(filename)
                print("Goodbye!")
                return
            else:
                print("Invalid command!. Please try again!")
