#include <iostream>
using namespace std;

class A
{
private:
  int *x;

public:
  A(int _x = 0)
  {
    x = new int{_x};
  }
  A(const A &a)
  {
    x = new int{*a.x};
  }
  int get()
  {
    return *x;
  }
  void set(int _x)
  {
    *x = _x;
  }
  ~A()
  {
    delete x;
  }
};

int main()
{
  A a1, a2;
  a1.set(8);
  A a3;
  a3 = a1;
  A a4 = a1;
  a1.set(5);
  cout << a1.get() << " ";
  cout << a2.get() << " ";
  cout << a3.get() << " ";
  cout << a4.get() << " ";
  system("pause");
  return 0;
}