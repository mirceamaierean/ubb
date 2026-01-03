#include <iostream>
#include <vector>
#include <thread>

using namespace std;

pair<int, int> decrypt(int index, int m)
{
    // 8 x 8
    return {index / m, index % m};
}

// {i, j} -> i * n + j
void compute(vector<vector<int>> &mat1, vector<vector<int>> &mat2, vector<vector<int>> &res, int start, int jump)
{
    // n x m
    // m x p
    // res: n x p
    int n = mat1.size();
    int m = mat1[0].size();
    int p = mat2[0].size();
    for (int index = start; index < n * p; index += jump)
    {
        auto per = decrypt(index, p);
        int i = per.first;
        int j = per.second;
        for (int k = 0; k < m; ++k)
        {
            res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

int main()
{
    int n = 50, m = 70, p = 100, t = 8;
    vector<vector<int>> mat1(n, vector<int>(m));
    vector<vector<int>> mat2(m, vector<int>(p));
    vector<vector<int>> res(n, vector<int>(p));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            mat1[i][j] = i + j;
        }
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < p; ++j)
        {
            mat2[i][j] = i + j;
        }
    }

    vector<thread> threads;
    threads.reserve(t);

    for (int i = 0; i < t; ++i)
    {
        threads.emplace_back(compute, ref(mat1), ref(mat2), ref(res), i, t);
    }

    for (int i = 0; i < t; ++i)
    {
        threads[i].join();
    }

    // for (int i = 0; i < n; ++i)
    // {
    //     for (int j = 0; j < p; ++j)
    //     {
    //         cout << res[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < p; ++j)
        {
            int correct = 0;
            for (int k = 0; k < m; ++k)
            {
                correct += mat1[i][k] * mat2[k][j];
            }
            if (res[i][j] != correct)
            {
                cout << "Incorrect result at " << i << " " << j << " " << res[i][j] << " " << correct << endl;
            }
        }
    }

    return 0;
}
