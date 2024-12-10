#include <fstream>
#include <vector>
#include <deque>

using namespace std;

typedef vector<int> vi;

// Vectors to store the solutions
vector<vi> solutions;
vector<int> solution;

ifstream cin("5.in");
ofstream cout("5.out");

int m, n;

// Because we are working over Z_2, we can view each row of the matrix as a binary representation of a number, and we can use the XOR operator to check if 2 rows may not ensure that the matrix to be written in row echelon form. The leading 1 if the first bit, from left to right, that has value of 1. If there is another 1 on the same position, with XOR, the result will be 0, so the new number will be smaller than both of them, then the matrix can't be written in row echelon form.
bool check(int y)
{
  for (auto x : solution)
  {
    if ((x ^ y) < y)
      return false;
  }
  return true;
}

// Recursive function to generate all the possible solutions
void GenerateSolutions(int lvl)
{
  // If the current solution has the desired dimension, add it to the solutions vector
  if (lvl == m)
  {
    solutions.push_back(solution);
    return;
  }
  // For each possible vector, check if it can be part of the matrix and if it can, add it to the solution and call the function again
  // The next possible matrix is the one that is greater than or equal to the last one in the solution
  for (int i = solution.back(); i < (1 << n); ++i)
    if (check(i))
    {
      solution.push_back(i);
      GenerateSolutions(lvl + 1);
      solution.pop_back();
    }
}

// Function to print the binary representation of a number
void BinaryRepresentation(int x)
{
  deque<int> nr;
  while (x)
  {
    nr.push_front(x & 1);
    x >>= 1;
  }
  while (nr.size() < n)
    nr.push_front(0);

  cout << "(" << nr[0];
  for (int i = 1; i < n; ++i)
    cout << ", " << nr[i];
  cout << ")\n";
}

int main()
{
  cin >> m >> n;

  // The first vector in the basis is always has to be smaller than 2 ^ (n - 1), we start looping from 0

  for (int i = 0; i < (1 << (n - 1)); ++i)
  {
    solution.push_back(i);
    GenerateSolutions(1);
    solution.pop_back();
  }

  // Print the number of solutions
  cout << "The number of matrices A in reduced echelon form is " << solutions.size() << "\nThe matrices are\n";

  // Print the solutions
  for (auto v : solutions)
  {
    // We print the vectors in reverse order because the last vector is the one with the most significant bit set to 1, and the first vector is the one with the least significant bit set to 1
    for (int i = v.size() - 1; i >= 0; --i)
      BinaryRepresentation(v[i]);

    cout << "\n";
  }
  return 0;
}