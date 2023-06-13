#include <iostream>
#include <deque>

using namespace std;

int main()
{
  vector<int> v{1, 2, 3, 4, 5};
  vector<int>::iterator it = std::find(v.begin(), v.end(), 4);
  v.insert(it, 7);
  it = v.begin() + 2;
  *it = 11;
  deque<int> x;
  std::copy_if(v.begin(), v.end(), front_inserter(x), [](int a)
               { return a % 2 == 1; });
  for (auto a : x)
    std::cout << a << " ";

  v = vector<int>{1, 2, 3, 4, 5};
  it = std::find(v.begin(), v.end(), 4);
  v.insert(it, 8);
  it = v.begin() + 2;
  *it = 10;
  vector<int> X;
  std::copy_if(v.begin(), v.end(), back_inserter(X), [](int a)
               { return a % 2 == 0; });
  for (auto a : X)
    std::cout << a << " ";
  return 0;
}