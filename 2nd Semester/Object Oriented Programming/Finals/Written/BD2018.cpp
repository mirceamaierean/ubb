#include <iostream>

using namespace std;

class B
{
public:
  B(){};
  B(const B &b) { cout << "copy "; }
  virtual void f() { cout << "B.f "; }
  void g(B b) { cout << "B.g "; };
  virtual ~B() { cout << "~B() "; }
};

class D : public B
{
public:
  D(){};
  void f() { cout << "D.f "; }
  void g(D d) { cout << "D.g "; }
};

int main()
{
  B *b = new B();
  B *d = new D();
  // D.f
  d->f();
  // copy B.g ~B()
  d->g(*b);
  //~B()
  delete b;
  //~B()
  delete d;
  return 0;
}