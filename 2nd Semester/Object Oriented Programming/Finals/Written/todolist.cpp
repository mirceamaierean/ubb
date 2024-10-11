#include <iostream>
#include <vector>

class Activity
{
private:
  std::string name, time;

public:
  Activity(std::string name = "", std::string time = "") : name{name}, time{time} {};
  friend std::ostream &operator<<(std::ostream &out, const Activity &act);
};

std::ostream &operator<<(std::ostream &out, const Activity &act)
{
  out << "Activity " << act.name << " takes place at " << act.time;
  return out;
}

template <typename T>
class ToDo
{
private:
  std::vector<T> tasks;

public:
  ToDo(){};
  ToDo &operator+=(const T &t)
  {
    this->tasks.push_back(t);
    return *this;
  }
  void reversePrint(std::ostream &out)
  {
    auto it = this->tasks.rbegin();
    for (; it != this->tasks.rend(); ++it)
      out << *it << '\n';
  }
  typedef typename std::vector<T>::iterator iterator;

  iterator begin()
  {
    return this->tasks.begin();
  }

  iterator end()
  {
    return this->tasks.end();
  }
};

int main()
{
  ToDo<Activity> todo{};
  Activity tiff{"go to TIFF movie", "20:00"};

  todo += tiff;

  Activity project{"present project assignment", "09.20"};
  todo += project;

  for (auto a : todo)
    std::cout << a << '\n';

  todo.reversePrint(std::cout);
  return 0;
}