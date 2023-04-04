from graph import Graph

dict = {}
x = 2
y = 3
dict[x] = {}
dict[x][y] = (1, 2);
print(dict[x][y][1]);

g = Graph()

g.read_graph_from_file("file.txt");