#include <mpi.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function for multiplication
void worker(vector<long long> &a, vector<long long> &b, vector<long long> &c, int index, int nr_processes)
{
    int n = a.size();
    int m = b.size();
    for (int i = index; i < n + m; i += nr_processes)
    {
        for (int j = 0; j <= i; ++j)
        {
            if (j < n && i - j < m)
                c[i] += a[j] * b[i - j];
        }
    }
}

void read_input(const char *filename, vector<long long> &a, vector<long long> &b, vector<long long> &c, int &n, int &m)
{
    ifstream fin(filename);
    fin >> n;
    a.resize(n + 1);
    for (int i = 0; i <= n; ++i)
        fin >> a[i];
    fin >> m;
    b.resize(m + 1);
    for (int i = 0; i <= m; ++i)
        fin >> b[i];
    c.resize(n + m + 1, 0);
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    vector<long long> a, b, c;
    int n, m;

    if (rank == 0)
    {
        if (argc != 2)
        {
            cout << "Usage: " << argv[0] << " <input_file>" << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        read_input(argv[1], a, b, c, n, m);
    }

    // Broadcast sizes to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0)
    {
        a.resize(n + 1);
        b.resize(m + 1);
    }

    MPI_Bcast(a.data(), n + 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(b.data(), m + 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    int total_size = n + m + 1;
    vector<long long> local_c(total_size, 0);

    auto start_time = high_resolution_clock::now();

    worker(a, b, local_c, rank, size);

    MPI_Reduce(local_c.data(), c.data(), total_size, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    auto end_time = high_resolution_clock::now();

    if (rank == 0)
    {
        ofstream fout("mpi_reg_par_output.txt");

        for (int i = 0; i < c.size(); ++i)
            fout << c[i] << " ";

        auto duration = duration_cast<microseconds>(end_time - start_time);
        cout << "MPI Parallel Time taken by function: " << duration.count() << " microseconds" << endl;
    }

    MPI_Finalize();
    return 0;
}
