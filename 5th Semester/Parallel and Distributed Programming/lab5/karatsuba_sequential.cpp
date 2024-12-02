// multiplication of 2 polynomial using karatsuba sequential algorithm
// Input: 2 polynomials
// Output: product of 2 polynomials
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

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

    int half = a.size() / 2 + a.size() % 2;

    vector<long long> a_lo(a.begin(), a.begin() + half);
    vector<long long> a_hi(a.begin() + half, a.end());
    vector<long long> b_lo(b.begin(), b.begin() + half);
    vector<long long> b_hi(b.begin() + half, b.end());

    vector<long long> lo(a_lo.size() + b_lo.size() - 1);
    vector<long long> hi(a_hi.size() + b_hi.size() - 1);

    // lo = a_lo * b_lo
    karatsuba(a_lo, b_lo, lo);
    // hi = a_hi * b_hi
    karatsuba(a_hi, b_hi, hi);

    // mid = (a_lo + a_hi) * (b_lo + b_hi)
    for (int i = 0; i < a_hi.size(); ++i)
    {
        a_lo[i] += a_hi[i];
        b_lo[i] += b_hi[i];
    }

    vector<long long> mid(a_lo.size() + b_lo.size() - 1);
    karatsuba(a_lo, b_lo, mid);

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

void clean_zeroes(vector<long long> &c, int size)
{
    while (c.size() > size + 1)
    {
        c.pop_back();
    }
}

void padd(vector<long long> &v, int size)
{
    //  add 0s to make the size of the vector a power of 2
    for (int i = v.size(); i < size; ++i)
    {
        v.push_back(0);
    }
}

void solve(string filename)
{
    ifstream fin(filename);
    ofstream fout("karatsuba_sequential_output.txt");

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

    int new_polynomial_size = n + m;

    int new_size = find_next_power(max(n, m));

    padd(a, new_size);
    padd(b, new_size);
    vector<long long> sol(a.size() + b.size() - 1);

    auto start = high_resolution_clock::now();

    karatsuba(a, b, sol);
    clean_zeroes(sol, new_polynomial_size);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Karatsuba Sequential Time taken by function: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < sol.size(); i++)
    {
        fout << sol[i] << " ";
    }
}

int main(int argc, char *argv[])
{
    solve(argv[1]);
    return 0;
}