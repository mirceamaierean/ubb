#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <memory>

using namespace std;

struct Operation
{
    int serial;
    int amount;
    int source;
    int dest;
};

struct Serial
{
    int serial;
    mutex mtx;

    Serial() : serial(0) {}
};

const int ACCOUNTS = 100000000;
const int TRANSACTIONS = 1000000000;
const int INITIAL_AMOUNT = 100000;

int threadsCount = 8;

class Account
{
public:
    int id;
    long long balance;
    vector<Operation> logs;
    mutex mtx;

    Account(int id, int balance) : id(id), balance(balance)
    {
        logs = vector<Operation>();
    }

    // Account(const Account &) = delete;
    // Account &operator=(const Account &) = delete;

    void transfer(Account &dest, int amount, Serial &serial)
    {
        // Get the serial number, and increment it
        if (this->id < dest.id)
        {
            this->mtx.lock();
            dest.mtx.lock();
        }
        else
        {
            dest.mtx.lock();
            this->mtx.lock();
        }

        // cout << "Transfering " << amount << " from " << this->id << " to " << dest.id << endl;

        serial.mtx.lock();
        int serialValue = serial.serial;
        serial.serial++;
        serial.mtx.unlock();

        // Create the operation to be added to the logs
        Operation op = {serialValue, amount, this->id, dest.id};

        // Extract amount from the account
        balance -= amount;
        logs.push_back(op);

        // Add amount to the other account
        dest.balance += amount;
        dest.logs.push_back(op);

        if (this->id < dest.id)
        {
            this->mtx.unlock();
            dest.mtx.unlock();
        }
        else
        {
            dest.mtx.unlock();
            this->mtx.unlock();
        }
    }

    bool check()
    {
        int total = 0;
        for (Operation op : logs)
        {
            if (op.source == id)
            {
                total -= op.amount;
            }
            else
            {
                total += op.amount;
            }
        }
        return balance - total == INITIAL_AMOUNT;
    }
};

void performTransactions(vector<shared_ptr<Account>> &accounts, Serial &ser)
{
    for (int i = 0; i < TRANSACTIONS / threadsCount; ++i)
    {
        int source = rand() % ACCOUNTS;
        int dest = rand() % ACCOUNTS;
        while (source == dest)
        {
            dest = rand() % ACCOUNTS;
        }
        int amount = rand() % 1000;
        accounts[source]->transfer(*accounts[dest], amount, ser);
    }
}

bool continueCheck;

void check(vector<shared_ptr<Account>> &accounts, Serial &ser)
{
    try
    {
        while (continueCheck)
        {
            for (int i = 0; i < ACCOUNTS; ++i)
            {
                accounts[i]->mtx.lock();
            }
            cout << ser.serial << endl;
            bool ok = true;

            int rezXor = 0;
            for (int i = 0; i < ACCOUNTS; ++i)
            {
                ok &= accounts[i]->check();
                for (Operation op : accounts[i]->logs)
                {
                    rezXor ^= op.serial;
                }
            }
            if (rezXor != 0)
            {
                cout << "Serials are not properly placed" << endl;
                ok = false;
            }

            if (ok)
            {
                cout << "All accounts are correct" << endl;
            }
            else
            {
                cout << "Some accounts are incorrect" << endl;
            }

            for (int i = 0; i < ACCOUNTS; ++i)
            {
                accounts[i]->mtx.unlock();
            }

            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    // Catch exception when the mutex is destroyed
    catch (const std::exception &e)
    {
        cout << "Done checking" << endl;
    }
}

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        threadsCount = atoi(argv[1]);
    }

    continueCheck = true;

    cout << "Number of threads: " << threadsCount << endl;

    vector<shared_ptr<Account>> accounts;
    Serial ser;

    // Initialize accounts
    for (int i = 1; i <= ACCOUNTS; ++i)
    {
        accounts.push_back(make_shared<Account>(i, INITIAL_AMOUNT));
    }

    vector<thread> threads(threadsCount);

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < threadsCount; i++)
    {
        threads[i] = thread(performTransactions, ref(accounts), ref(ser));
    }

    thread checkThread = thread(check, ref(accounts), ref(ser));

    for (int i = 0; i < threadsCount; ++i)
    {
        threads[i].join();
    }

    auto end = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Total time taken: " << duration.count() << " miliseconds" << endl;

    continueCheck = false;

    cout << ser.serial << endl;
    cout << "All threads have finished" << endl;

    checkThread.detach();

    return 0;
}