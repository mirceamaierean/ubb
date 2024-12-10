#include <fstream>
#include <deque>
#include <vector>
using namespace std;

ifstream fin("p3.in");
ofstream fout("p3.out");

// A = {a1, a2, a3, ... , an}

// cnt = number of associative elements for a set with n elements
// a[][] = a matrix in which we store our operation table
// In our matrixes, we store only the index of the element for the set
// e.g. a[x][y] = 1, then in a[x][y] we have a1
int cnt, n, a[10][10];

// An opperation is associative if, for any x, y, z from s, (x * y) * x = x * y * z
// Writing this for our matrix, we get that a[a[x][y]][z] = a[x][a[y][z]]
// We check for each (x, y, z) belongign to A x A x A

bool check()
{
  bool ok = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n; ++k)
        ok &= (a[a[i][j]][k] == a[i][a[j][k]]);
  return ok;
}

// In this function, we print our matrix

void print_solution()
{
  for (int i = 1; i <= n; ++i, fout << '\n')
  {
    fout << "(a" << a[i][1];
    for (int j = 2; j <= n; ++j)
      fout << ", a" << a[i][j];
    fout << ")";
  }
  fout << "\n";
}

// We generate all the possible matrixes using the elements from the set. If a matrix passes the check test, we increment our cnt and we print the soltuion

void compute_matrixes(int x, int y, int val)
{
  a[x][y] = val;
  if (x == n && y == n)
  {
    if (check())
    {
      cnt++;
      if (n <= 4)
        print_solution();
    }
    return;
  }
  if (y == n)
  {
    ++x;
    y = 1;
  }
  else
    ++y;
  for (int i = 1; i <= n; ++i)
    compute_matrixes(x, y, i);
}

int main()
{
  fin >> n;

  // We begin our process by assigning all the values from the set A
  for (int i = 1; i <= n; ++i)
    compute_matrixes(1, 1, i);

  fout << "The number of associative operations on a set with " << n << " elements is " << cnt << '\n';
  return 0;
}