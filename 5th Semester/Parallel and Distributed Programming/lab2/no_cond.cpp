#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>

using namespace std;

struct Queue
{
    queue<int> q;
    bool done;
    mutex m;
    unsigned long long result;
};

void performPairMultiplication(vector<pair<int, int>> &v, Queue &q)
{
    int index = 0;
    while (index < v.size())
    {
        unique_lock<mutex> lock(q.m);
        if (q.q.size())
        {
            lock.unlock();
            continue;
        }
        // cout << "Producing " << v[index].first * v[index].second << endl;
        q.q.push(v[index].first * v[index].second);
        ++index;
        lock.unlock();
    }
    unique_lock<mutex> lock(q.m);
    q.done = true;
    lock.unlock();
}

void performAddition(Queue &q)
{
    int sum = 0;
    while (true)
    {
        unique_lock<mutex> lock(q.m);
        if (q.q.size())
        {
            // cout << "Consuming " << q.q.front() << endl;
            sum += q.q.front();
            q.q.pop();
        }
        else if (q.done)
        {
            break;
        }
        lock.unlock();
    }
    q.result = sum;
}

int main()
{
    vector<pair<int, int>> v;

    for (int i = 1; i <= 100000; ++i)
        v.push_back({i % 10, i % 10});

    cout << "Vector size: " << v.size() << endl;
    Queue q;
    q.done = false;

    thread producer(performPairMultiplication, ref(v), ref(q));
    thread consumer(performAddition, ref(q));

    producer.join();
    consumer.join();
    cout << "Result: " << q.result << endl;

    return 0;
}