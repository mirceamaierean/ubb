#include <deque>
#include <string>
#include <iostream>
int main()
{
  std::deque<std::string> d;
  d.push_back("A");
  d.push_front("B");
  d.push_back("C");
  d.push_front("D");
  auto itBegin = d.begin();
  auto itEnd = d.end();
  itBegin++;
  itEnd--;
  while (itBegin != itEnd)
  {
    std::cout << *itBegin << " ";
    itBegin++;
  }
  return 0;
}