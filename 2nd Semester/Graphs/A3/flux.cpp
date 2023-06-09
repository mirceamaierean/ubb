#include <fstream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

const int NMAX = 1e3 + 2;

vector<int> g[NMAX];
bitset<NMAX> used;

int c[NMAX][NMAX], t[NMAX], n, m, x, y;

bool BFS()
{
  used.reset();

  queue<int> q;

  q.push(1);
  used[1] = 1;

  while (!q.empty())
  {
    x = q.front();
    q.pop();
    if (x == n)
      continue;
    for (auto i : g[x])
      if (used[i] == 0 && c[x][i] > 0)
      {
        used[i] = 1;
        q.push(i);
        t[i] = x;
      }
  }
  return used[n];
}

int maxflow()
{
  int maxflow = 0;
  while (BFS())
    for (auto i : g[n])
    {
      if (!used[i] || c[i][n] <= 0)
        continue;

      int e = 0x3f3f3f3f;
      t[n] = i;

      for (int j = n; j != 1; j = t[j])
        e = min(e, c[t[j]][j]);

      if (!e)
        continue;

      for (int j = n; j != 1; j = t[j])
      {
        c[t[j]][j] -= e;
        c[j][t[j]] += e;
      }
      maxflow += e;
    }
  return maxflow;
}

int main()
{
  fin >> n >> m;
  for (int i = 1; i <= m; ++i)
  {
    fin >> x >> y;
    fin >> c[x][y];
    g[x].push_back(y);
    g[y].push_back(x);
  }
  fout << maxflow() << '\n';
  return 0;
}