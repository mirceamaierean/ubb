#include <iostream>

using namespace std;

class Channel
{
public:
  virtual void send(string message = "") const = 0;
  virtual ~Channel(){};
};

class Telephone : public Channel
{
private:
  string number;

public:
  Telephone(string number = "") : number{number} {};
  virtual void send(string messages = "") const override
  {
    srand(time(NULL));
    int r = rand() % 4;
    if (r == 0)
      throw runtime_error("Line is busy");
    cout << "Dialing " << this->number << '\n';
  }
};

class Fax : public Telephone
{
public:
  Fax(string number = "") : Telephone{number} {};
  void send(string message = "") const override
  {
    Telephone::send(message);
    cout << "sending fax\n";
  }
};

class SMS : public Telephone
{
public:
  SMS(string number = "") : Telephone{number} {};
  void send(string message = "") const override
  {
    Telephone::send(message);
    cout << "sending sms\n";
  }
};

class Failover : public Channel
{
private:
  Channel *channel1, *channel2;

public:
  Failover(Channel *channel1, Channel *channel2) : channel1{channel1}, channel2{channel2} {};
  ~Failover()
  {
    delete channel1;
    delete channel2;
  }
  void send(string message = "") const override
  {
    try
    {
      channel1->send();
    }
    catch (runtime_error &ex)
    {
      channel2->send();
    }
  }
};

class Contact
{
private:
  Channel *channel1, *channel2, *channel3;

public:
  Contact(Channel *channel1, Channel *channel2, Channel *channel3) : channel1{channel1}, channel2{channel2}, channel3{channel3} {};
  ~Contact()
  {
    delete channel1;
    delete channel2;
    delete channel3;
  }
  void sendAlarm(string message = "")
  {
    while (1)
    {
      try
      {
        channel1->send(message);
        return;
      }
      catch (runtime_error &e)
      {
        std::cout << "am prins eroare la 1\n";
      }
      try
      {
        channel2->send(message);
        return;
      }
      catch (runtime_error &e)
      {
        std::cout << "am prins eroare la 2\n";
      }
      try
      {
        channel3->send(message);
        return;
      }
      catch (runtime_error &e)
      {
        std::cout << "am prins eroare la 3\n";
      }
    }
  }
};

void createContact()
{
  Channel *telephone = new Telephone("0773");

  Channel *fax = new Fax("0773");
  Channel *sms = new SMS("0773");
  Channel *failover = new Failover(fax, sms);

  Channel *telephone2 = new Telephone();
  Channel *fax2 = new Fax("0773");
  Channel *sms2 = new SMS("0773");
  Channel *failover2 = new Failover(fax2, sms2);

  Channel *failover3 = new Failover(telephone2, failover2);

  Contact contact(telephone, failover, failover3);

  contact.sendAlarm("mesaj boss");
}

int main()
{
  createContact();
  return 0;
}