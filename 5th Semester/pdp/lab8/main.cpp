#include <mpi.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "DSM.h"
#include "Subscriber.h"

using namespace std;

void sleep_for_milliseconds(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    DSM &dsm = DSM::getInstance(); // Singleton DSM
    Subscriber subscriber(dsm);
    std::thread subscriberThread(&Subscriber::run, &subscriber);

    std::cout << "Start " << rank << " of " << size << std::endl;

    if (rank == 0)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        dsm.subscribeTo(1);
        dsm.subscribeTo(2);
        dsm.subscribeTo(3);
        sleep_for_milliseconds(4000);

        dsm.checkAndReplace(1, 0, 10); // Update "i" if it equals 0
        sleep_for_milliseconds(3000);

        dsm.checkAndReplace(3, 2, 30); // Update "iii" if it equals 2
        sleep_for_milliseconds(3000);

        dsm.checkAndReplace(2, 100, 20); // No update since "ii" does not equal 100
        sleep_for_milliseconds(3000);

        dsm.close(); // Send close message to all subscribers

        sleep_for_milliseconds(1000);

        subscriberThread.join(); // Wait for the subscriber to finish
        cout << "\nHere from master\n";
    }
    else if (rank == 1)
    {
        MPI_Barrier(MPI_COMM_WORLD);

        dsm.subscribeTo(1);
        dsm.subscribeTo(3);
        sleep_for_milliseconds(8000);

        subscriberThread.join();
        cout << "\nHere from first\n";
    }
    else if (rank == 2)
    {
        MPI_Barrier(MPI_COMM_WORLD);

        dsm.subscribeTo(2);
        sleep_for_milliseconds(9000);

        dsm.checkAndReplace(2, 1, 50); // Update "ii" if it equals 1
        sleep_for_milliseconds(1000);

        subscriberThread.join();
        cout << "\nHere from second\n";
    }

    MPI_Finalize();
    return 0;
}
