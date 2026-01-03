#include <iostream>

using namespace std;

class Sofa
{
private:
    double width, height;
    Sofa *next, *previous;

public:
    Sofa(double width, double height, Sofa *next = nullptr, Sofa *previous = nullptr)
    {
        if (width <= 0)
            throw invalid_argument("Width is not a strictly positive value");
        if (height <= 0)
            throw invalid_argument("Height is not a strictly positivi value");
        this->width = width;
        this->height = height;
        this->next = next;
        this->previous = previous;
    };
    virtual ~Sofa() {}
    virtual double getCoefficient() = 0;
    double getPrice()
    {
        return this->getCoefficient() * (this->height + this->width);
    }
    Sofa *getNext()
    {
        return this->next;
    }
    Sofa *getPrevious()
    {
        return this->previous;
    }
    void setNext(Sofa *nextSofa)
    {
        this->next = nextSofa;
    }
    void setPrevious(Sofa *previousSofa)
    {
        this->previous = previousSofa;
    }
};

class SofaWithRoundArms : public Sofa
{
private:
    double lengthOfArms;

public:
    SofaWithRoundArms(double width, double height, double lengthOfArms, Sofa *next = nullptr, Sofa *previous = nullptr) : Sofa(width, height, next, previous)
    {
        if (lengthOfArms < 0)
            throw invalid_argument("LOA is not a strictly positive value");
        this->lengthOfArms = lengthOfArms;
    }

    double getCoefficient()
    {
        return 2;
    }

    double getPrice()
    {
        return 10 * lengthOfArms + Sofa::getPrice();
    }
};

class ClassicSofa : public Sofa
{
public:
    ClassicSofa(double width, double height, Sofa *next = nullptr, Sofa *previous = nullptr) : Sofa(width, height, next, previous) {}

    double getCoefficient()
    {
        return 1.5;
    }
};

class SellingProduct
{
private:
    Sofa *first, *last;

public:
    SellingProduct(Sofa *first = nullptr, Sofa *last = nullptr)
    {
        this->first = first;
        this->last = last;
    }

    ~SellingProduct()
    {
    }

    void addProductToSell(Sofa *sofa)
    {
        Sofa *crt = this->first;
        if (crt == nullptr)
        {
            // first sofa that is added, so set first and last to the current sofa
            this->first = sofa;
            this->last = sofa;
        }
        while (crt != nullptr)
        {
            double currentPriceOfSofa = crt->getPrice();
            if (currentPriceOfSofa < sofa->getPrice())
            {
                // sofa has to be inserted here
                Sofa *prevSofa = crt->getPrevious();
                if (prevSofa != nullptr)
                {
                    prevSofa->setNext(sofa);
                    sofa->setPrevious(prevSofa);
                    sofa->setNext(crt);
                }
                else
                {
                    // if prevSofa is a nullptr, then it means it was the first one of the list, so update first as well
                    this->first = sofa;
                    sofa->setNext(crt);
                    crt->setPrevious(sofa);
                }
                return;
            }
            else
                crt = crt->getNext();
        }
        // if we are here at the end, it means that we have traversed the whole this
        // so, the sofa has to be added at the end
        last->setNext(sofa);
        sofa->setPrevious(last);
        this->last = sofa;
    }

    Sofa *getFirstProduct()
    {
        return this->first;
    }

    Sofa *getLastProduct()
    {
        return this->last;
    }

    void setFirstProduct(Sofa *sofa)
    {
        this->first = sofa;
    }

    void setLastProduct(Sofa *sofa)
    {
        this->last = sofa;
    }
};

void displayPricesInAscendingOrder(SellingProduct &sp)
{
    Sofa *s = sp.getLastProduct();

    while (s != nullptr)
    {
        cout << s->getPrice() << '\n';
        s = s->getPrevious();
    }
}

void removeSofaWithPriceInRange(SellingProduct &sp, double startPrice, double endPrice)
{
    if (startPrice > endPrice)
        throw runtime_error("Start price has to be lower than or equal to endPrice");

    Sofa *crt = sp.getFirstProduct();

    while (crt != nullptr)
    {
        if (crt->getPrice() < startPrice)
            return;
        if (crt->getPrice() <= endPrice)
        {
            // remove crt object;
            Sofa *previousSofa = crt->getPrevious();
            Sofa *nextSofa = crt->getNext();
            if (previousSofa != nullptr && nextSofa != nullptr)
            {
                previousSofa->setNext(nextSofa);
                nextSofa->setPrevious(previousSofa);
            }
            else if (previousSofa != nullptr) // crt is last
            {
                previousSofa->setNext(nextSofa);
                sp.setLastProduct(previousSofa);
            }
            else if (nextSofa != nullptr)
            {
                nextSofa->setPrevious(previousSofa);
                sp.setFirstProduct(nextSofa);
            }
            else
            {
                sp.setFirstProduct(nullptr);
                sp.setLastProduct(nullptr);
            }
            delete crt;
            crt = nextSofa;
        }
        else
            crt = crt->getNext();
    }
}

void subpointD()
{
    SellingProduct sp;

    Sofa *classicSofa1 = new ClassicSofa(10.5, 20.5);
    Sofa *classicSofa2 = new ClassicSofa(2.5, 4.5);
    Sofa *sofaWithRoundArms1 = new SofaWithRoundArms(10.5, 24.5, 0.9);
    Sofa *sofaWithRoundArms2 = new SofaWithRoundArms(10.5, 24.5, 1.2);

    sp.addProductToSell(classicSofa1);
    sp.addProductToSell(classicSofa2);
    sp.addProductToSell(sofaWithRoundArms1);
    sp.addProductToSell(sofaWithRoundArms2);

    displayPricesInAscendingOrder(sp);
    removeSofaWithPriceInRange(sp, 50, 100);
}

int main()
{
}