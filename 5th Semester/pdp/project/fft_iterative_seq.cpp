#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

const double PI = acos(-1);

void iterative_fft(vector<complex<double>> &p, bool inverse)
{
    int n = p.size();
    vector<complex<double>> temp(n);

    int log_n = log2(n);
    for (int i = 0; i < n; ++i)
    {
        int reversed = 0, x = i;
        for (int j = 0; j < log_n; ++j)
        {
            reversed = (reversed << 1) | (x & 1);
            x >>= 1;
        }
        if (i < reversed)
            swap(p[i], p[reversed]);
    }

    // Iterative FFT
    for (int len = 2; len <= n; len <<= 1)
    {
        double theta = 2.0 * PI / len * (inverse ? -1 : 1);
        complex<double> wn(cos(theta), sin(theta));
        for (int i = 0; i < n; i += len)
        {
            complex<double> w(1);
            for (int j = 0; j < len / 2; ++j)
            {
                complex<double> u = p[i + j];
                complex<double> v = w * p[i + j + len / 2];
                p[i + j] = u + v;
                p[i + j + len / 2] = u - v;
                w *= wn;
            }
        }
    }

    // Scaling for inverse FFT
    if (inverse)
    {
        for (auto &x : p)
            x /= n;
    }
}

vector<long long> multiply(vector<long long> const &a, vector<long long> const &b)
{
    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int polynomial_size = a.size() + b.size();
    int n = 1;

    while (n < a.size() + b.size())
        n <<= 1;

    fa.resize(n);
    fb.resize(n);

    // Perform FFT on both polynomials
    iterative_fft(fa, false);
    iterative_fft(fb, false);

    for (int i = 0; i < n; ++i)
    {
        fa[i] *= fb[i];
    }

    // Perform inverse FFT on the root process
    iterative_fft(fa, true);

    vector<long long> final_result(n);
    for (int i = 0; i < n; i++)
        final_result[i] = round(fa[i].real());

    while (final_result.size() >= polynomial_size)
        final_result.pop_back();

    return final_result;
}

int main(int argc, char *argv[])
{
    vector<long long> a, b, c;

    // Input polynomials from file
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    int n, m;
    fin >> n;
    a.resize(n + 1);
    for (int i = 0; i <= n; i++)
        fin >> a[i];

    fin >> m;
    b.resize(m + 1);
    for (int i = 0; i <= m; i++)
        fin >> b[i];

    fin.close();

    auto start = high_resolution_clock::now();

    c = multiply(a, b);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    ofstream fout("fft_it_output.txt");
    cout << "FFT Iterative Multiplication Execution Time: " << duration.count() << " microseconds" << endl;
    for (size_t i = 0; i < c.size(); ++i)
        fout << c[i] << " ";
    fout << '\n';

    return 0;
}
