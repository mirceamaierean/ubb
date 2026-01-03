#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int compute_sequentially(vector<int> &a, vector<int> &b, int start, int end)
{
    if (start == end - 1)
        return a[start] * b[start];

    int mij = (start + end) / 2;
    
    return compute_sequentially(a, b, start, mij) + compute_sequentially(a, b, mij, end);
}

void compute(vector<int> &a, vector<int> &b, int start, int end, int &sum, mutex &mtx, int nr_threads)
{
    if (nr_threads == 1 || start == end - 1)
    {
        unique_lock<mutex> lock(mtx);
        sum += compute_sequentially(a, b, start, end);
        return;
    }

    int mij = (start + end) / 2;
    int half_threads = nr_threads / 2;

    thread t_left(compute, ref(a), ref(b), start, mij, ref(sum), ref(mtx), half_threads);             // 0 1 2 3 ... n / 2 - 1
    thread t_right(compute, ref(a), ref(b), mij, end, ref(sum), ref(mtx), nr_threads - half_threads); // n / 2, n / 2 + 1, n / 2 + 2 .. n

    t_left.join();
    t_right.join();
}

int main()
{
    int n = 6;
    int t = 8;
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
    compute(ref(a), ref(b), 0, n, ref(sum), ref(mtx), t);
    cout << sum << " " << correct_sum << endl;
    return 0;
}
