#include <iostream>

using namespace std;

class Beverage
{
private:
  string description;

public:
  Beverage(string description = "") : description{description} {};
  Beverage &operator=(Beverage &beverage)
  {
    this->description = beverage.description;
    return *this;
  }
  virtual ~Beverage(){};
  virtual double price() const = 0;
  virtual void print() const
  {
    cout << this->description << " " << this->price() << '\n';
  };
};

class Coffee : public Beverage
{
public:
  Coffee() : Beverage{"Coffee"} {};
  double price() const override
  {
    return 2.5;
  }
};

class Tea : public Beverage
{
public:
  Tea() : Beverage{"Tea"} {};
  double price() const override
  {
    return 1.5;
  }
};

class BeverageWithMilk : public Beverage
{
private:
  Beverage *beverage;
  int milkCount;

public:
  BeverageWithMilk(Beverage *beverage, int milkCount = 0) : beverage{beverage}, milkCount{milkCount} {};
  ~BeverageWithMilk()
  {
    delete beverage;
  }
  double price() const override
  {
    return this->beverage->price() + 0.5 * milkCount;
  }
  void print() const override
  {
    this->beverage->print();
    cout << "Milk count: " << this->milkCount << '\n';
  }
};

class BeverageMachine
{
public:
  void prepare(string beverageType, int milkCount)
  {
    Beverage *beverage = new Coffee();
    if (beverageType == "Tea")
    {
      delete beverage;
      beverage = new Tea();
    }
    BeverageWithMilk beverageWithMilk(beverage, milkCount);
    beverageWithMilk.print();
  }
};

int main()
{
  BeverageMachine beverageMachine;

  beverageMachine.prepare("Tea", 0);
  beverageMachine.prepare("Tea", 2);
  beverageMachine.prepare("Tea", 3);
  beverageMachine.prepare("Coffee", 0);
  beverageMachine.prepare("Coffee", 1);
  beverageMachine.prepare("Coffee", 2);

  return 0;
}