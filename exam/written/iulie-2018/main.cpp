#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace std;

class Vehicle
{
private:
    int basePrice;

public:
    Vehicle(int basePrice) : basePrice{basePrice}
    {
        if (basePrice <= 0)
            throw runtime_error("Baseprice must be greater than 0");
    }
    virtual ~Vehicle() {}
    virtual string description() = 0;
    virtual int getPrice()
    {
        return this->basePrice;
    }
};

class Car : public Vehicle
{
private:
    string model;

public:
    Car(int basePrice, string model) : Vehicle(basePrice), model{model}
    {
        if (model == "")
            throw runtime_error("Model not configured");
    }

    string description()
    {
        return this->model;
    }
};

class AutomaticCar : public Car
{
private:
    int additionalPrice;

public:
    AutomaticCar(int basePrice, string model, int additionalPrice) : Car(basePrice, model), additionalPrice{additionalPrice}
    {
        if (additionalPrice <= 0)
            throw runtime_error("Additional Price has to be greater than 0");
    }
    int getPrice()
    {
        return Car::getPrice() + this->additionalPrice;
    }
    string description()
    {
        return "Automatic car " + Car::description();
    }
};

class CarWithParkingSensor : public Car
{
private:
    string sensorType;

public:
    CarWithParkingSensor(int basePrice, string model, string sensorType) : Car(basePrice, model), sensorType{sensorType}
    {
        if (sensorType == "")
            throw runtime_error("Sensor type not configured");
    };

    int getPrice()
    {
        return Car::getPrice() + 2500;
    }

    string description()
    {
        return "Car with parking sensor " + this->sensorType + " " + Car::description();
    }
};

vector<pair<string, int>> countCar(vector<Vehicle *> &l)
{
    unordered_map<string, int> cars;
    for (auto &crt : l)
    {
        Car *castToCar = dynamic_cast<Car *>(crt);
        if (castToCar)
            ++cars[castToCar->description()];
    }

    vector<pair<string, int>> cnt;

    for (auto x : cars)
        cnt.push_back(x);

    return cnt;
}

void arrangeCars(vector<Vehicle *> &l)
{
    for (int i = 0; i < l.size(); ++i)
    {
        for (int j = i + 1; j < l.size(); ++j)
        {
            int price1 = l[i]->getPrice();
            int price2 = l[j]->getPrice();
            if ((price2 >= 1000 && price2 <= 2000) && (price1 < 1000 || price1 > 4000))
                swap(l[i], l[j]);
        }
    }
}

void printDescription(vector<Vehicle *> &l)
{
    for (auto &crt : l)
    {
        Car *castToCar = dynamic_cast<Car *>(crt);
        if (castToCar)
            cout << castToCar->description() << '\n';
    }
}

void e()
{
    Vehicle *car1 = new Car(100, "Audi");
    Vehicle *car2 = new AutomaticCar(5000, "Audi", 30);
    Vehicle *car3 = new Car(1500, "Toyota");
    Vehicle *car4 = new AutomaticCar(1700, "Mercedes", 5000);
    Vehicle *car5 = new CarWithParkingSensor(1000, "Toyota", "Senzori");

    vector<Vehicle *> l{car1, car2, car3, car4, car5};
    printDescription(l);
    vector<pair<string, int>> vp = countCar(l);

    arrangeCars(l);
    printDescription(l);

    delete car1;
    delete car2;
    delete car3;
    delete car4;
    delete car5;
}

int main()
{
    e();
    return 0;
}
