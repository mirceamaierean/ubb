import copy


class Graph:
    def __init__(self, nr_of_vertices=0):
        """
        :param nr_of_vertices: the number of vertices in the graph. Default value is 0

        Default constructor of our graph. It initializes the following fields:

        self.__nr_of_vertices: the number of vertices in the graph

        self.__nr_of_edges: the number of edges in the graph

        self.__in_edges: a dictionary that stores the inbound edges of a vertex

        self.__out_edges: a dictionary that stores the outbound edges of a vertex

        self.__edges_cost: a dictionary that stores the cost of an edge
         """
        self.__nr_of_vertices = nr_of_vertices
        self.__nr_of_edges = 0
        self.__in_edges = {}
        self.__out_edges = {}
        self.__edges_cost = {}

    """Setters and getters for our functions"""

    def set_number_of_vertices(self, nr_of_vertices):
        """
        :param nr_of_vertices: the number of vertices with which our graph will be updated

        Set value for the number of vertices in the graph
        """
        self.__nr_of_vertices = nr_of_vertices

    def get_number_of_vertices(self):
        """:return: The number of vertices of our graph"""
        return self.__nr_of_vertices

    def get_set_of_vertices(self):
        """
        :return: 
        The set of vertices of our graph"""
        return set(self.__in_edges.keys())

    def set_number_of_edges(self, nr_of_edges):
        """
        :param nr_of_edges: the number of edges with which our graph will be updated

        Set value for the number of edges in the graph
        """
        self.__nr_of_edges = nr_of_edges

    def get_endpoints_of_edge(self, edge_id):
        """
        :param edge_id: the id of the edge for which we want to retrieve the endpoints

        We iterate through the outbound edges of each vertex and check if the edge_id is the same as the one we are looking for.
        ...

        :return: a tuple (x, y) where x is the start node and y is the end node of the edge, or (-1, -1) if the edge does not exist

        """
        for x in self.__out_edges:
            for y in self.__out_edges[x]:
                if self.__out_edges[x][y] == edge_id:
                    return x, y
        return -1, -1

    def return_id_of_edge(self, x, y):
        """
        :param x: the start node of the edge
        :param y: the end node of the edge
        :return: the id of the edge (x, y) if it exists, -1 otherwise
        """
        if x in self.__out_edges and y in self.__out_edges[x]:
            return self.__out_edges[x][y]
        return -1

    def get_number_of_edges(self):
        """
        :return:
        The number of edges of our graph"""
        return self.__nr_of_edges

    def get_out_edges(self):
        """
        :return:
        The outbound edges of our graph"""
        return dict(sorted(self.__out_edges.items()))

    def get_in_edges(self):
        """
        :return:
        The inbound edges of our graph"""
        return dict(sorted(self.__in_edges.items()))

    def get_in_degree(self, v):
        """
        :param v: the vertex for which we want to know the in degree
        :return: The in degree of a vertex v
        """
        if v in self.__in_edges:
            return len(self.__in_edges[v])

    def get_out_degree(self, v):
        """
        :param v: the vertex for which we want to know the out degree

        :return: The out degree of a vertex v
        """
        if v in self.__out_edges:
            return len(self.__out_edges[v])

    def get_outbound_neighbours(self, v):
        """
        :param v: the vertex for which we want to retrieve the outbound neighbours

        :return:
        Since we store the inbound neighbours of a vertex in a dictionary, we simply have to return the set of keys
        """
        return set(self.__out_edges[v].keys())

    def get_inbound_neighbours(self, v):
        """
        :param v: the vertex for which we want to retrieve the inbound neighbours

        :return:
        Since we store the inbound neighbours of a vertex in a dictionary, we simply have to return the set of keys
        """
        return set(self.__in_edges[v].keys())

    def get_cost_of_edge(self, edge_id):
        """
        :param edge_id: the id of the edge for which we want to retrieve the cost

        :return: The cost of the edge with the given id
        """
        return self.__edges_cost[edge_id]

    def modify_cost_of_edge(self, edge_id, cost):
        """
        :param edge_id: the id of the edge for which we want to set the cost
        :param cost: the cost of the edge
        """
        self.__edges_cost[edge_id] = cost

    def check_if_edge_exists(self, x, y):
        """
        :param x: the start node of the edge
        :param y: the end node of the edge
        :return: True if the edge (x, y) exists, False otherwise

        In order to check if an edge exists, we simply call the function return_id_of_edge and check if it returns -1 or not
        """
        return self.return_id_of_edge(x, y) != -1

    def add_vertex_in_graph(self, v):
        """
        :param v: the vertex we have to add to the grap
        """
        if not v in self.__in_edges:
            self.__in_edges[v] = {}
            self.__out_edges[v] = {}

    def remove_vertex_from_graph(self, v):
        """
        :param v: the vertex we have to remove from the graph
        """
        if v in self.__in_edges:
            self.__nr_of_vertices -= 1
            self.__nr_of_edges -= len(self.__in_edges[v]) + \
                len(self.__out_edges[v])
            for x in self.__in_edges[v]:
                del self.__edges_cost[self.__in_edges[v][x]]
                del self.__out_edges[x][v]
            for x in self.__out_edges[v]:
                del self.__edges_cost[self.__out_edges[v][x]]
                del self.__in_edges[x][v]
            del self.__in_edges[v]
            del self.__out_edges[v]

    def add_edge_to_graph(self, start_node, end_node, cost):
        """
        :param start_node: the start node of the edge
        :param end_node: the end node of the edge
        :param edge_id: the id of the edge
        """
        self.add_vertex_in_graph(start_node)
        self.add_vertex_in_graph(end_node)
        self.__in_edges[end_node][start_node] = self.__nr_of_edges
        self.__out_edges[start_node][end_node] = self.__nr_of_edges
        self.__edges_cost[self.__out_edges[start_node][end_node]] = cost
        self.__nr_of_edges += 1

    def remove_edge_from_graph(self, start_node, end_node):
        """
        :param start_node: the start node of the edge
        :param end_node: the end node of the edge
        """
        if self.check_if_edge_exists(start_node, end_node):
            del self.__edges_cost[self.__out_edges[start_node][end_node]]
            del self.__out_edges[start_node][end_node]
            del self.__in_edges[end_node][start_node]
            self.__nr_of_edges -= 1

    def get_copy_of_graph(self):
        """
        Function that returns a copy of the graph

        :return: a copy of the graph
        """
        g = Graph(self.__nr_of_vertices)
        g.__in_edges = copy.deepcopy(self.__in_edges)
        g.__out_edges = copy.deepcopy(self.__out_edges)
        g.__edges_cost = copy.deepcopy(self.__edges_cost)
        return g

    def set_cost_on_edge(self, edge_id, cost):
        """
        :param edge_id: the id of the edge for which we want to set the cost
        :param cost: the cost of the edge
        """
        self.__edges_cost[edge_id] = cost
