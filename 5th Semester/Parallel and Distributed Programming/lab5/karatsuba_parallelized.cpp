#include <iostream>
#include <fstream>
#include <vector>
#include <future>
#include <chrono>

using namespace std;
using namespace std::chrono;

void karatsuba(const vector<long long> &a, const vector<long long> &b, vector<long long> &sol)
{
    // base case, use regular multiplication
    if (a.size() <= 1024 && b.size() <= 1024)
    {
        for (int i = 0; i < a.size(); ++i)
        {
            for (int j = 0; j < b.size(); ++j)
            {
                sol[i + j] += a[i] * b[j];
            }
        }
        return;
    }

    int half = a.size() / 2;

    vector<long long> a_lo(a.begin(), a.begin() + half);
    vector<long long> a_hi(a.begin() + half, a.end());
    vector<long long> b_lo(b.begin(), b.begin() + half);
    vector<long long> b_hi(b.begin() + half, b.end());

    vector<long long> lo(a_lo.size() + b_lo.size() - 1);
    vector<long long> hi(a_hi.size() + b_hi.size() - 1);

    // lo = a_lo * b_lo
    auto future_lo = async(karatsuba, cref(a_lo), cref(b_lo), ref(lo));

    // hi = a_hi * b_hi
    auto future_hi = async(karatsuba, cref(a_hi), cref(b_hi), ref(hi));

    future_lo.get();
    future_hi.get();

    for (int i = 0; i < a_hi.size(); ++i)
    {
        a_lo[i] += a_hi[i];
        b_lo[i] += b_hi[i];
    }

    vector<long long> mid(a_lo.size() + b_lo.size() - 1);
    karatsuba(a_lo, b_lo, mid); // Sequential computation of mid

    // sol = x ^ 2 * half * hi + x * (mid - lo - hi) + lo
    for (int i = 0; i < lo.size(); ++i)
    {
        sol[i] += lo[i];
    }

    for (int i = 0; i < mid.size(); ++i)
    {
        sol[i + half] += mid[i] - lo[i] - hi[i];
    }

    for (int i = 0; i < hi.size(); ++i)
    {
        sol[i + 2 * half] += hi[i];
    }
}

int find_next_power(int n)
{
    int next_power = 1;
    while (next_power < n)
    {
        next_power *= 2;
    }
    return next_power;
}

void padd(vector<long long> &v, int size)
{
    for (int i = v.size(); i < size; ++i)
    {
        v.push_back(0);
    }
}

void clean_zeroes(vector<long long> &c, int size)
{
    while (c.size() > size + 1)
    {
        c.pop_back();
    }
}

void solve(string filename)
{
    ifstream fin(filename);
    ofstream fout("karatsuba_parallelized_output.txt");
    int n, m;
    vector<long long> a, b;
    fin >> n;
    for (int i = 0; i <= n; ++i)
    {
        int x;
        fin >> x;
        a.push_back(x);
    }
    fin >> m;
    for (int i = 0; i <= m; ++i)
    {
        int x;
        fin >> x;
        b.push_back(x);
    }

    int size_of_new_polynomial = n + m;

    int new_size = find_next_power(max(n + 1, m + 1));

    padd(a, new_size);
    padd(b, new_size);
    vector<long long> sol(a.size() + b.size() - 1);
    auto start = high_resolution_clock::now();

    karatsuba(a, b, sol);
    clean_zeroes(sol, size_of_new_polynomial);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Karatsuba Parallelized Time taken by function: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < sol.size(); i++)
    {
        fout << sol[i] << " ";
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    solve(argv[1]);
    return 0;
}
