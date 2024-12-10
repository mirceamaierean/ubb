#include <iostream>

class B
{
public:
  B() { std::cout << "B{}\n"; }
  virtual void print() { std::cout << "B\n"; }
  virtual ~B() { std::cout << "~B()\n"; }
};

class D : public B
{
public:
  D() { std::cout << "D{}\n"; }
  void print() override { std::cout << "D\n"; }
  virtual ~D() { std::cout << "~D()\n"; }
};

int main()
{
  B *b[] = {new B{}, new D{}};
  b[0]->print();
  b[1]->print();
  delete b[0];
  delete b[1];
  return 0;
}