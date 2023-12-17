#include <iostream>

using namespace std;

int fct(string s)
{
  if (s == "")
    throw string("2");
  cout << "1 ";
  if (s.size() > 4)
  {
    throw std::runtime_error{"Not empty"};
  }
  return 0;
}

int main()
{
  try
  {
    cout << fct("Hi") << " ";
    cout << fct("Hello") << " ";
    cout << fct("") << " ";
  }
  catch (string &e)
  {
    cout << e;
  }
  catch (std::runtime_error &e)
  {
    cout << e.what();
  }

  return 0;
}