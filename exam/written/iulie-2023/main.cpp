#include <iostream>
#include <vector>

using namespace std;

class MyObject
{
public:
    MyObject() {};
    virtual ~MyObject() {};
    virtual void print() = 0;
};

class MyInteger : public MyObject
{
private:
    int element;

public:
    MyInteger(int element = 0) : element{element} {};
    ~MyInteger() {};
    void print()
    {
        cout << element << ' ';
    }
};

class MyString : public MyObject
{
private:
    string element;

public:
    MyString(string element = "") : element{element} {};
    ~MyString() {};
    void print()
    {
        cout << element << ' ';
    }
};

class MyObjectList
{
private:
    vector<MyObject *> v;

public:
    MyObjectList() {};
    ~MyObjectList()
    {
        for (auto obj : v)
            delete obj;
    };
    MyObjectList &add(MyObject *obj)
    {
        v.push_back(obj);
        return *this;
    }
    MyObject *getElementOnPosition(int pos)
    {
        return v[pos];
    }

    vector<MyObject *> &getObject()
    {
        return this->v;
    }

    MyObject *getObjectOnPosition(int pos)
    {
        return this->v[pos];
    }

    int length()
    {
        return this->v.size();
    }

    friend class MyListIterator;
};

class MyListIterator
{
private:
    MyObjectList &l;
    int pos;

public:
    MyListIterator(MyObjectList &list) : l{list}, pos{0} {}

    MyObject *element()
    {
        return l.v[pos];
    }

    bool isValid()
    {
        return pos < l.v.size();
    }

    void next()
    {
        ++pos;
    };
};

class Person
{
private:
    string surname, firstname;
    int age;

public:
    Person(string surname = "", string firstname = "", int age = 0) : surname{surname}, firstname{firstname}, age{age} {};

    void setSurname(string s)
    {
        surname = s;
    }

    void setFirstname(string s)
    {
        firstname = s;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    int getAge()
    {
        return this->age;
    }

    string getSurname()
    {
        return this->surname;
    }

    string getFirstname()
    {
        return this->firstname;
    }
};

bool sort(Person &a, Person &b)
{
    if (a.getAge() == b.getAge())
    {
        if (a.getSurname() == b.getSurname())
            return a.getFirstname() < b.getFirstname();
        return a.getSurname() < b.getSurname();
    }
    return a.getAge() > b.getAge();
}

void merge(vector<Person> &v, bool (*sortFunction)(Person &, Person &))
{
    if (v.size() == 1)
        return;

    int mid = v.size() / 2;

    vector<Person> firstHalf, secondHalf;

    for (int i = 0; i < mid; ++i)
        firstHalf.push_back(v[i]);

    for (int i = mid; i < v.size(); ++i)
        secondHalf.push_back(v[i]);

    merge(firstHalf, sortFunction);
    merge(secondHalf, sortFunction);

    v.clear();

    int firstHalfIndex = 0, secondHalfIndex = 0;
    while (firstHalfIndex < firstHalf.size() && secondHalfIndex < secondHalf.size())
    {
        if (sortFunction(firstHalf[firstHalfIndex], secondHalf[secondHalfIndex]))
            v.push_back(firstHalf[firstHalfIndex++]);
        else
            v.push_back(secondHalf[secondHalfIndex++]);
    }

    while (firstHalfIndex < firstHalf.size())
        v.push_back(firstHalf[firstHalfIndex++]);

    while (secondHalfIndex < secondHalf.size())
        v.push_back(secondHalf[secondHalfIndex++]);
}

int main()
{
    MyObjectList list{};
    list.add(new MyInteger{2}).add(new MyString{"Hi"});

    MyString *s = new MyString{"Bye"};

    list.add(s).add(new MyString{"5"});

    MyListIterator i{list};

    while (i.isValid())
    {
        MyObject *o = i.element();
        o->print();
        i.next();
    }

    Person mircea("Maierean", "Mircea", 21);
    Person alex("Ignat", "Alex", 22);
    Person dragos("Ignat", "Dragos", 22);
    Person vivi("Jurj", "Victor", 21);
    Person deea("Lung", "Andreea", 21);

    vector<Person> v{mircea, alex, dragos, vivi, deea};
    merge(v, sort);
    cout << '\n';

    for (auto &p : v)
        cout << p.getSurname() << ' ' << p.getFirstname() << '\n';
    return 0;
}