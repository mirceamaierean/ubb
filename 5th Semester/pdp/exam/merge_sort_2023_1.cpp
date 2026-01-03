/*
    1) deadlock nrProc > dataSize
    2) nextChild odd number of processes

    Since we give each available process a [worker], it means every process is expected to receive and send back data. However, when we have more processes than it is actually needed, we will reach a point where we will be calling [mergeSortLocal()] when [dataSize <= 1], but [nrProc > 1], meaning we won't be sending data to the remaining [nrProc] processes, which will be left waiting, causing a deadlock. To solve the issue, we can remove the condition [dataSize <= 1], and call [mergeSortLocal()] only when we don't have any more processes to split data towards. Indeed, in such a case we will send an empty vector having [dataSize = 0], but this won't be a problem, since it won't affect the final result. => (A)

    Another problem is related to the way we choose the next child, when [nrProc] is odd. Sure, it is a good idea to get [halfProc] to be on the lower bound of the result and send the smaller part to the child, while keeping the bigger part for the recursive call, but we have to consider such thing also when we set the id of [child], meaning that instead of skipping a number of positions equal to the smaller part, we need to skip a number of position equal to the bigger part. To ensure such thing works for both even and odd numbers, we can set [child = myId + (nrProc + 1) / 2]. If we don't do such a thing, we risk giving more tasks to the same process, resulting in a deadlock. For example, let's say we have 3 processes.

    Process 0 will tell process [0 + 3 / 2 = 1] that it has to split data among other [3 / 2 = 1] processes. While process 1 works, process 0 will continue the recursive call, with 2 more processes to split data between. Now, on this recursive call, it will try to send data again to process [0 + 2 / 2 = 1], which is already waiting for its parent (process 0) to receive the result. Of course, the parent process 0 can't receive what is sent by process 1, due to the fact it hasn't finished the recursive call, because it waits for process 1 to receive new information. This creates a circular dependency, resulting in a deadlock. In addition, process 2 will never get sent anything. => (C), (D).

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
    std::cout << "myId=" << myId << "; nrProc=" << nrProc << "; dataSize=" << dataSize << "\n";
    // daca ai 2 procese, si dataSize = 0, atunci tu
    // if (nrProc == 1 || dataSize <= 1) // initial implementation
    if (nrProc == 1) // actual solution
        mergeSortLocal(v, dataSize);
    // }
    else
    {
        // 5 procese, rank 0 -> (2 procese, rank 2) + (3 procese, rank 0)
        // 2 procese, rank 2 -> (1 proces, rank 3) + (1 proces, rank 2)
        // 3 procese, rank 0 -> (1 proces, rank 1) + (2 procese, rank 0)
        // 2 procese, rank 0 -> (1 proces, rank 1) + (1 proces, rank 0)
        // worker 4 asteapta

        // 9, 10 -> 4, 5 -> 2, 2 -> 1, 1

        // 5 procese, rank 0 -> (2 procese, rank 3) + (3 procese, rank 0)
        // 2 procese, rank 3 -> (1 proces, rank 4) + (1 proces, rank 3)
        // 3 procese, rank 0 -> (1 proces, rank 2) + (2 procese, rank 0)
        // 2 procese, rank 0 -> (1 proces, rank 1) + (1 proces, rank 0)
        // impartim vectorul in jumatati
        int halfSize = dataSize / 2;
        int halfProc = nrProc / 2;
        int child;
        child = myId + halfProc;
        // initial implementation
        // asigura ca in procesul paralel vor merge mai multe date
        //
        // child = myId + (nrProc + 1) / 2; // actual solution
        // MPI_SSend sends the data synchronously, meaning that the function will not return until the data has been received by the destination process.
        // int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
        // trimite prima jumata a vectorului catre copil
        // (0, 3) -> (1, 2)
        std::cout << "myId=" << myId << "; child=" << child << "; halfSize=" << halfSize << "; halfProc=" << halfProc << "\n";
        MPI_Ssend(&halfSize, 1, MPI_INT, child, 1, MPI_COMM_WORLD);
        MPI_Ssend(&halfProc, 1, MPI_INT, child, 2, MPI_COMM_WORLD);
        MPI_Ssend(v, halfSize, MPI_INT, child, 3, MPI_COMM_WORLD);

        //  mergeSort(v, halfSize, myId, halfProc); initial implementation
        // rezolva recursiv partea din dreapta
        mergeSort(v + halfSize, dataSize - halfSize, myId, nrProc - halfProc);

        MPI_Recv(v, halfSize, MPI_INT, child, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        mergeParts(v, dataSize, halfSize);
    }
}

mergeSort(v, dataSize - halfSize, myId, (nrProc / 2)); // initial implementation

void worker(int myId)
{
    MPI_Status status;
    int dataSize, nrProc;
    // int MPI_Recv(void* buffer, int count, MPI_Datatype datatype, int sender, int tag, MPI_Comm communicator, MPI_Status* status);
    MPI_Recv(&dataSize, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
    auto parent = status.MPI_SOURCE;
    MPI_Recv(&nrProc, 1, MPI_INT, parent, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::vector<int> v(dataSize); // v.data() is the pointer to the first element
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