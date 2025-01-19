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
int max_depth;

void fft(vector<complex<double>> &p, bool inverse, int depth = 0)
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

    if (depth < max_depth)
    {
        auto future1 = async(fft, ref(pe), inverse, depth + 1);
        auto future2 = async(fft, ref(po), inverse, depth + 1);
        future1.get();
        future2.get();
    }
    else
    {
        fft(pe, inverse, depth + 1);
        fft(po, inverse, depth + 1);
    }

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

vector<long long> multiply(vector<long long> const &a, vector<long long> const &b)
{
    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int polynomial_size = a.size() + b.size();
    int n = 1;

    while (n < a.size() + b.size())
        n <<= 1;

    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());

    while (result.size() >= polynomial_size)
        result.pop_back();

    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << " <depth> " << endl;
        return 1;
    }
    ifstream fin(argv[1]);
    ofstream fout("fft_parallelized_output.txt");
    max_depth = atoi(argv[2]);
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

    auto start = high_resolution_clock::now();
    c = multiply(a, b);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "FFT Parallelized Execution Time: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < c.size(); i++)
    {
        fout << c[i] << " ";
    }

    fout << '\n';

    return 0;
}