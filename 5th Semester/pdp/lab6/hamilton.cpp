#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;
using namespace std::chrono;

ifstream fin("graph.in");
ofstream fout("graph.out");

const int NMAX = 1001;
const int NR_THREADS = 18;

int n, m;

vector<vector<int>> g;

atomic<int> threads_count(0);
atomic<bool> found(false);

void read()
{
    fin >> n >> m;
    int x, y;
    g = vector<vector<int>>(n);
    for (int i = 0; i < m; ++i)
    {
        fin >> x >> y;
        g[x].push_back(y);
    }
}

void write(const vector<int> &sol)
{
    for (auto &x : sol)
        fout << x << " ";
    fout << sol[0];
}

bool is_edge(int &x, int &y)
{
    for (auto &node : g[x])
        if (node == y)
            return true;
    return false;
}

bool find_cycle(int node, vector<int> &sol, bitset<NMAX> visited)
{
    if (found.load(memory_order_relaxed))
        return false;

    sol.push_back(node);
    visited[node] = 1;

    if (sol.size() == n)
    {
        if (is_edge(sol.back(), sol[0]))
        {
            found.store(true, memory_order_relaxed);
            return true;
        }
        return false;
    }

    if (g[node].size() == 0)
        return false;

    if (g[node].size() > 1)
    {
        int prev_threads_count = threads_count.load(memory_order_relaxed);
        while (!found.load(memory_order_relaxed) && prev_threads_count + 2 <= NR_THREADS)
        {
            if (threads_count.compare_exchange_strong(prev_threads_count, prev_threads_count + 2, memory_order_relaxed))
            {
                bool sol_even = false, sol_odd = false;
                vector<int> sol_found_even = sol, sol_found_odd = sol;

                thread t_even([&]()
                              { for (int i = 0; i < g[node].size() && !found.load(memory_order_relaxed); i += 2)
                    if (!visited[g[node][i]])
                       {
                            if (find_cycle(g[node][i], sol_found_even, visited))
                            {
                                sol_even = true;
                                break;
                            }
                       } });

                thread t_odd([&]()
                             { for (int i = 1; i < g[node].size() && !found.load(memory_order_relaxed); i += 2)
                    if (!visited[g[node][i]])
                          {
                             if (find_cycle(g[node][i], sol_found_odd, visited))
                             {
                                  sol_odd = true;
                                  break;
                             }
                          } });

                t_even.join();
                t_odd.join();

                threads_count.fetch_sub(2, memory_order_relaxed);
                if (sol_even)
                {
                    sol = sol_found_even;
                    return true;
                }
                if (sol_odd)
                {
                    sol = sol_found_odd;
                    return true;
                }

                return false;
            }
            else
            {
                prev_threads_count = threads_count.load(memory_order_relaxed);
            }
        }
    }

    if (!visited[g[node][0]])
    {
        vector<int> sol_branch = sol;
        auto visited_copy = visited;
        if (find_cycle(g[node][0], sol_branch, visited_copy))
        {
            sol = sol_branch;
            return true;
        }
    }
    return false;
}

int main()
{
    read();

    vector<int> sol;
    bitset<NMAX> visited;
    visited.reset();

    auto start = high_resolution_clock::now();
    if (find_cycle(0, sol, visited))
        write(sol);
    else
        fout << "No hamiltonian cycle found";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    return 0;
}