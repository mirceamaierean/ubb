#include <iostream>
#include <mpi.h>

// let n be the number of processes
int main(int argc, char **argv)
{
    MPI_Init(0, 0);

    int me;
    int size;

    // everyone has access to size and me
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    std::cout << "Hello, I am " << me << " out of " << size << "\n";

    int message = 0;
    if (me == 0)
    {
        message = 42;
    }

    // 0 -> (1, 2, 3, 4);
    else
    {
        MPI_Status status;
        int nr;
        //  receive waits from the other to send
        MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &nr);
        if (nr != 1)
        {
            std::cerr << "Wrong size\n";
        }
        std::cout << "Me=" << me << "; source=" << status.MPI_SOURCE << "; tag=" << status.MPI_TAG << "; message=" << message << "\n";
    }

    // last process will display from here (n - 1)
    if (me == size - 1)
    {
        std::cout << "Message = " << message << "\n";
    }
    // {0, 1, 2, ..., n - 2} will update the message and send it to the next process
    else
    {
        ++message;

        // MPI_Ssend
        MPI_Ssend(&message, 1, MPI_INT, me + 1, 123, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}