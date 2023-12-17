# # Define an empty dictionary to store the graph
# graph = {}

# # Define a list of vertices
# vertices = ['A', 'B', 'C', 'D']

# # Initialize for each vertex an empty list
# for vertex in vertices:
#     graph[vertex] = []

# edges = [('A', 'B'), ('B', 'C'), ('C', 'D'), ('D', 'A')]

# # Add edges to the graph
# for edge in edges:
#     v1, v2 = edge
#     graph[v1].append(v2)
#     graph[v2].append(v1)
  
# # Print the graph
# print(graph)

graph = []
for i in range(5):
    graph.append([])

graph[1].append(2)
graph[1].append(3)
graph[2].append(3)
graph[3].append(4)

for node in range(1, 5):
    print(node, " -> ", graph[node])