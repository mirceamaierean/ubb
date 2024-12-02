// multiplication of 2 polynomial using regular sequential algorithm
// Input: 2 polynomials
// Output: product of 2 polynomials
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<long long> multiply(vector<long long> &a, vector<long long> &b)
{
    int n = a.size();
    int m = b.size();
    vector<long long> c(n + m - 1, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            c[i + j] += a[i] * b[j];
        }
    }
    return c;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    ifstream fin(argv[1]);
    ofstream fout("regular_sequential_output.txt");
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

    // multiply the 2 polynomials
    c = multiply(a, b);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Regular Sequential Time taken by function: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < c.size(); i++)
    {
        fout << c[i] << " ";
    }
    return 0;
}
