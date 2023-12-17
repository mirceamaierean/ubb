#include <iostream>
#include <cassert>
#include <exception>
#include <vector>

template <typename T>
class Stack
{
private:
  int maxCapacity, firstFree;
  T *elements;

public:
  Stack(int maxCapacity = 0) : maxCapacity(maxCapacity)
  {
    this->firstFree = 0;
    this->elements = new T[maxCapacity];
  }

  ~Stack()
  {
    delete this->elements;
  }

  int getCapacity() const
  {
    return this->maxCapacity;
  }

  T pop()
  {
    if (this->firstFree == 0)
      throw std::runtime_error("Stack is empty");

    return this->elements[--this->firstFree];
  }

  Stack &operator+(const T &item)
  {
    /**
     * Pushes an item onto the stack.
     * If the stack is already full, throws a runtime_error exception.
     *
     * @param item The item to be pushed onto the stack. item is of type T
     * @return A reference to the modified stack.
     * @throws std::runtime_error If the stack is already full.
     */
    if (this->firstFree == this->maxCapacity)
      throw std::runtime_error("Stack is full");

    this->elements[this->firstFree++] = item;
    return *this;
  }
};

int main()
{
  Stack<std::string> s{2};

  assert(s.getCapacity() == 2);

  try
  {
    s = s + "capacity";
    s = s + "oop";
    s = s + "test";
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  assert(s.pop() == "oop");
  assert(s.pop() == "capacity");

  try
  {
    s.pop();
    assert(false);
  }
  catch (const std::exception &e)
  {
    assert(true);
    std::cerr << e.what() << '\n';
  }

  return 0;
}
