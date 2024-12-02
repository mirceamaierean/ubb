// multiplication of 2 polynomial using karatsuba sequential algorithm
// Input: 2 polynomials
// Output: product of 2 polynomials
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <future>
#include <chrono>

using namespace std;
using namespace std::chrono;

void karatsuba(const vector<long long> &a, const vector<long long> &b, vector<long long> &sol)
{
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

    // Parallelize low and high karatsubaiplications
    auto future_lo = async(karatsuba, cref(a_lo), cref(b_lo), ref(lo));
    auto future_hi = async(karatsuba, cref(a_hi), cref(b_hi), ref(hi));

    vector<long long> sum_a = a_lo;
    vector<long long> sum_b = b_lo;
    for (int i = 0; i < a_hi.size(); ++i)
    {
        sum_a[i] += a_hi[i];
    }
    for (int i = 0; i < b_hi.size(); ++i)
    {
        sum_b[i] += b_hi[i];
    }

    vector<long long> mid(sum_a.size() + sum_b.size() - 1);
    karatsuba(sum_a, sum_b, mid);

    future_lo.get();
    future_hi.get();

    for (int i = 0; i < lo.size(); ++i)
    {
        sol[i] += lo[i];
    }

    for (int i = 0; i < mid.size(); ++i)
    {
        sol[i + half] += mid[i] - lo[i] - (i < hi.size() ? hi[i] : 0);
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

void clean_zeroes(vector<long long> &c)
{
    while (c.size() > 1 && c.back() == 0)
    {
        c.pop_back();
    }
}

void handle_as_numbers(vector<long long> &c)
{
    int carry = 0;
    for (int i = 0; i < c.size(); i++)
    {
        c[i] += carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
    while (carry)
    {
        c.push_back(carry % 10);
        carry /= 10;
    }
}

string construct_result(vector<long long> &c, int zeroes_to_add)
{
    string result = "";
    for (int i = 0; i < c.size(); i++)
    {
        result += to_string(c[i]);
    }
    while (zeroes_to_add--)
    {
        result += "0";
    }
    return result;
}

void solve(string filename)
{
    ifstream fin(filename);
    ofstream fout("big_numbers.txt");
    vector<long long> a, b, c;
    int count_zeroes_for_1 = 0, count_zeroes_for_2 = 0;
    string nr1, nr2;

    fin >> nr1 >> nr2;

    while (nr1.size() && nr1.back() == '0')
    {
        count_zeroes_for_1++;
        nr1.pop_back();
    }

    while (nr2.size() && nr2.back() == '0')
    {
        count_zeroes_for_2++;
        nr2.pop_back();
    }

    if (nr1.size() == 0 || nr2.size() == 0)
    {
        fout << 0 << endl;
        return;
    }

    for (int i = nr1.size() - 1; i >= 0; --i)
    {
        a.push_back(nr1[i] - '0');
    }

    for (int i = nr2.size() - 1; i >= 0; --i)
    {
        b.push_back(nr2[i] - '0');
    }

    int size_of_new_polynomial = a.size() + b.size();

    int new_size = find_next_power(max(a.size(), b.size()));

    padd(a, new_size);
    padd(b, new_size);

    vector<long long> sol(a.size() + b.size() - 1);

    karatsuba(a, b, sol);

    clean_zeroes(sol);

    handle_as_numbers(sol);

    reverse(sol.begin(), sol.end());

    cout << construct_result(sol, count_zeroes_for_1 + count_zeroes_for_2) << endl;
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
