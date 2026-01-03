#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void compute(vector<bool> &isPrime, vector<int> &primeNumbers, int start, int t)
{
    for (int i = start; i < primeNumbers.size(); i += t)
        for (int j = primeNumbers[i] * 2; j < isPrime.size(); j += primeNumbers[i])
            isPrime[j] = false;
}

void gatherPrimeNumbers(vector<bool> &isPrime, int start, int t, mutex &mtx, vector<int> &primeNumbers)
{
    for (int i = start; i < isPrime.size(); i += t)
        if (isPrime[i])
        {
            unique_lock<mutex> lock(mtx);
            primeNumbers.push_back(i);
        }
}

int main()
{
    int n = 500;
    vector<int> knownPrimeNumbers = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    vector<thread> threads;
    threads.reserve(8);

    for (int i = 0; i < 8; ++i)
        threads.emplace_back(compute, ref(isPrime), ref(knownPrimeNumbers), i, knownPrimeNumbers[i]);

    for (int i = 0; i < 8; ++i)
        threads[i].join();

    vector<int> primeNumbers;

    threads.clear();

    mutex mtx;

    for (int i = 0; i < 8; ++i)
        threads.emplace_back(gatherPrimeNumbers, ref(isPrime), i, 8, ref(mtx), ref(primeNumbers));

    for (int i = 0; i < 8; ++i)
        threads[i].join();

    sort(primeNumbers.begin(), primeNumbers.end());

    for (int i = 0; i < primeNumbers.size(); ++i)
    {
        cout << primeNumbers[i] << " ";
    }

    return 0;
}
