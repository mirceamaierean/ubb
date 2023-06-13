#include <iostream>

using namespace std;

class Expression
{
public:
  virtual double evaluate() = 0;
};

class Constant : public Expression
{
private:
  double number;

public:
  Constant(double number = 0) : number{number};
  double evaluate()
  {
    return this->number;
  }
};

int main()
{
  return 0;
}