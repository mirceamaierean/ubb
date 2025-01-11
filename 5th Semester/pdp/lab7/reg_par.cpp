// multiplication of 2 polynomial using regular parallelized algorithm
// Input: 2 polynomials
// Output: product of 2 polynomials
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int THREADS = 8;

void worker(vector<long long> &a, vector<long long> &b, vector<long long> &c, int index)
{
    int n = a.size();
    int m = b.size();
    for (int i = index; i < n + m; i += THREADS)
    {
        for (int j = 0; j <= i; ++j)
        {
            if (j < n && i - j < m)
                c[i] += a[j] * b[i - j];
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    ifstream fin(argv[1]);
    ofstream fout("reg_par_output.txt");
    int n, m;
    vector<long long> a, b, c;
    fin >> n;
    for (int i = 0; i <= n; i++)
    {
        int x;
        fin >> x;
        a.push_back(x);
    }
    fin >> m;
    for (int i = 0; i <= m; i++)
    {
        int x;
        fin >> x;
        b.push_back(x);
    }
    vector<thread> threads;

    c.resize(n + m + 1, 0);

    auto start = high_resolution_clock::now();

    for (int i = 0; i < THREADS; ++i)
    {
        threads.push_back(thread(worker, ref(a), ref(b), ref(c), i));
    }

    for (int i = 0; i < THREADS; ++i)
    {
        threads[i].join();
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Regular Parallelized Time taken by function: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < c.size(); i++)
    {
        fout << c[i] << " ";
    }
    return 0;
}