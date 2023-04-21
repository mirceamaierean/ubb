from graph import Graph
from random import randint


class Service:
    def __init__(self):
        """
        Default constructor of our service. It initializes the following fields:

        self.graph: the graph that we will use for our algorithms
        """
        self.graph = Graph()

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

    def backwards_bfs(self, start_node, end_node):
        """
        This function finds the shortest path between two nodes in a directed graphs, using a backwards breadth-first search, starting from the end node
        :param start_node: the start node
        :param end_node: the end node
        :return: the shortest path between the two nodes
        """
        # We will use a queue to store the nodes that we will visit. For each node, we will store the parent of that node, and also if we have visited that node or not
        visited = [False] * self.graph.get_number_of_vertices()
        queue = []
        exists_a_path = False
        queue.append(end_node)
        visited[end_node] = True
        parent = [None] * self.graph.get_number_of_vertices()
        # As long as the queue has elements, or the node is not the one we have to find, we will continue
        while queue:
            # We pop the first element of the queue
            node = queue.pop(0)
            # If we have found the node, we will break the loop
            if node == start_node:
                exists_a_path = True
                break
            # We will add the neighbours of the node to the queue, if they have not been visited yet
            for neighbour in self.graph.get_in_edges()[node]:
                if not visited[neighbour]:
                    queue.append(neighbour)
                    visited[neighbour] = True
                    parent[neighbour] = node
        # If there is no path between the two nodes, we will return an empty list
        if exists_a_path == False:
            return []
        # We will reconstruct the path from the start node to the end node
        path = []
        node = start_node
        # We will add the nodes to the path, until we reach the end node. We go down the tree, at each step the new node will be the father of the previous node
        while node != end_node:
            path.append(node)
            node = parent[node]
        # We add the end node to the path
        path.append(end_node)
        return path
