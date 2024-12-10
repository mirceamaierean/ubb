#include <iostream>
#include <stdexcept>

using namespace std;

class Vector
{
private:
  int *elems;
  int size;

public:
  Vector() : size{0}
  {
    elems = new int[10];
  }
  void add(int elem)
  {
    elems[size++] = elem;
  }
  int &operator[](int pos)
  {
    if (pos < 0 || pos >= size)
      throw std::runtime_error{"Index out of bounds!"};
    return elems[pos];
  }
  ~Vector()
  {
    delete elems;
  }
};

int main()
{
  Vector v1;
  v1.add(0);
  v1.add(1);
  Vector v2 = v1;
  try
  {
    v1[0] = 2;
    cout << v1[0] << " " << v1[1] << '\n';
    cout << v2[0] << " " << v2[1] << '\n';
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << '\n';
  }

  return 0;
}