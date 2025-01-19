#include <iostream>
#include <fstream>
#include <vector>
#include <future>
#include <mpi.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Base case multiplication for small sizes
void karatsuba_base(const vector<long long> &a, const vector<long long> &b, vector<long long> &sol)
{
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < b.size(); ++j)
        {
            sol[i + j] += a[i] * b[j];
        }
    }
}

// Karatsuba algorithm adapted for MPI
void karatsuba_mpi(const vector<long long> &a, const vector<long long> &b, vector<long long> &sol, int rank, int size)
{
    int n = a.size();

    if (n <= 1024)
    { // Base case: use regular multiplication for small sizes
        karatsuba_base(a, b, sol);
        return;
    }

    cout << "Rank: " << rank << " Size: " << size << endl;

    int half = n / 2;

    vector<long long> a_lo(a.begin(), a.begin() + half);
    vector<long long> a_hi(a.begin() + half, a.end());
    vector<long long> b_lo(b.begin(), b.begin() + half);
    vector<long long> b_hi(b.begin() + half, b.end());

    vector<long long> lo(a_lo.size() + b_lo.size() - 1);
    vector<long long> hi(a_hi.size() + b_hi.size() - 1);
    vector<long long> mid(a_lo.size() + b_lo.size() - 1);

    if (rank == 0)
    {
        // Send sub-tasks to other ranks
        MPI_Send(a_lo.data(), half, MPI_LONG_LONG, 1, 0, MPI_COMM_WORLD);
        MPI_Send(b_lo.data(), half, MPI_LONG_LONG, 1, 0, MPI_COMM_WORLD);

        MPI_Send(a_hi.data(), half, MPI_LONG_LONG, 2, 0, MPI_COMM_WORLD);
        MPI_Send(b_hi.data(), half, MPI_LONG_LONG, 2, 0, MPI_COMM_WORLD);

        // Receive results
        MPI_Recv(lo.data(), lo.size(), MPI_LONG_LONG, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(hi.data(), hi.size(), MPI_LONG_LONG, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Compute mid locally
        for (int i = 0; i < a_hi.size(); ++i)
        {
            a_lo[i] += a_hi[i];
            b_lo[i] += b_hi[i];
        }
        karatsuba_base(a_lo, b_lo, mid);

        // Combine results
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
    else if (rank == 1)
    {
        // Rank 1 computes lo = a_lo * b_lo
        MPI_Recv(a_lo.data(), half, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b_lo.data(), half, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        karatsuba_base(a_lo, b_lo, lo);
        MPI_Send(lo.data(), lo.size(), MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }
    else if (rank == 2)
    {
        // Rank 2 computes hi = a_hi * b_hi
        MPI_Recv(a_hi.data(), half, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b_hi.data(), half, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        karatsuba_base(a_hi, b_hi, hi);
        MPI_Send(hi.data(), hi.size(), MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }
}

// Function to pad polynomials to the nearest power of 2
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

void solve(string filename)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    vector<long long> a, b;
    int n = 0, m = 0;

    if (rank == 0)
    { // Root process reads input
        ifstream fin(filename);
        if (!fin)
        {
            cerr << "Error opening input file." << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fin >> n;
        a.resize(n + 1);
        for (int i = 0; i <= n; ++i)
        {
            fin >> a[i];
        }

        fin >> m;
        b.resize(m + 1);
        for (int i = 0; i <= m; ++i)
        {
            fin >> b[i];
        }
        fin.close();
    }

    // Broadcast sizes to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0)
    {
        a.resize(n + 1);
        b.resize(m + 1);
    }

    // Broadcast polynomial coefficients
    MPI_Bcast(a.data(), n + 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(b.data(), m + 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    int size_of_new_polynomial = n + m;
    int new_size = find_next_power(max(n + 1, m + 1));

    padd(a, new_size);
    padd(b, new_size);

    vector<long long> sol(a.size() + b.size() - 1, 0);

    auto start = high_resolution_clock::now();

    karatsuba_mpi(a, b, sol, rank, size);

    if (rank == 0)
    {
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "MPI Karatsuba Time: " << duration.count() << " microseconds" << endl;

        // Save result to output file
        ofstream fout("mpi_kar_output.txt");
        for (int i = 0; i < sol.size(); ++i)
        {
            fout << sol[i] << " ";
        }
        fout.close();
        cout << "Result written to karatsuba_mpi_output.txt" << endl;
    }
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    if (rank == 0)
    {
        if (argc != 2)
        {
            cout << "Usage: " << argv[0] << " <input_file>" << endl;
            MPI_Finalize();
            return 1;
        }

        solve(argv[1]);

        MPI_Finalize();
    }
    return 0;
}
