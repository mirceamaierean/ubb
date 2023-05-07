#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Graph
{
private:
  int v, e;
  map<int, vector<pair<int, int>>> in_edges;
  map<int, vector<pair<int, int>>> out_edges;
  map<int, int> cost;

public:
  Graph(int v = 0, int e = 0)
  {
    this->v = v;
    this->e = e;
  }
  ~Graph()
  {
  }
  void setNumberOfVertices(int v)
  {
    this->v = v;
  }
  void setNumberOfEdges(int e)
  {
    this->e = e;
  }
  int getNumberOfVertices()
  {
    return this->v;
  }
  int getNumberOfEdges()
  {
    return this->e;
  }
  pair<int, int> getEndpointsOfEdge(int edge)
  {
    for (auto it : out_edges)
      for (auto it2 : it.second)
        if (it2.second == edge)
          return make_pair(it.first, it2.first);
    return make_pair(-1, -1);
  }
  vector<int> getVerticesOfgraph()
  {
    vector<int> vertices;
    for (auto it : out_edges)
      vertices.push_back(it.first);
    return vertices;
  }
  int getIdOfEdge(int u, int v)
  {
    for (auto it : out_edges[u])
      if (it.first == v)
        return it.second;
    return -1;
  }
  bool checkIfEdgeExists(int u, int v)
  {
    return this->getIdOfEdge(u, v) != -1;
  }
  int getInDegreeOfVertex(int v)
  {
    return in_edges[v].size();
  }
  int getOutDegreeOfVertex(int v)
  {
    return out_edges[v].size();
  }
  vector<pair<int, int>> getInEdgesOfVertex(int v)
  {
    return in_edges[v];
  }
  vector<pair<int, int>> getOutEdgesOfVertex(int v)
  {
    return out_edges[v];
  }
  void setCostOfEdge(int u, int v, int cost)
  {
    if (this->checkIfEdgeExists(u, v))
    {
      int id = this->getIdOfEdge(u, v);
      this->cost[id] = cost;
    }
  }
  int getCostOfEdge(int u, int v)
  {
    if (this->checkIfEdgeExists(u, v))
    {
      int id = this->getIdOfEdge(u, v);
      return this->cost[id];
    }
    return -1;
  }
  Graph getCopyOfGraph()
  {
    Graph g(this->v, this->e);
    g.in_edges = this->in_edges;
    g.out_edges = this->out_edges;
    g.cost = this->cost;
    return g;
  }
  void addEdge(int u, int v, int cost)
  {
    if (this->checkIfEdgeExists(u, v))
      return;
    int id = this->e;
    ++this->e;
    this->out_edges[u].push_back(make_pair(v, id));
    this->in_edges[v].push_back(make_pair(u, id));
    this->cost[id] = cost;
  }
  void removeEdge(int u, int v)
  {
    if (!this->checkIfEdgeExists(u, v))
      return;
    int id = this->getIdOfEdge(u, v);
    this->out_edges[u].erase(remove_if(this->out_edges[u].begin(), this->out_edges[u].end(), [id](pair<int, int> p)
                                       { return p.second == id; }),
                             this->out_edges[u].end());
    this->in_edges[v].erase(remove_if(this->in_edges[v].begin(), this->in_edges[v].end(), [id](pair<int, int> p)
                                      { return p.second == id; }),
                            this->in_edges[v].end());
    this->cost.erase(id);
    --this->e;
  }
  void addVertex(int v)
  {
    if (this->out_edges.find(v) != this->out_edges.end())
      return;
    ++this->v;
    this->out_edges[v] = vector<pair<int, int>>();
    this->in_edges[v] = vector<pair<int, int>>();
  }
  void removeVertex(int v)
  {
    if (this->out_edges.find(v) == this->out_edges.end())
      return;
    for (auto it : this->out_edges[v])
      this->removeEdge(v, it.first);
    for (auto it : this->in_edges[v])
      this->removeEdge(it.first, v);
    this->out_edges.erase(v);
    this->in_edges.erase(v);
    --this->v;
  }
  void generateRandomGraph(int v, int e)
  {
    this->v = v;
    this->e = e;
    for (int i = 0; i < v; ++i)
      this->addVertex(i);
    for (int i = 0; i < e; ++i)
    {
      int u = rand() % v;
      int v = rand() % v;
      int cost = rand() % 100;
      this->addEdge(u, v, cost);
    }
  }
};

ifstream fin("graph1k.in");
ofstream fout("graph1k.out");

class UI
{
private:
  Graph g;

public:
  UI()
  {
  }
  ~UI()
  {
  }
  void printTheNumberOfVertices()
  {
    cout << "The Number of Vertices is " << g.getNumberOfVertices() << '\n';
  }
  void printTheNumberOfEdges()
  {
    cout << "The Number of Edges is " << g.getNumberOfEdges() << "\n";
  }
  void printTheVerticesOfGraphOnScreen()
  {
    cout << "The Vertices of the Graph are: ";
    vector<int> vertices = g.getVerticesOfgraph();
    for (auto it : vertices)
      cout << it << " ";
    cout << endl;
  }
  void printTheEdgesOfGraphOnScreen()
  {
    cout << "The Edges of the Graph are: " << endl;
    vector<int> vertices = g.getVerticesOfgraph();
    for (auto it : vertices)
    {
      vector<pair<int, int>> edges = g.getOutEdgesOfVertex(it);
      for (auto it2 : edges)
        cout << it << " " << it2.first << " " << g.getCostOfEdge(it, it2.first) << endl;
    }
  }
  void readGraphFromFile()
  {
    int v, e;
    fin >> v >> e;
    for (int i = 0; i < v; ++i)
      g.addVertex(i);
    for (int i = 0; i < e; ++i)
    {
      int u, v, cost;
      fin >> u >> v >> cost;
      g.addEdge(u, v, cost);
    }
    cout << "Graph read from file successfully! " << endl;
  }
  void writeGraphToFile()
  {
    fout << g.getNumberOfVertices() << " " << g.getNumberOfEdges() << endl;
    vector<int> vertices = g.getVerticesOfgraph();
    for (auto it : vertices)
    {
      vector<pair<int, int>> edges = g.getOutEdgesOfVertex(it);
      for (auto it2 : edges)
        fout << it << " " << it2.first << " " << g.getCostOfEdge(it, it2.first) << endl;
    }
    cout << "Graph written to file successfully" << endl;
  }
  void printIdOfEdge()
  {
    int u, v;
    cout << "Enter the two vertices of the edge" << endl;
    cin >> u >> v;
    int idOfEdge = g.getIdOfEdge(u, v);
    if (idOfEdge == -1)
      cout << "Edge does not exist" << endl;
    else
      cout << "The id of the edge is " << idOfEdge << endl;
  }
  void printInDegreeAndOutDegreeOfVertex()
  {
    cout << "Which vertex do you want to check?" << endl;
    int v;
    cin >> v;
    cout << "In degree of vertex " << v << " is " << g.getInDegreeOfVertex(v) << endl;
    cout << "Out degree of vertex " << v << " is " << g.getOutDegreeOfVertex(v) << endl;
  }
  void printTheOutboundEdgesOfVertex()
  {
    cout << "Which vertex do you want to check?" << endl;
    int v;
    cin >> v;
    vector<pair<int, int>> edges = g.getOutEdgesOfVertex(v);
    if (edges.size() == 0)
    {
      cout << "There are no outbound edges to the vertex!" << endl;
      return;
    }
    cout << "The outbound edges of vertex " << v << " are: " << endl;
    for (auto it : edges)
      cout << v << " " << it.first << " " << g.getCostOfEdge(v, it.first) << endl;
  }
  void printTheInboundEdgesOfVertex()
  {
    cout << "Which vertex do you want to check?" << endl;
    int v;
    cin >> v;
    vector<pair<int, int>> edges = g.getInEdgesOfVertex(v);
    if (edges.size() == 0)
    {
      cout << "There are no inbound edges to the vertex!" << endl;
      return;
    }
    cout << "The inbound edges of vertex " << v << " are: " << endl;
    for (auto it : edges)
      cout << it.first << " " << v << " " << g.getCostOfEdge(it.first, v) << endl;
  }
  void printTheCostOfEdge()
  {
    cout << "Enter the two vertices of the edge" << endl;
    int u, v;
    cin >> u >> v;
    int cost = g.getCostOfEdge(u, v);
    if (cost == -1)
      cout << "Edge does not exist" << endl;
    else
      cout << "The cost of the edge is " << cost << endl;
  }
  void printTheEndpointsOfAnEdge()
  {
    cout << "Enter the id of the edge" << endl;
    int id;
    cin >> id;
    pair<int, int> endpoints = g.getEndpointsOfEdge(id);
    if (endpoints.first == -1)
      cout << "Edge does not exist" << endl;
    else
      cout << "The endpoints of the edge are " << endpoints.first << " " << endpoints.second << endl;
  }
  void addEdge()
  {
    cout << "Enter the two vertices of the edge and the cost" << endl;
    int u, v, cost;
    cin >> u >> v >> cost;
    g.addEdge(u, v, cost);
  }
  void removeEdge()
  {
    cout << "Enter the two vertices of the edge" << endl;
    int u, v;
    cin >> u >> v;
    g.removeEdge(u, v);
  }
  void addVertex()
  {
    cout << "Enter the id of the vertex" << endl;
    int v, n = g.getNumberOfVertices();
    cin >> v;
    if (n == 0)
    {
      cout << "The graph is empty. You have to set a dimension first" << endl;
      int n;
      cin >> n;
      g.setNumberOfVertices(n);
    }
    if (v < 0 || v >= n + 1)
    {
      cout << "Invalid vertex" << endl;
      return;
    }
    g.addVertex(v);
  }
  void removeVertex()
  {
    cout << "Enter the id of the vertex" << endl;
    int v, n = g.getNumberOfVertices();
    cin >> v;
    if (n == 0)
    {
      cout << "The graph is empty. There is nothing to remove" << endl;
      return;
    }
    if (v < 0 || v >= n)
    {
      cout << "Invalid vertex" << endl;
      return;
    }
    g.removeVertex(v);
  }
  void printMenuOfOptions()
  {
    cout << "1. Print the number of vertices" << endl;
    cout << "2. Print the number of edges" << endl;
    cout << "3. Print the vertices of the graph" << endl;
    cout << "4. Print the edges of the graph" << endl;
    cout << "5. Read the graph from a file" << endl;
    cout << "6. Write the graph to a file" << endl;
    cout << "7. Print the id of an edge" << endl;
    cout << "8. Print the in degree and out degree of a vertex" << endl;
    cout << "9. Print the outbound edges of a vertex" << endl;
    cout << "10. Print the inbound edges of a vertex" << endl;
    cout << "11. Print the cost of an edge" << endl;
    cout << "12. Print the endpoints of an edge" << endl;
    cout << "13. Add an edge" << endl;
    cout << "14. Remove an edge" << endl;
    cout << "15. Add a vertex" << endl;
    cout << "16. Remove a vertex" << endl;
    cout << "17. Exit" << endl;
  }
};
int main()
{
  UI ui;
  while (1)
  {
    ui.printMenuOfOptions();
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
      ui.printTheNumberOfVertices();
      break;
    case 2:
      ui.printTheNumberOfEdges();
      break;
    case 3:
      ui.printTheVerticesOfGraphOnScreen();
      break;
    case 4:
      ui.printTheEdgesOfGraphOnScreen();
      break;
    case 5:
      ui.readGraphFromFile();
      break;
    case 6:
      ui.writeGraphToFile();
      break;
    case 7:
      ui.printIdOfEdge();
      break;
    case 8:
      ui.printInDegreeAndOutDegreeOfVertex();
      break;
    case 9:
      ui.printTheOutboundEdgesOfVertex();
      break;
    case 10:
      ui.printTheInboundEdgesOfVertex();
      break;
    case 11:
      ui.printTheCostOfEdge();
      break;
    case 12:
      ui.printTheEndpointsOfAnEdge();
      break;
    case 13:
      ui.addEdge();
      break;
    case 14:
      ui.removeEdge();
      break;
    case 15:
      ui.addVertex();
      break;
    case 16:
      ui.removeVertex();
      break;
    case 17:
      cout << "Goodbye!" << endl;
      return 0;
    default:
      cout << "Invalid option" << endl;
    }
  }
  return 0;
}