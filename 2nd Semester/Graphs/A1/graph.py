import copy


class Graph:
    def __init__(self, nr_of_vertices = 0, nr_of_edges = 0, type_of_read = 0):
        """
        :param nr_of_vertices: the number of vertices in the graph. Default value is 0
        :param nr_of_edges: the number of edges in the graph. Default value is 0
        :param type_of_read: indicates whether the file indicates the id of the edge, or not. Default value is 0
        
        Default constructor of our graph. It initializes the following fields:

        self.__type_of_read: indicates whether the file indicates the id of the edge, or not
        
        self.__nr_of_vertices: the number of vertices in the graph

        self.__nr_of_edges: the number of edges in the graph

        self.__in_edges: a dictionary that stores the inbound edges of a vertex

        self.__out_edges: a dictionary that stores the outbound edges of a vertex

        self.__edges_cost: a dictionary that stores the cost of an edge
         """
        self.__type_of_read = type_of_read
        self.__nr_of_vertices = nr_of_vertices
        self.__nr_of_edges = nr_of_edges
        self.__in_edges = {}
        self.__out_edges = {}
        self.__edges_cost = {}
        for vertex in range(nr_of_vertices):
            self.__in_edges[vertex] = {}
            self.__out_edges[vertex] = {}
    
    """Setters and getters for our function"""
    def set_number_of_vertices(self, nr_of_vertices):
        """
        :param nr_of_vertices: the number of vertices with which our graph will be updated

        Set value for the number of vertices in the graph
        """
        self.__nr_of_vertices = nr_of_vertices

    def set_number_of_edges(self, nr_of_edges):
        """
        :param nr_of_edges: the number of edges with which our graph will be updated

        Set value for the number of edges in the graph
        """
        self.__nr_of_edges = nr_of_edges

    def get_number_of_vertices(self):
        """:return: The number of vertices of our graph"""
        return self.__nr_of_vertices
    
    def get_number_of_edges(self):
        """
        :return:
        The number of edges of our graph"""
        return self.__nr_of_edges
    
    def get_set_of_vertices(self):
        """
        :return: 
        The set of vertices of our graph"""
        return set(self.__in_edges.keys())
    
    def get_in_degree(self, v):
        """
        :param v: the vertex for which we want to know the in degree
        :return: The in degree of a vertex v
        """
        return len(self.__in_edges[v])

    def get_out_degree(self, v):
        """
        :param v: the vertex for which we want to know the out degree

        :return: The out degree of a vertex v
        """
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
      if y in self.__out_edges[x]:
        return self.__out_edges[x][y]
      return -1
    
    def check_if_edge_exists(self, x, y):
        return self.__return_id_of_edge(x, y) != -1
    
    def get_copy_of_graph(self):
        return copy.deepcopy(self)
    
    def add_edge_to_graph(self, start_node, end_node, edge_id):
        self.__in_edges[end_node][start_node] = edge_id
        self.__out_edges[start_node][end_node] = edge_id
        self.__nr_of_edges += 1

    def read_graph_from_file(self, filename):
        file = open(filename, "r")
        v, e = file.readline().split()
        print(v, e);
        self.set_number_of_vertices(v)
        self.set_number_of_edges(e)
        for i in range(e):
            edge_id = i
            if self.__type_of_read == 0:
                start_node, end_node = file.readline().split()
            else:
                start_node, end_node, edge_id = file.readline().split()
            

  
