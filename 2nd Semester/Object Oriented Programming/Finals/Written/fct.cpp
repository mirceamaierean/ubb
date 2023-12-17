#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
T fct(vector<T> v)
{
  if (v.empty())
    throw exception();
  T sum = T();
  for (auto el : v)
    sum += el;
  return sum;
}

int main()
{
  vector<int> v1{4, 2, 1, -4};

  assert(fct<int>(v1) == 3);

  vector<int> v2;

  try
  {
    fct<int>(v2);
    assert(false);
  }
  catch (std::exception &)
  {
    assert(true);
  }

  vector<double> v3{2, 10.5, 5, -10};
  assert(fct<double>(v3) == 7.5);

  vector<string> v4{"y", "q", "a", "m"};
  assert(fct<string>(v4) == "yqam");

  return 0;
}