#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
function findPosition(a, elem) is:
    left <- 1
    right <- a.len
    ans <- right + 1
    while left <= right
        mid <- [(left + right) / 2]
        if a[mid] = elem then
            return mid
        end-if
        if a[mid] > elem then
            left <- mid + 1
        else
            if mid < ans
                ans = mid
            end-if
            right <- mid - 1
        end-if
        return ans
    end-while
end-subalgorithm

function circularPermutation(x, k)
    n <- len(x)
    s <- "" // array of length x
    for i = 1 to n
        s[(i - 1 + k) % n + 1] <- x[i]
    end-for
    return s
end-subalgorithm
*/

/*
// cat de mult ma duc in jos, spre stanga
// ajung jos de tot, dupa urc in root (voi avea nevoie de o valoare mai mare decat ceea ce aveam anterior)
// dupa cobor in dreapta, unde iar voi avea o valoare mai mare
// 1 2 3....n

function checkArray(a, n)
    isOk <- true;
    for i = 1 to n:
        while a[i] != i then:
            isOk <- false
            j <- a[i]
            aux <- a[i]
            a[i] <- a[j]
            a[j] <- aux
            print(i, j)
        end-while
    end-for
    if isOk then
        print(0)
    end-if
end-subalgorithm

*/

class Product
{
private:
    string name;
    int baseprice;

public:
    Product(string name, int baseprice) : name{name}, baseprice{baseprice} {};
    virtual ~Product() {};
    virtual string toString()
    {
        return this->name + ", " + to_string(this->totalPrice());
    }
    virtual int totalPrice()
    {
        return this->baseprice;
    }
};

class Computer : public Product
{
private:
    int tax;

public:
    Computer(string name, int baseprice, int tax) : Product(name, baseprice), tax{tax} {};
    ~Computer() {};
    int totalPrice()
    {
        return Product::totalPrice() + tax;
    }
};

class SorterByTotalPrice
{
private:
    static inline bool cmp(Product *a, Product *b)
    {
        return a->totalPrice() > b->totalPrice();
    }

public:
    static void sort(vector<Product *> &v)
    {
        std::sort(v.begin(), v.end(), cmp);
    }
};

class Contact
{
private:
    string name;

public:
    Contact(string name = "") : name{name} {};
    virtual ~Contact() {};
    virtual void sendMessage(string message) = 0;
    string getName()
    {
        return this->name;
    }
};

class Person : public Contact
{
private:
    string number;

public:
    Person(string name = "", string number = "") : Contact(name), number{number} {};
    ~Person() {};

    void sendMessage(string message) override
    {
        cout << this->getName() << " " << this->number << " " << message << '\n';
    }
};

class Group : public Contact
{
private:
    vector<Contact *> contacts;

public:
    Group(string groupName, vector<Contact *> contacts) : Contact(groupName), contacts{contacts} {}

    void add(Contact *contact)
    {
        this->contacts.push_back(contact);
    }

    void sendMessage(string message) override
    {
        for (auto c : contacts)
            c->sendMessage(message);
    }
    ~Group()
    {
        for (auto c : contacts)
            delete c;
    }
};

int main()
{
    vector<Product *> computers{new Computer("HC90", 140, 10), new Computer{"HC91", 100, 12}, new Computer("HC85", 150, 15)};
    SorterByTotalPrice::sort(computers);

    cout << computers[0]->toString();
    for (auto c : computers)
    {
        delete c;
        c = nullptr;
    }

    Contact *mother = new Person("Mother", "1");
    Contact *father = new Person("Father", "2");
    Group *group1 = new Group("motherfather", vector<Contact *>{mother, father});

    // group1->add(mother);
    // group1->add(father);

    Group *family = new Group("Family", vector<Contact *>{group1, new Person("Jane", "3")});

    // family->add(group1);
    // family->add(new Person("Jane", "3"));

    Contact *john = new Person("John", "4");
    family->sendMessage("You are invited to my birthday party!");
    john->sendMessage("You are invited to my birthday party!");

    delete john;
    delete family;

    return 0;
}