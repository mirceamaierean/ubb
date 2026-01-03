#include <iostream>
#include <stdexcept>
#include <stack>

using namespace std;

class RailCar
{
private:
    string name;
    RailCar *next;

public:
    RailCar(string name = "", RailCar *next = nullptr) : name{name}, next{next}
    {
        if (name.length() < 2)
            throw runtime_error("Name length must be at lrast 2");
    };

    virtual ~RailCar() {}

    virtual bool isProfitable() = 0;
    virtual string toString() = 0;

    RailCar *getNext()
    {
        return this->next;
    }

    void setNext(RailCar *next)
    {
        this->next = next;
    }

    virtual RailCar *clone() = 0;

    string getName()
    {
        return this->name;
    }
};

class PassengerCar : public RailCar
{
private:
    int capacity;

public:
    PassengerCar(string name = "", RailCar *next = nullptr, int capacity = 0) : RailCar(name, next), capacity{capacity}
    {
        if (capacity < 0)
            throw runtime_error("Capacity has to be greater than 0");
    };
    bool isProfitable()
    {
        return this->capacity > 40;
    }
    string toString()
    {
        return this->getName() + " " + to_string(capacity);
    }
    RailCar *clone()
    {
        return new PassengerCar(this->getName(), this->getNext(), this->capacity);
    }
};

class RestaurantCar : public RailCar
{
private:
    int numberOfTables;

public:
    RestaurantCar(string name = "", RailCar *next = nullptr, int numberOfTables = 0) : RailCar(name, next), numberOfTables{numberOfTables}
    {
        if (numberOfTables < 0)
            throw runtime_error("Number of tables has to be greater than 0");
    };
    bool isProfitable()
    {
        return this->numberOfTables > 20;
    }
    string toString()
    {
        return this->getName() + " " + to_string(numberOfTables);
    }
    RailCar *clone()
    {
        return new RestaurantCar(this->getName(), this->getNext(), this->numberOfTables);
    }
};

class Locomotive
{
private:
    RailCar *first;

public:
    Locomotive(RailCar *first = nullptr) : first{first} {};
    ~Locomotive()
    {
        RailCar *crt = first;
        while (crt != nullptr)
        {
            RailCar *next = crt->getNext();
            RailCar *cpy = crt;
            delete cpy;
            crt = next;
        }
    }
    void attachRailCar(RailCar *next)
    {
        // next: pointer of class RailCar
        // returns: nothing
        // iterates on the linked list of RailCars and adds at the end the pointer to the car that wishes to be added
        RailCar *crt = first;
        if (crt == nullptr)
        {
            first = next;
            return;
        }
        RailCar *prev = crt;
        while (crt != nullptr)
        {
            prev = crt;
            crt = crt->getNext();
        }
        prev->setNext(next);
    }
    RailCar *getFirstRailCar()
    {
        return this->first;
    }
    void setFirstRailCar(RailCar *newFirst)
    {
        this->first = newFirst;
    }
};

void removeRailCarsThatAreNotProfitable(Locomotive &l)
{
    RailCar *crt = l.getFirstRailCar();

    while (crt != nullptr && crt->isProfitable() == false)
        crt = crt->getNext();

    l.setFirstRailCar(crt);

    while (crt != nullptr)
    {
        RailCar *next = crt->getNext();
        while (next != nullptr && next->isProfitable() == false)
        {
            RailCar *nextNext = next->getNext();
            crt->setNext(nextNext);
            delete next;
            next = nextNext;
        }
        crt = crt->getNext();
    }
}

Locomotive cloneLocomotive(Locomotive &l)
{
    RailCar *crt = l.getFirstRailCar();
    if (crt == nullptr)
        return Locomotive();

    stack<RailCar *> stacksOfRailCars;

    while (crt != nullptr)
    {
        stacksOfRailCars.push(crt);
        crt = crt->getNext();
    }

    crt = stacksOfRailCars.top()->clone();
    RailCar *firstCar = crt;
    stacksOfRailCars.pop();

    while (!stacksOfRailCars.empty())
    {
        crt->setNext(stacksOfRailCars.top()->clone());
        stacksOfRailCars.pop();
        crt = crt->getNext();
    }

    crt->setNext(nullptr);
    Locomotive copyOfLocomotive(firstCar);

    return copyOfLocomotive;
}

void solveE()
{
    Locomotive l;

    l.setFirstRailCar(new PassengerCar("Robi", nullptr, 50));
    l.attachRailCar(new PassengerCar("Hori", nullptr, 32));
    l.attachRailCar(new PassengerCar("Vivi", nullptr, 40));
    l.attachRailCar(new RestaurantCar("Deea", nullptr, 25));
    l.attachRailCar(new RestaurantCar("Mircea", nullptr, 20));

    removeRailCarsThatAreNotProfitable(l);

    Locomotive cpy = cloneLocomotive(l);

    RailCar *crt = cpy.getFirstRailCar();

    while (crt != nullptr)
    {
        cout << crt->toString() << "\n";
        crt = crt->getNext();
    }
}

int main()
{
    solveE();
    return 0;
}