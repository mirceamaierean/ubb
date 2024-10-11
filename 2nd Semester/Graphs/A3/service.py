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
        self.topological_sorting = []
        self.visited = []
        self.dp = [[-1 for _ in range(2)] for _ in range(1 << 20)]
        self.people = []

    def read_graph_from_file(self, filename):
        """
        :param filename: the name of the file from which we want to read the graph

        This function reads line by line the content of the file and adds the edges to the graph
        """
        file = open(filename, "r")
        v, e = file.readline().split()
        v, e = int(v), int(e)
        self.graph = Graph(v)
        for _ in range(e):
            cost = 0
            start_node, end_node, cost = file.readline().split()
            start_node, end_node, cost = int(
                start_node), int(end_node), int(cost)
            self.graph.add_edge_to_graph(start_node, end_node, cost)

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

    def DFS(self, node):
        """
        DFS on outbound edges, for finding the strongly connected components of the graph
        """
        self.visited[node] = True
        for neighbour in self.graph.get_out_edges()[node]:
            if self.visited[neighbour] == False:
                self.DFS(neighbour)
        self.topological_sorting.append(node)

    def find_minimum_cost_walk(self, start_node, end_node):
        """
        This function finds the minimum cost walk from a start node to an end node
        :param start_node: the start node
        :param end_node: the end node
        :return: the minimum cost walk
        """
        q = PriorityQueue()
        q.put((0, start_node, -1))
        visited = [False] * self.graph.get_number_of_vertices()
        minimum_cost = [float("inf")] * self.graph.get_number_of_vertices()
        minimum_cost[start_node] = 0
        parent = [-1] * self.graph.get_number_of_vertices()
        out_edges = self.graph.get_out_edges()
        while not q.empty():
            current_pair = q.get()
            current_node = current_pair[1]
            if visited[current_node]:
                continue
            visited[current_node] = True
            minimum_cost[current_node] = current_pair[0]
            parent[current_node] = current_pair[2]
            if current_node == end_node:
                break
            for x in out_edges[current_node]:
                if not visited[x]:
                    q.put((minimum_cost[current_node] +
                           self.graph.get_cost_of_edge(out_edges[current_node][x]), x, current_node))
        if minimum_cost[end_node] == float("inf"):
            return None, None
        minimum_cost_walk = []
        current_node = end_node
        while current_node != -1:
            minimum_cost_walk.append(current_node)
            current_node = parent[current_node]
        minimum_cost_walk.reverse()
        return minimum_cost_walk, minimum_cost[end_node]

    def find_number_of_walks_with_minimum_cost(self, start_node, end_node):
        """
        This function finds the number of walks with minimum cost from a start node to an end node
        :param star_node: the start node
        :param end_node: the end node
        :return: the number of walks with minimum cost
        """
        path, minimum_cost = self.find_minimum_cost_walk(
            start_node, end_node)
        
        if path is None:
            return None
        
        q = PriorityQueue()
        
        q.put((0, start_node, -1))
        
        visited = [False] * self.graph.get_number_of_vertices()
        number_of_walks = [0] * self.graph.get_number_of_vertices()
        minimum_cost_walk = [float("inf")] * \
            self.graph.get_number_of_vertices()
        
        number_of_walks[start_node] = 1
        minimum_cost_walk[start_node] = 0
        out_edges = self.graph.get_out_edges()

        while not q.empty():
            current_pair = q.get()
            current_node = current_pair[1]
            # If the current cost is greater than the minimum cost of the walk, we stop, because we won't find a cheaper walk
            if current_pair[0] > minimum_cost:
                break
            if visited[current_node]:
                if minimum_cost_walk[current_node] == current_pair[0]:
                    number_of_walks[current_node] += number_of_walks[current_pair[2]]
                continue
            visited[current_node] = True
            minimum_cost_walk[current_node] = current_pair[0]
            if current_pair[2] != -1:
                number_of_walks[current_node] = number_of_walks[current_pair[2]]
            for x in out_edges[current_node]:
                if not visited[x]:
                    q.put((minimum_cost_walk[current_node] +
                           self.graph.get_cost_of_edge(out_edges[current_node][x]), x, current_node))

        return number_of_walks[end_node]

    def find_number_of_walks_between_two_vertices(self, start_node, end_node):
        self.visited = [False] * self.graph.get_number_of_vertices()
        self.topological_sorting = []
        self.DFS(start_node)
        dp = [0] * self.graph.get_number_of_vertices()
        edges = self.graph.get_out_edges()
        dp[end_node] = 1
        for node in self.topological_sorting:
            for neighbour in edges[node]:
                dp[node] += dp[neighbour]
        return dp[start_node]

    def count_number_of_set_bits(self, mask):
        """
        This function counts the number of set bits in a mask
        :param mask: the mask
        :return: the number of set bits in the mask
        """
        cnt = 0
        while mask:
            cnt += mask & 1
            mask >>= 1
        return cnt

    def find_min_time_for_transfer(self, leftmask, turn, n):
        """
        This function finds the minimum time for transfer for a given mask and turn
        :param mask: the mask
        :param turn: the turn
        :return: the minimum time for transfer
        """
        if leftmask == 0:
            return 0

        res = self.dp[leftmask][turn]

        if ~res:
            return res

        rightmask = ((1 << n) - 1) ^ leftmask

        if turn:
            minRow = float("inf")
            person = 0

            for i in range(n):
                if rightmask & (1 << i):
                    if minRow > self.people[i]:
                        minRow = self.people[i]
                        person = i

            res = self.people[person] + self.find_min_time_for_transfer(
                leftmask | (1 << person), turn ^ 1, n)

        else:
            if self.count_number_of_set_bits(leftmask) == 1:
                for i in range(n):
                    if leftmask & (1 << i):
                        res = self.people[i]
                        break
            else:
                res = float('inf')
                for i in range(n):
                    if leftmask & (1 << i):
                        for j in range(i + 1, n):
                            if leftmask & (1 << j):
                                res = min(res, max(self.people[i], self.people[j]) + self.find_min_time_for_transfer(
                                    leftmask ^ (1 << i) ^ (1 << j), turn ^ 1, n))

        return res

    def find_minimum_time_for_transfer(self, people, n):
        self.people = people
        self.dp = [[-1 for i in range(2)] for j in range(1 << n)]
        mask = (1 << n) - 1
        return self.find_min_time_for_transfer(mask, 0, n)
