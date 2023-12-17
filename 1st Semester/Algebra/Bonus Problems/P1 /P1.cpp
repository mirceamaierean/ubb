#include <fstream>
#include <vector>
#include <bitset>
#include <set>
using namespace std;

ifstream cin("input.in");
ofstream cout("output.out");

/* We see that, inside a partiton, for each of the components set, the elements are with their indexes in an ascending order. If we remove the brackets, we can see that the set generated is a permutation of the set {a1, a2, a3 ... , an}. In order to solve this, we will generate all of the permutations of our initial set, and we will use a structure, that guarantees an unique solution. In order to get the set, we will use a function AddToSet, that, for each permutation, breaks it into multiple sets. An element is added to the current set if it is greater than the last element added to the set. If not, it will added to a new set, that will be used to compare the following elements. The partitions will be stored in a structure
set < set <set <int> > > solutions
set <int> assures that the elements in a set of the partitions are in ascendin order
set < set <int> > represents a partition that is sorted in an ascending order
set < set < set <int> > > represents all the partitions of our set. When we add a new partition to the set, it will be checked if the partition is already there, and, if it is present, it will not be stored in our solution.
*/

// In this vertor, we will store the permutations of {a1, a2, a3 ... an}
vector<int> v;

// This structure is used for generating the permutations of n
bitset<100> used;

int n, cnt;

set<set<set<int>>> solutions;

/* This function separates our permutation in sets, where all the elements are in ascendin order
For example, let's consider the permutation (1, 4, 3, 7, 2, 5, 6, 8)
This permutation will be decomposed in sets, with each of the elements in an ascendin order
{1, 4}, {3, 7}, {2, 5, 6, 8}
Because we use a set, the permutations will be stored with the elements in an ascending order, resulting in
{1, 4}, {2, 5, 6, 8}, {3, 7}
*/
void AddToSet()
{
  set<set<int>> solution;
  set<int> s;
  s.insert(v[0]);
  for (int i = 1; i < n; ++i)
  {
    if (v[i] < v[i - 1])
    {
      solution.insert(s);
      s.clear();
    }
    s.insert(v[i]);
  }
  solution.insert(s);
  solutions.insert(solution);
}

// Backtracking algorithm to generate all of the permutations

void back(int val)
{
  used[val] = 1;
  v.push_back(val);
  if (v.size() == n)
    AddToSet();
  else
  {
    for (int i = 1; i <= n; ++i)
      if (used[i] == 0)
        back(i);
  }
  v.pop_back();
  used[val] = 0;
}

set<pair<int, int>> pairs;

// For the equivalence relation, we take each of the sets in a permutation, and we generate the cartesian product. We will store the pairs, in a set of pairs

void CreatePairs(set<int> &s)
{
  for (auto x : s)
    for (auto y : s)
      pairs.insert({x, y});
}

int main()
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    back(i);

  // After we generate the products, we display the size of set of the partitions

  cout << "The number of partitions of a set with " << n << " elements is " << solutions.size() << '\n';

  cout << "The partitions, and their equivalence relations, are: \n";

  for (auto sol : solutions)
  {
    pairs.clear();
    cout << "{";
    // We use cnt to check if we are at the last element. Based on this, we check if we display print a comma or not
    int cnt = 0;
    for (auto s : sol)
    {
      ++cnt;
      cout << "(";
      set<int>::iterator it = s.begin();
      cout << "a[" << *it << "]";
      ++it;
      for (; it != s.end(); ++it)
        cout << ", a[" << *it << "]";
      cout << ")";
      if (cnt != sol.size())
        cout << ", ";
      CreatePairs(s);
    }
    cout << "} -> {";
    cnt = 0;
    for (auto pair : pairs)
    {
      cout << "(a[" << pair.first << "], a[" << pair.second << "])";
      ++cnt;
      if (cnt != pairs.size())
        cout << ", ";
    }
    cout << "}\n";
  }

  return 0;
}