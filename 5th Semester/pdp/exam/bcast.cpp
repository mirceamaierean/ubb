#include <mpi.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc, char **argv)
{
    int rank;
    int buf = 0;
    const int root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == root)
    {
        buf = 777;
        // sleep(5);
        buf = 888;
        MPI_Bcast(&buf, 1, MPI_INT, root, MPI_COMM_WORLD);
    }

    printf("[%d]: Before Bcast, buf is %d\n", rank, buf);

    /* everyone calls bcast, data is taken from root and ends up in everyone's buf */
    /*
    For MPI collective communications, everyone has to particpate; everyone has to call the Bcast, or the Allreduce, or what have you. (That's why the Bcast routine has a parameter that specifies the "root", or who is doing the sending; if only the sender called bcast, you wouldn't need this.) Everyone calls the broadcast, including the receivers; the receviers don't just post a receive.

    The reason for this is that the collective operations can involve everyone in the communication, so that you state what you want to happen (everyone gets one processes' data) rather than how it happens (eg, root processor loops over all other ranks and does a send), so that there is scope for optimizing the communication patterns (eg, a tree-based hierarchical communication that takes log(P) steps rather than P steps for P processes).
    */
    if (rank == root)
        buf = 999;
    MPI_Bcast(&buf, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Bcast(&buf, 1, MPI_INT, root, MPI_COMM_WORLD);

    printf("[%d]: After Bcast, buf is %d\n", rank, buf);

    MPI_Finalize();
    return 0;
}