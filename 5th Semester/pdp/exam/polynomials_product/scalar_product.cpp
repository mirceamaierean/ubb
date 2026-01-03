#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int compute_sequentially(vector<int> &a, vector<int> &b, int start, int jump)
{
    // M jump + start
    // 0 8 16 24 32 ....
    // 1 9 17 25 33 .
    // ....
    // 7 15 23 31 39
    int sum = 0;
    for (int i = start; i < a.size(); i += jump)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

void compute(vector<int> &a, vector<int> &b, int start, int jump, int &sum, mutex &mtx, int nr_threads)
{
    if (nr_threads == 1)
    {
        unique_lock<mutex> lock(mtx);
        sum += compute_sequentially(a, b, start, jump);
        return;
    }

    int half_threads = nr_threads / 2;

    thread t_left(compute, ref(a), ref(b), start, jump, ref(sum), ref(mtx), half_threads);                              // 0 1 2 3 ... n / 2 - 1
    thread t_right(compute, ref(a), ref(b), start + half_threads, jump, ref(sum), ref(mtx), nr_threads - half_threads); // n / 2, n / 2 + 1, n / 2 + 2 .. n

    t_left.join();
    t_right.join();
}

int main()
{
    int n = 97;
    int t = 2;
    mutex mtx;
    int sum = 0, correct_sum = 0;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i)
    {
        a[i] = i;
        b[i] = i;
        correct_sum += i * i;
    }
    compute(ref(a), ref(b), 0, t, ref(sum), ref(mtx), t);
    cout << sum << " " << correct_sum << endl;
    return 0;
}
