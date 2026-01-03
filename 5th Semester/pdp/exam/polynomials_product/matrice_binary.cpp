#include <mutex>
#include <iostream>
#include <vector>
#include <thread>
using namespace std;

int compute(int i_sus, int j_sus, int i_jos, int j_jos, vector<vector<int>> &mat)
{
    if (i_sus == i_jos && j_sus == j_jos)
    {
        return mat[i_sus][j_sus];
    }
    if (i_sus == i_jos)
    {
        int j_mid = (j_sus + j_jos) / 2;
        return compute(i_sus, j_sus, i_jos, j_mid, mat) + compute(i_sus, j_mid + 1, i_jos, j_jos, mat);
    }
    int i_mid = (i_sus + i_jos) / 2;
    return compute(i_sus, j_sus, i_mid, j_jos, mat) + compute(i_mid + 1, j_sus, i_jos, j_jos, mat);
}

void parallel_sum(int i_sus, int j_sus, int i_jos, int j_jos, vector<vector<int>> &mat, mutex &mtx, int &sum, int nr_threads)
{
    if (i_sus == i_jos && j_sus == j_jos)
    {
        unique_lock<mutex> lock(mtx);
        sum += mat[i_sus][j_sus];
        return;
    }

    if (nr_threads == 1)
    {
        unique_lock<mutex> lock(mtx);
        sum += compute(i_sus, j_sus, i_jos, j_jos, mat);
        return;
    }

    if (i_sus == i_jos)
    {
        int j_mij = (j_sus + j_jos) / 2;
        int half_threads = nr_threads / 2;
        thread t_left(parallel_sum, i_sus, j_sus, i_jos, j_mij, ref(mat), ref(mtx), ref(sum), half_threads);
        thread t_right(parallel_sum, i_sus, j_mij + 1, i_jos, j_jos, ref(mat), ref(mtx), ref(sum), nr_threads - half_threads);
        t_left.join();
        t_right.join();
        return;
    }

    int i_mij = (i_sus + i_jos) / 2;
    int half_threads = nr_threads / 2;
    thread t_up(parallel_sum, i_sus, j_sus, i_mij, j_jos, ref(mat), ref(mtx), ref(sum), half_threads);
    thread t_down(parallel_sum, i_mij + 1, j_sus, i_jos, j_jos, ref(mat), ref(mtx), ref(sum), nr_threads - half_threads);
    t_up.join();
    t_down.join();
}

int main()
{
    const int t = 7;
    int n = 100;
    vector<vector<int>> mat(n, vector<int>(n));
    int correct_sum = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            mat[i][j] = i + j;
            correct_sum += i + j;
        }
    }
    int sum = 0;
    mutex mtx;
    parallel_sum(0, 0, mat.size() - 1, mat[0].size() - 1, ref(mat), ref(mtx), ref(sum), t);
    cout << sum << " " << correct_sum << endl;
    return 0;
}
