#include <iostream>

class Person
{
public:
  Person() { std::cout << "Person{}"; }
  virtual void print() = 0;
  ~Person() { std::cout << "~Person()"; }
};

class Student : public Person
{
public:
  Student()
  {
    std::cout << "Student{}";
  }
  void print() override { std::cout << "Student"; }
  ~Student() { std::cout << "~Student()"; }
};

int main()
{
  // This generates error, Person is abstract, can't be instantiated
  // Person *p = new Person{};
  // delete p;
  Student *s = new Student{};
  s->print();
  delete s;

  return 0;
}