#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void compute(vector<int> &a, vector<int> &b, vector<int> &c, int start, int jump)
{
    // a.size() - gradul polinomului + 1
    // a.size() = 3 -> polinom de grad 2
    for (int i = start; i < a.size() + b.size() - 1; i += jump)
    {
        for (int j = 0; j < b.size(); ++j)
        {
            // a_i + b_j = c_(i + j)
            // a_[i - j] * b_j = c_i
            int k = i - j;
            if (k >= 0 && k < a.size())
                c[i] += a[k] * b[j];
        }
    }
}

int main(int argc, char **argv)
{
    
    int n = 53, m = 46, t = 8;
    vector<int> a(n + 1);
    vector<int> b(m + 1);
    vector<int> c(n + m + 1, 0);
    for (int i = 0; i < n + 1; ++i)
    {
        a[i] = i + 1;
    }
    for (int i = 0; i < m + 1; ++i)
    {
        b[i] = i + 1;
    }
    vector<thread> threads;
    threads.reserve(t);

    for (int i = 0; i < t; ++i)
    {
        threads.emplace_back(compute, ref(a), ref(b), ref(c), i, t);
    }

    for (int i = 0; i < t; ++i)
        threads[i].join();

    for (int i = 0; i < c.size(); ++i)
    {
        cout << c[i] << " ";
    }
    // check if the result is correct
    for (int i = 0; i < c.size(); ++i)
    {
        int sum = 0;
        for (int j = 0; j < a.size(); ++j)
        {
            if (i - j >= 0 && i - j < b.size())
                sum += a[j] * b[i - j];
        }
        if (sum != c[i])
        {
            cout << "Incorrect result at index " << i << " expected " << sum << " got " << c[i] << endl;
            break;
        }
    }
    return 0;
}
