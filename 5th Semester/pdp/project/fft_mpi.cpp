#include <mpi.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <cmath>
#include <functional>
#include <future>

using namespace std;
using namespace std::chrono;

const double pi = acos(-1);

void fft(vector<complex<double>> &p, bool inverse)
{
    int n = p.size();
    if (n == 1)
        return;
    vector<complex<double>> pe(n / 2), po(n / 2);
    for (int i = 0; i < n / 2; ++i)
    {
        pe[i] = p[2 * i];
        po[i] = p[2 * i + 1];
    }

    fft(pe, inverse);
    fft(po, inverse);

    double theta = 2.00 * pi / n * (inverse ? -1 : 1);
    complex<double> w(1), wn(cos(theta), sin(theta));
    for (int i = 0; i < n / 2; ++i)
    {
        p[i] = pe[i] + w * po[i];
        p[i + n / 2] = pe[i] - w * po[i];
        if (inverse)
        {
            p[i] /= 2;
            p[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

vector<long long> multiply(vector<long long> const &a, vector<long long> const &b, int rank, int size)
{
    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int polynomial_size = a.size() + b.size(); // Store the expected size
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    // Broadcast the input arrays to all processes
    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Send(fa.data(), n * 2, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(fb.data(), n * 2, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(fa.data(), n * 2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(fb.data(), n * 2, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Perform FFT
    fft(fa, false);
    fft(fb, false);

    // Distribute multiplication work
    int chunk_size = n / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? n : (rank + 1) * chunk_size;

    // Perform multiplication for this process's chunk
    for (int i = start; i < end; i++)
        fa[i] *= fb[i];

    // Gather results back to process 0
    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            int recv_start = i * chunk_size;
            int recv_size = (i == size - 1) ? (n - recv_start) : chunk_size;
            MPI_Recv(fa.data() + recv_start, recv_size * 2, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    else
    {
        MPI_Send(fa.data() + start, (end - start) * 2, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    // Only process 0 performs the inverse FFT and final processing
    if (rank == 0)
    {
        fft(fa, true);
        vector<long long> result(n);
        for (int i = 0; i < n; i++)
            result[i] = round(fa[i].real());

        // Trim the result to the correct polynomial size
        while (result.size() >= polynomial_size)
            result.pop_back();

        return result;
    }

    return vector<long long>(); // Non-root processes return empty vector
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2 && rank == 0)
    {
        cout << "Usage: " << argv[0] << " <input_file>\n";
        MPI_Finalize();
        return 1;
    }

    vector<long long> a, b, c;
    if (rank == 0)
    {
        ifstream fin(argv[1]);

        int n, m;
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
    }

    // Broadcast sizes of vectors
    int size_a = a.size();
    int size_b = b.size();
    MPI_Bcast(&size_a, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&size_b, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Resize vectors on non-root processes
    if (rank != 0)
    {
        a.resize(size_a);
        b.resize(size_b);
    }

    // Broadcast vector contents
    MPI_Bcast(a.data(), size_a, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(b.data(), size_b, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    auto start = high_resolution_clock::now();
    c = multiply(a, b, rank, size);
    auto end = high_resolution_clock::now();

    if (rank == 0)
    {
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "FFT MPI Execution Time: " << duration.count() << " microseconds" << endl;

        ofstream fout("fft_mpi_output.txt");
        for (int i = 0; i < c.size(); i++)
        {
            fout << c[i] << " ";
        }
        fout << '\n';
    }

    MPI_Finalize();
    return 0;
}