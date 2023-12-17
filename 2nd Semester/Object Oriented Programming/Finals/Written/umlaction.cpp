#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Action
{
public:
  Action(){};
  virtual ~Action(){};
  virtual void execute() const = 0;
};

class CreateAction : public Action
{
public:
  CreateAction(){};
  void execute() const
  {
    cout << "Create File\n";
  }
};

class ExitAction : public Action
{
public:
  ExitAction(){};
  void execute() const override
  {
    cout << "Exit File\n";
  }
};

class MenuItem
{
private:
  string text;
  Action *action;

public:
  MenuItem(string text = "", Action *action = nullptr) : text{text}, action{action} {};
  ~MenuItem()
  {
    if (action != nullptr)
      delete action;
  }
  string getText() const
  {
    return this->text;
  }
  virtual void print() const
  {
    cout << this->text << '\n';
  }
  void clicked() const
  {
    this->print();
    if (action != nullptr)
      action->execute();
  }
};

class Menu : public MenuItem
{
private:
  vector<unique_ptr<MenuItem>> items;

public:
  Menu(string text = "", Action *action = nullptr) : MenuItem{text, action} {};
  void add(MenuItem *menuItem)
  {
    this->items.emplace_back(menuItem);
  }
  void print() const
  {
    cout << this->getText() << "\n";
    for (auto &item : items)
      item->print();
  }
};

class MenuBar
{
private:
  vector<unique_ptr<Menu>> menus;

public:
  void add(Menu *m)
  {
    this->menus.emplace_back(m);
  }
  void print()
  {
    for (auto &menu : menus)
      menu->print();
  }
};

int main()
{
  return 0;
}