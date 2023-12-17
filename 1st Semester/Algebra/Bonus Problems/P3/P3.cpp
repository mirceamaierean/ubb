#include <fstream>
#include <deque>
#include <vector>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

vector<deque<int>> v;

// For the vectors to be linearly independt, the determinant of the matrix must be != 0

int det(int a1, int b1, int c1,
        int a2, int b2, int c2,
        int a3, int b3, int c3)
{
  return (a1 * b2 * c3 + a2 * b3 * c1 + a3 * b1 * c2 - c1 * b2 * a3 - c2 * b3 * a1 - c3 * b1 * a2) & 1;
}

void solve_4()
{
  // We expand the matrix, using the first line
  // We loop through the vector that has all the vectors generated, we choose 4 that are different, and we compute the determinant.
  // If det != 0, then the vectors are linearly independet, so they form a basis
  // We print the solution
  for (int i = 0; i < v.size(); ++i)
    for (int j = 0; j < v.size(); ++j)
      for (int k = 0; k < v.size(); ++k)
        for (int l = 0; l < v.size(); ++l)
          if (i != j && i != k && i != l && j != k && j != l && k != l)
          {
            int det_value = (v[i][0] * det(v[j][1], v[j][2], v[j][3], v[k][1], v[k][2], v[k][3], v[l][1], v[l][2], v[l][3]) - v[i][1] * det(v[j][0], v[j][2], v[j][3], v[k][0], v[k][2], v[k][3], v[l][0], v[l][2], v[l][3]) + v[i][2] * det(v[j][1], v[j][0], v[j][3], v[k][1], v[k][0], v[k][3], v[l][1], v[l][0], v[l][3]) - v[i][3] * det(v[j][1], v[j][2], v[j][0], v[k][1], v[k][2], v[k][0], v[l][1], v[l][2], v[l][0])) & 1;
            if (det_value == 1)
              fout << "((" << v[i][0] << "," << v[i][1] << "," << v[i][2] << "," << v[i][3] << "),(" << v[j][0] << "," << v[j][1] << "," << v[j][2] << "," << v[j][3] << "),(" << v[k][0] << "," << v[k][1] << "," << v[k][2] << "," << v[k][3] << "),(" << v[l][0] << "," << v[l][1] << "," << v[l][2] << "," << v[l][3] << "))\n";
          }
}

void solve_3()
{
  // We loop through the vector that has all the vectors generated, we choose 3 that are different, and we compute the determinant.
  // If det != 0, then the vectors are linearly independet, so they form a basis
  // We print the solution
  for (int i = 0; i < v.size(); ++i)
    for (int j = 0; j < v.size(); ++j)
      for (int k = 0; k < v.size(); ++k)
        if (i != j && i != k && j != k)
        {
          int det_value = det(v[i][0], v[i][1], v[i][2], v[j][0], v[j][1], v[j][2], v[k][0], v[k][1], v[k][2]);
          if (det_value == 1)
            fout
                << "((" << v[i][0] << "," << v[i][1] << "," << v[i][2] << "),(" << v[j][0] << "," << v[j][1] << "," << v[j][2] << "),(" << v[k][0] << "," << v[k][1] << "," << v[k][2] << "))\n";
        }
}

void compute_vectors(int n)
{
  //                                                               ^    ^
  // Because it is modulo 2 class, each element of a vector can be 0 or 1. We loop thorugh the numbers from 1 to (2^n) - 1, and we find their binary representation. We push each bit to the front of a list (we use deque to do this opperation faster). If the size of the deque is smaller than n, then we add at the front 0 until the size is equal to n. After that, we push our deque to a vector.
  for (int i = 1; i < (1 << n); ++i)
  {
    deque<int> vect;
    int k = i;
    while (k)
    {
      vect.push_front(k & 1);
      k >>= 1;
    }
    while (vect.size() < n)
      vect.push_front(0);
    v.push_back(vect);
  }
}

int main()
{
  /*
    Let S = Z2n. A pair (z1, z2, …, zn) is a base ⇐⇒ z1, z2, z3, … , zn are linearly independent.
    Take z1  !=  0 ⇒ z1 is a part of the base ⇒ z1 can be chosen in 2ˆn − 1 ways.
    If z2, z3, z4, … zn ⇒ z1, z2, z3, … , zn linearly independent ⇐⇒ z2 ∈ S \ <z1 >, z3 ∈ S \ <z1,z2 >, …, zn ∈ S \ <z1,z2 , …,zn>.
    So z2 can be chosen in (2 ^ n – 2) ways, z3 can be chosen in  (2^n – 2^2), …, zn can be chosen in (2^n – 2^(n – 1). Hence, the number of basis is equal to (2^n – 1) * (2ˆn – 2) * … * (2^n – 2ˆ(n – 1)).
  */

  unsigned long long bases_cnt = 1, start_pow = 1LL, subst_pow = 1;
  int n;
  fin >> n;
  start_pow <<= n;
  while (start_pow > subst_pow)
  {
    bases_cnt *= start_pow - subst_pow;
    subst_pow <<= 1;
  }
  fout << "The number of bases is " << bases_cnt << '\n';
  if (n <= 4)
  {
    fout << "The vectors of each such basis are:\n";
    compute_vectors(n);
    if (n == 3)
      solve_3();
    if (n == 4)
      solve_4();
  }
  return 0;
}