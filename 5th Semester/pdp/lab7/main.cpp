#include <mpi.h>
#include <iostream>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv); // Initialize MPI

    int world_rank;
    int world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the total number of processes

    std::cout << "Hello from process " << world_rank << " out of " << world_size << std::endl;

    MPI_Finalize(); // Finalize MPI
    return 0;
}
