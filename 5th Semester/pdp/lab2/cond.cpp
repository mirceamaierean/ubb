#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>

using namespace std;

struct Prod
{
    queue<int> q;
    bool productReady, done;
    mutex mtx;
    condition_variable cv;
    long long result;
};

void performPairMultiplication(vector<pair<int, int>> &v, Prod &q)
{
    for (int i = 0; i < v.size(); ++i)
    {
        unique_lock<mutex> lock(q.mtx);
        cout << "Producing " << i << " " << v[i].first * v[i].second << endl;
        q.q.push(v[i].first * v[i].second);
        q.productReady = true;
        lock.unlock();
        q.cv.notify_one();
        lock.lock();
        q.cv.wait(lock, [&q]
                  { return !q.productReady; });
    }
    cout << "Done producing" << endl;
    unique_lock<mutex> lock(q.mtx);
    q.done = true;
    q.cv.notify_one();
}

void performAddition(Prod &q)
{
    this_thread::sleep_for(chrono::seconds(1));
    while (true)
    {
        unique_lock<mutex> lock(q.mtx);
        q.cv.wait(lock, [&q]
                  { return q.productReady || q.done; });
        if (q.done)
        {
            cout << "Done consuming" << endl;
            break;
        }
        cout << "Consuming " << q.q.front() << endl;
        q.result += q.q.front();
        q.q.pop();
        q.productReady = false;

        q.cv.notify_one();
    }
}

int main()
{
    vector<pair<int, int>> v;

    for (int i = 1; i <= 100000; ++i)
        v.push_back({i % 10, i % 10});

    cout << "Vector size: " << v.size() << endl;

    Prod q;
    q.done = false;
    q.productReady = false;
    q.result = 0;

    thread producer(performPairMultiplication, ref(v), ref(q));
    thread consumer(performAddition, ref(q));

    producer.join();
    consumer.join();
    cout << "Result: " << q.result << endl;

    return 0;
}