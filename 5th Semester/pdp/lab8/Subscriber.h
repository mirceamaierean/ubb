#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <iostream>
#include <string>
#include <vector>
#include <mpi.h>
#include "DSM.h"
#include "message.h"

class Subscriber
{
private:
    DSM &dsm;

public:
    Subscriber(DSM &dsmInstance) : dsm(dsmInstance) {}

    void run()
    {
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the process

        bool closed = false;

        while (!closed)
        {
            std::cerr << world_rank << " is waiting\n";

            message ms;
            MPI_Status status;
            MPI_Recv(&ms, sizeof(ms), MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == 0)
            {
                switch (ms.message_type)
                {
                case CLOSE_MESSAGE:
                {
                    std::cerr << world_rank << " stopped\n";
                    closed = true;
                    break;
                }

                case UPDATE_MESSAGE:
                {
                    std::cerr << "Update message in " << world_rank << ": Value of variable " << ms.variable << " has been updated to " << ms.value << " by " << ms.rank << "\n";
                    dsm.setVariable(ms.variable, ms.value);
                    break;
                }
                case SUBSCRIBE_MESSAGE:
                {
                    std::cerr << "Subscriber message in " << world_rank << ": " << ms.rank << " subscribes to " << ms.variable << "\n";
                    dsm.syncSubscriber(ms.rank, ms.variable);
                    break;
                }
                default:
                    break;
                }
            }
        }

        std::cerr << "Final " << world_rank << " - " << "DSM state printed below:\n";
        dsm.printState();
    }
};

#endif // SUBSCRIBER_H
