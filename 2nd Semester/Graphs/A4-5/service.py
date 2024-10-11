from graph import Graph
from random import randint
from queue import PriorityQueue


class Service:
    def __init__(self):
        """
        Default constructor of our service. It initializes the following fields:

        self.graph: the graph that we will use for our algorithms
        """
        self.graph = Graph()
        self.__visited = []

    def read_graph_from_file(self, filename):
        """
        :param filename: the name of the file from which we want to read the graph

        This function reads line by line the content of the file and adds the edges to the graph
        """
        file = open(filename, "r")
        v, e = file.readline().split()
        v, e = int(v), int(e)
        self.graph = Graph(v)
        for i in range(e):
            edge_id = i
            cost = 0
            start_node, end_node, cost = file.readline().split()
            start_node, end_node, cost = int(
                start_node), int(end_node), int(cost)
            self.graph.add_edge_to_graph(start_node, end_node, cost)

    def read_graph_from_file_directed(self, filename):
        """
        :param filename: the name of the file from which we want to read the graph

        This function reads line by line the content of the file and adds the edges to the graph
        """
        file = open(filename, "r")
        v, e = file.readline().split()
        v, e = int(v), int(e)
        self.graph = Graph(v)
        for i in range(e):
            edge_id = i
            cost = 0
            start_node, end_node, cost = file.readline().split()
            start_node, end_node, cost = int(
                start_node), int(end_node), int(cost)
            self.graph.add_edge_directed(start_node, end_node, cost)

    def write_graph_to_file(self, filename):
        """
        :param filename: the name of the file to which we want to write the graph

        This function writes the graph to a file
        """
        file = open(filename, "w")
        file.write(str(self.graph.get_number_of_vertices()) +
                   " " + str(self.graph.get_number_of_edges()) + "\n")
        out_edges = self.graph.get_out_edges()
        for x in out_edges:
            for y in out_edges[x]:
                file.write(str(x) + " " + str(y) + " " +
                           str(self.graph.get_cost_of_edge(out_edges[x][y])) + "\n")

    def generate_random_graph(self, nr_of_vertices, nr_of_edges):
        """
        This function generates a random graph
        :param nr_of_vertices: the number of vertices of the graph
        :param nr_of_edges: the number of edges of the graph
        """
        self.graph = Graph(nr_of_vertices)
        for i in range(nr_of_edges):
            start_node = randint(0, nr_of_vertices - 1)
            end_node = randint(0, nr_of_vertices - 1)
            while self.graph.check_if_edge_exists(start_node, end_node):
                start_node = randint(0, nr_of_vertices - 1)
                end_node = randint(0, nr_of_vertices - 1)
            self.graph.add_vertex_in_graph(start_node)
            self.graph.add_vertex_in_graph(end_node)
            self.graph.add_edge_to_graph(start_node, end_node, i)
            self.graph.set_cost_on_edge(i, randint(1, 100) - 50)

    def find_minimum_spanning_tree_using_prim(self, start_node):
        """
        :param start_node: the node from which we want to start our search

        This function finds the minimum spanning tree of the graph using Prim's algorithm
        """
        dad = [-1] * self.graph.get_number_of_vertices()
        dad[start_node] = start_node

        q = PriorityQueue()
        q.put((0, start_node, start_node))

        minimum_cost = 0

        for i in range(self.graph.get_number_of_vertices()):
            current_pair = ()
            while not q.empty():
                current_pair = q.get()
                if dad[current_pair[1]] == -1:
                    break
            current_node = current_pair[1]
            dad[current_node] = current_pair[2]
            minimum_cost += current_pair[0]
            for neighbour in self.graph.get_out_edges()[current_node]:
                if dad[neighbour] == -1:
                    q.put((self.graph.get_cost_of_edge(
                        self.graph.get_out_edges()[current_node][neighbour]), neighbour, current_node))

        return minimum_cost, dad

    def dfs_dag(self, node, topological_order, previous_nodes, is_dag):
        """
        :param start_node: the node from which we want to start our search
        :param visited: the list of visited nodes
        :param topological_order: the topological order of the nodes

        This function does a dfs on a directed acyclic graph
        """
        self.__visited[node] = True
        previous_nodes.append(node)
        for neighbour in self.graph.get_out_edges()[node]:
            if not self.__visited[neighbour]:
                self.dfs_dag(neighbour, topological_order,
                             previous_nodes, is_dag)
            else:
                if neighbour in previous_nodes:
                    is_dag[0] = False
        topological_order.append(node)
        previous_nodes.pop()

    def check_if_graph_is_dag(self):
        """
        This function checks if the graph is a directed acyclic graph
        """
        self.__visited = [False] * self.graph.get_number_of_vertices()
        topological_order = []
        previous_nodes = []
        is_dag = [True]
        for node in range(self.graph.get_number_of_vertices()):
            if not self.__visited[node]:
                self.dfs_dag(node, topological_order, previous_nodes, is_dag)
                if not is_dag[0]:
                    return False, []
        return is_dag[0], topological_order

    def find_number_of_walks_between_two_vertices(self, start_node, end_node):
        topological_order = self.check_if_graph_is_dag()

        if not topological_order[0]:
            return - 1

        topological_order = topological_order[1]

        dp = [0] * self.graph.get_number_of_vertices()
        edges = self.graph.get_out_edges()
        dp[end_node] = 1
        for node in topological_order:
            for neighbour in edges[node]:
                dp[node] += dp[neighbour]

        return dp[start_node]

    def find_minimum_cost_between_two_vertices_in_dag(self, start_node, end_node):
        topological_order = self.check_if_graph_is_dag()

        if not topological_order[0]:
            return -1

        topological_order = topological_order[1]

        dp = [float("inf")] * self.graph.get_number_of_vertices()
        dp[end_node] = 0

        for node in topological_order:
            for neighbour in self.graph.get_in_edges()[node]:
                dp[neighbour] = min(dp[neighbour], dp[node] + self.graph.get_cost_of_edge(
                    self.graph.get_in_edges()[node][neighbour]))

        return dp[start_node]

    def hamiltonian_cycle(self, node):
        """
        :param node: the node from which we want to start our search

        This function finds a hamiltonian cycle in the graph
        """
        if len(self.__cycle) == self.graph.get_number_of_vertices() and self.graph.check_if_edge_exists(node, self.__cycle[0]):
            return True
        for neighbour in self.graph.get_out_edges()[node]:
            if not self.__visited[neighbour]:
                self.__visited[neighbour] = True
                self.__cycle.append(neighbour)
                if self.hamiltonian_cycle(neighbour):
                    return True
                self.__visited[neighbour] = False
                self.__cycle.pop()
        return False

    def find_hamiltonian_cycle(self):
        """
        This function finds a hamiltonian cycle in the graph
        """
        self.__visited = [False] * self.graph.get_number_of_vertices()
        self.__cycle = []
        self.__cycle.append(0)
        self.__visited[0] = True
        result = self.hamiltonian_cycle(0)
        if result:
            return self.__cycle
        return []
