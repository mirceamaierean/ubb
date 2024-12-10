#include <iostream>
#include <string.h>
#include <vector>
#include <stdexcept>

using namespace std;

class Complex
{
private:
  double real, imaginary;

public:
  Complex(double real = 0, double imaginary = 0) : real{real}, imaginary{imaginary} {};

  double getReal() const { return this->real; }
  double getImaginary() const { return this->imaginary; }
  void setReal(double real) { this->real = real; }
  void setImaginary(double imaginary) { this->imaginary = imaginary; };

  bool operator==(const Complex &other) const
  {
    return this->getReal() == other.getReal() && this->imaginary == other.getImaginary();
  }
  Complex &operator=(const Complex &other)
  {
    this->setReal(other.getReal());
    this->setImaginary(other.getImaginary());
    return *this;
  }
  Complex &operator/(const double divider)
  {
    if (divider == 0)
      throw runtime_error("Division by zero!");
    this->setReal(this->getReal() / divider);
    this->setImaginary(this->getImaginary() / divider);
    return *this;
  }
  friend std::ostream &operator<<(std::ostream &out, const Complex &complex);
};

std::ostream &operator<<(std::ostream &out, const Complex &complex)
{
  out << complex.real << "+" << complex.imaginary << "i";
  return out;
}

template <typename T>
class Vector
{
private:
  vector<T> elements;

public:
  Vector(const std::vector<T> &elements) : elements{elements} {};

  void printAll(std::ostream &os) const
  {
    for (auto element : elements)
      os << element << ", ";
    os << '\n';
  }
};

int main()
{
  Complex a{}, b{1, 2}, c{6, 4}, d{b};

  assert(a.getReal() == 0 && a.getImaginary() == 0);

  assert(b == d);

  Complex res1 = c / 2;

  std::cout << res1 << '\n';

  try
  {
    Complex res2 = b / 0;
  }
  catch (runtime_error &e)
  {
    assert(strcmp(e.what(), "Division by zero!") == 0);
  }

  Vector<string> v1(std::vector<string>{"hello", "bye"});

  v1.printAll(std::cout);

  Vector<Complex> v2{std::vector<Complex>{a, b, c, d}};
  v2.printAll(std::cout);

  return 0;
}