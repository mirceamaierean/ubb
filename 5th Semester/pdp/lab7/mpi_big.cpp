#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0)
    {
        // Master process computes low part
        karatsuba(a_lo, b_lo, lo);

        // Send high parts to other process
        MPI_Send(a_hi.data(), half, MPI_LONG_LONG, 1, 0, MPI_COMM_WORLD);
        MPI_Send(b_hi.data(), half, MPI_LONG_LONG, 1, 0, MPI_COMM_WORLD);

        // Receive the high result
        MPI_Recv(hi.data(), hi.size(), MPI_LONG_LONG, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if (world_rank == 1)
    {
        vector<long long> a_hi_recv(half), b_hi_recv(half);
        MPI_Recv(a_hi_recv.data(), half, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b_hi_recv.data(), half, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        karatsuba(a_hi_recv, b_hi_recv, hi);

        MPI_Send(hi.data(), hi.size(), MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);
    }

    // Sum the results on the master process
    if (world_rank == 0)
    {
        for (int i = 0; i < lo.size(); ++i)
        {
            sol[i] += lo[i];
        }

        for (int i = 0; i < hi.size(); ++i)
        {
            sol[i + 2 * half] += hi[i];
        }
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
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    vector<long long> a, b, c;

    if (world_rank == 0)
    {
        ifstream fin(filename);
        string nr1, nr2;
        int count_zeroes_for_1 = 0, count_zeroes_for_2 = 0;

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

        for (int i = nr1.size() - 1; i >= 0; --i)
        {
            a.push_back(nr1[i] - '0');
        }

        for (int i = nr2.size() - 1; i >= 0; --i)
        {
            b.push_back(nr2[i] - '0');
        }

        int new_size = find_next_power(max(a.size(), b.size()));
        padd(a, new_size);
        padd(b, new_size);
        c.resize(a.size() + b.size() - 1);
    }

    // Broadcast vectors to all processes
    int size_a, size_b;
    if (world_rank == 0)
    {
        size_a = a.size();
        size_b = b.size();
    }

    MPI_Bcast(&size_a, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&size_b, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank != 0)
    {
        a.resize(size_a);
        b.resize(size_b);
        c.resize(size_a + size_b - 1);
    }

    MPI_Bcast(a.data(), size_a, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(b.data(), size_b, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    karatsuba(a, b, c);

    if (world_rank == 0)
    {
        clean_zeroes(c);
        handle_as_numbers(c);
        reverse(c.begin(), c.end());

        cout << "Product: " << construct_result(c, 0) << endl;
    }
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    if (rank == 0)
    {
        if (argc != 2)
        {
            if (MPI::COMM_WORLD.Get_rank() == 0)
            {
                cout << "Usage: " << argv[0] << " <input_file>" << endl;
            }
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }

        solve(argv[1]);

        MPI_Finalize();
    }

    return 0;
}
