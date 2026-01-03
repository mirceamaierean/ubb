/* The following program solves, through parallel explore, the following problem (known NP-hard):
* Given a set of objects with positive integer values, split it into two subsets, each having the same sum
    of the values of their objects. Only one solution is required if multiple solutions exist.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <future>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <numeric>

// Class that contains all the input data, plus the first solution found
class Solver
{
public:
    const std::vector<int> values; // the values of the objects (input vector)
    const int fullSum;             // the sum of values of all objects
    const int halfSum;             // half of the sum; this is the target value for the sum of the subset
    std::atomic<int> found;        // true if a solution has been found
    std::vector<bool> solution;    // the solution, if found

    // Constructor; just sets the input data (including the target sum) and initializes the output as "no solution found"
    explicit Solver(std::vector<int> v)
        : values(std::move(v)),
          fullSum(std::accumulate(values.begin(), values.end(), 0)),
          halfSum(fullSum / 2),
          found(0)
    {
        // nothing else
    }

    // Entry point for the solving process
    void solve(unsigned nrThreads)
    {
        if (fullSum % 2 != 0)
            return; // odd total sum - cannot be split evenly
        std::vector<bool> subset(values.size(), false);
        search(subset, 0, halfSum, nrThreads);
    }

    // Recursively searches a sub-tree of the search space.
    // subset A description of the prefix of the searched solutions. Each "true" value means that the corresponding object is selected into the subset; a "false"
    //    means that the object is not selected
    // pos The length of the prefix that is already decided. The function will try only solutions starting with the choices already made for objects from 0 to pos-1
    //    and will only try to explore what to do with the objects from position pos to values.size()-1
    // targetSum The sum of the values of the objects to be put in the set, in addition to those already put (up to pos-1).
    // nrThreads number of threads to be used in searching this part of the search space
    void search(std::vector<bool> &subset, size_t pos, int targetSum, unsigned nrThreads)
    {
        if (found != 0)
            return; // if another thread has already found a solution, we stop the search.
        if (pos >= values.size())
        {
            // We have a complete solution candidate, so we check it if it really is a solution
            if (targetSum == 0)
            {
                // solution found
                int wasFound = found.fetch_or(1);
                if (wasFound == 0)
                {
                    // we are the first, so we shall record our solution
                    solution = subset;
                }
            }
            return;
        }
        // No complete candidate. We shall check both possibilities for the next object (put it into the solution candidate or skip it)
        if (nrThreads > 1)
        {
            // At least two threads available. Check the two possibilities on separate threads
            std::vector<bool> subset2 = subset;
            subset2[pos] = false;
            std::future<void> other = std::async(std::launch::async, [this, pos, &subset2, targetSum, nrThreads]()
                                                 { search(subset2, pos + 1, targetSum, nrThreads / 2); });
            subset[pos] = true;
            search(subset, pos + 1, targetSum - values[pos], nrThreads - nrThreads / 2);
            other.wait();
        }
        else
        {
            // Only one thread available. Check sequentially on the same thread.
            subset[pos] = false;
            search(subset, pos + 1, targetSum, 1);
            subset[pos] = true;
            search(subset, pos + 1, targetSum - values[pos], 1);
        }
    }
};

int main()
{
    long long nrThreads = 5;
    std::vector<int> values{1, 9, 4, 6, 10, 3, 7, 20, 1, 18, 36, 28, 37, 16, 28, 39, 74, 26, 33};

    Solver solver(std::move(values));
    solver.solve(nrThreads);

    if (solver.found)
    {
        for (unsigned i = 0; i < solver.values.size(); ++i)
        {
            if (solver.solution[i])
            {
                printf("%d ", solver.values[i]);
            }
        }
        printf("\n");
    }
    else
    {
        printf("impossible\n");
    }
    return 0;
}