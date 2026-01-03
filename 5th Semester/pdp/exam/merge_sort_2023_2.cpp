/*
    Since we give each available process a [worker], it means every process is expected to receive and send back data. However, when we have more processes than it is actually needed,
    we will reach a point where we will be calling [mergeSortLocal()] when [dataSize <= 1], but [nrProc > 1], meaning we won't be sending data to the remaining [nrProc] processes, which will be
    left waiting, causing a deadlock. To solve the issue, we can remove the condition [dataSize <= 1], and call [mergeSortLocal()] only when we don't have any more processes to split data
    towards. Indeed, in such a case we will send an empty vector having [dataSize = 0], but this won't be a problem, since it won't affect the final result. => (A)

    Another problem is related to the way we choose the next child, when [nrProc] is odd. Sure, it is a good idea to get [halfProc] to be on the upper bound of the result and send the bigger part to the child, while keeping the smaller part for the recursive call, but we have to consider such thing also when we set the id of [child], meaning that instead of skipping a number of positions equal to the bigger part, we need to skip a number of position equal to the smaller part. If we don't do such a thing, we risk getting out of bounds with how we assign processes. For example, let's say we have 3 processes. Process 0 will tell process [0 + (3 + 1) / 2 = 2] that it has to split data among other [(3 + 1) / 2 = 2] processes. While process 1 works, process 0 will continue the recursive call, with 1 more processes to split data between. Of course, this will go inside the first if clause and call [mergeSortLocal()], resulting in process 1 being unused and waiting. More than that, if we go back to process 2, process 2 will now try to split data between itself and process [2 + (2 + 1) / 2 = 3], which overflows the number of processes. => (C), (D).

    B: False, since we go recursively with [halfSize] and [dataSize - halfSize], thus ensuring the whole size is covered.
*/
/*
Consider the following excerpt from a program that is supposed to **merge-sort** a vector. The function worker() is called in all processes except process 0, the function mergeSort() is called from process 0 (and from the places described in this excerpt), the function mergeSortLocal() sorts the specified vector and the function mergeParts() merges two sorted adjacent vectors, given the pointer to the first element, the total length and the length of the first vector. Which of the following issues are present? Describe the changes needed to solve them.

>
A: the application can deadlock if the length of the vector is smaller than the number of MPI processes.
B: the application can produce a wrong result if the input vector size is not a power of 2.
C: some worker processes are not used if the number of processes is not a power of 2.
D: the application can deadlock if the number of processes is not a power of 2.
>
*/

// channel de comunicare:
// 1 - se trimite dataSize-ul (dimensiunea vectorului)
// 2 - se trimite nrProc (numarul de procese)
// 3 - se trimite vectorul
// 4 - se primeste vectorul sortat
// 8 workeri
#include <iostream>
#include <numeric>
#include <algorithm>
#include <mpi.h>

void mergeSortLocal(int *v, int dataSize)
{
    std::sort(v, v + dataSize);
}

void mergeParts(int *v, int dataSize, int halfSize)
{
    std::vector<int> aux(dataSize);
    std::merge(v, v + halfSize, v + halfSize, v + dataSize, aux.begin());
    std::copy(aux.begin(), aux.end(), v);
}
void mergeSort(int *v, int dataSize, int myId, int nrProc)
{
    if (nrProc == 1)
    { // if (nrProc == 1 || dataSize <= 1)
        mergeSortLocal(v, dataSize);
    }
    else
    {
        int halfSize = dataSize / 2;
        int halfProc = (nrProc + 1) / 2;
        int child;
        // child = myId + nrProc / 2; // JA
        child = myId + halfProc; // NEIN
        // 
        std::cout << "myId=" << myId << "; child=" << child << "; halfSize=" << halfSize << "; halfProc=" << halfProc << "; nrProc=" << nrProc << "\n";
        MPI_Ssend(&halfSize, 1, MPI_INT, child, 1, MPI_COMM_WORLD);
        MPI_Ssend(&halfProc, 1, MPI_INT, child, 2, MPI_COMM_WORLD);
        MPI_Ssend(v, halfSize, MPI_INT, child, 3, MPI_COMM_WORLD);
        mergeSort(v + halfSize, dataSize - halfSize, myId, nrProc - halfProc);
        MPI_Recv(v, halfSize, MPI_INT, child, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        mergeParts(v, dataSize, halfSize);
    }
}

void worker(int myId)
{
    MPI_Status status;
    int dataSize, nrProc;
    MPI_Recv(&dataSize, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
    auto parent = status.MPI_SOURCE;
    MPI_Recv(&nrProc, 1, MPI_INT, parent, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::vector<int> v(dataSize);
    MPI_Recv(v.data(), dataSize, MPI_INT, parent, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    mergeSort(v.data(), dataSize, myId, nrProc);
    MPI_Ssend(v.data(), dataSize, MPI_INT, parent, 4, MPI_COMM_WORLD);
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int me;
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    if (me == 0)
    {
        std::vector<int> v = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        // std::vector<int> v = {10, 9, 8, 7};
        mergeSort(v.data(), v.size(), me, size);
        for (auto &x : v)
        {
            std::cout << x << " ";
        }
    }
    else
    {
        worker(me);
        std::cout << "Worker " << me << " finished\n";
    }

    MPI_Finalize();
    return 0;
}