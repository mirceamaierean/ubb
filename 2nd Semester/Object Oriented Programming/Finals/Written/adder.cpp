#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Adder
{
private:
  std::vector<T> values;

public:
  Adder(T value = T())
  {
    values.push_back(value);
  };
  T getSum() const
  {
    T sum = T();
    for (auto elem : values)
      sum += elem;
    return sum;
  }

  std::vector<T> getValues() const
  {
    return this->values;
  }

  Adder &operator=(const Adder &other)
  {
    this->values = other.getValues();
    return *this;
  }
  Adder &operator+(const T &value)
  {
    this->values.push_back(value);
    return *this;
  }

  Adder &operator++()
  {
    this->values.push_back(this->values.back());
    return *this;
  }

  Adder &operator++(int)
  {
    this->values.push_back(this->values.back());
    return *this;
  }

  Adder &operator--()
  {
    if (this->values.empty())
      throw runtime_error("No more values");
    this->values.pop_back();
    return *this;
  }
};

int main()
{
  Adder<int> add{5};
  add = add + 5 + 2;
  ++add;
  add++;
  add + 8;
  std::cout << add.getSum() << '\n';
  --add;
  std::cout << add.getSum() << '\n';
  --(--add);
  std::cout << add.getSum() << '\n';

  try
  {
    --(--(--add));
  }
  catch (runtime_error &ex)
  {
    std::cout << ex.what() << '\n';
  }

  return 0;
}