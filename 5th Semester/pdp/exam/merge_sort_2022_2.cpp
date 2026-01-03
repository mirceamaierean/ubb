// la subiectul 1, perechile de procese respectiv lungimi de vector trebuie sa dea aceeasi suma, daca nu se ajunge la procese care nu exista sau nu se ajunge la unele procese existente
/*
    Since we give each available process a [worker], it means every process is expected to receive and send back data. However, when we have more processes than it is actually needed,
    we will reach a point where we will be calling [mergeSortLocal()] when [dataSize <= 1], but [nrProc > 1], meaning we won't be sending data to the remaining [nrProc] processes, which will be
    left waiting, causing a deadlock. To solve the issue, we can remove the condition [dataSize <= 1], and call [mergeSortLocal()] only when we don't have any more processes to split data
    towards. Indeed, in such a case we will send an empty vector having [dataSize = 0], but this won't be a problem, since it won't affect the final result. => (A)

    Another problem is that, int the case when [dataSize] is odd, we compute [halfSize] to be on the lower bound. We send this lower bound to the child, but that means, what remains for the parent is the bigger part, which is [dataSize - halfSize], and not [halfSize]. If we are not careful with this, in the case when the initial [dataSize] is not a power of 2, inconsistent
    data is produced. => (B)

    C, D - False, those are correctly computed.
*/
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
        int child = myId + (nrProc / 2);
        MPI_Ssend(&halfSize, 1, MPI_INT, child, 1, MPI_COMM_WORLD);
        MPI_Ssend(&halfProc, 1, MPI_INT, child, 2, MPI_COMM_WORLD);
        MPI_Ssend(v + (dataSize - halfSize), halfSize, MPI_INT, child, 3, MPI_COMM_WORLD); // MPI_Ssend(v + halfSize, halfSize, MPI_INT, child, 3, MPI_COMM_WORLD);
        mergeSort(v, dataSize - halfSize, myId, child - myId);
        MPI_Recv(v + (dataSize - halfSize), halfSize, MPI_INT, child, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // MPI_Recv(v + halfSize, halfSize, MPI_INT, child, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        mergeParts(v, dataSize, (dataSize - halfSize));                                                      // mergeParts(v, dataSize, halfSize);
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