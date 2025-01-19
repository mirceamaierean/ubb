#ifndef DSM_H
#define DSM_H

#include <string>
#include <map>
#include <set>
#include <mutex>
#include <thread>
#include <iostream>
#include <mpi.h>
#include "message.h"

class DSM
{
private:
    std::map<int, int> variables;
    std::map<int, std::set<int>> subscribers;
    mutable std::mutex lock;

    // Private constructor for Singleton pattern
    DSM()
    {
        variables[1] = 0;
        variables[2] = 1;
        variables[3] = 2;

        for (auto it : variables)
            subscribers[it.first] = {};
    }

public:
    // Prevent copying and assignment
    DSM(const DSM &) = delete;
    DSM &operator=(const DSM &) = delete;

    // Static method to access the single instance
    static DSM &getInstance()
    {
        static DSM instance; // Created once, shared globally
        return instance;
    }

    int get_self() const
    {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        return rank;
    }

    int get_size() const
    {
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        return size;
    }

    void setVariable(const int &variable, int value)
    {
        std::lock_guard<std::mutex> guard(lock);

        variables[variable] = value;
        std::cerr << "Variable " << variable << " set to " << value << std::endl;
    }

    void updateVariable(const int &variable, int value)
    {
        int rank = get_self();
        setVariable(variable, value);
        message ms = {UPDATE_MESSAGE, rank, variable, value};
        std::cerr << "Update Variable called\n";
        sendMessageToSubscribers(variable, ms);
    }

    void checkAndReplace(const int &variable, int oldValue, int newValue)
    {
        if (variables.find(variable) != variables.end() && variables[variable] == oldValue)
        {
            std::cerr << "Check and replace executing\n";
            updateVariable(variable, newValue);
        }
    }

    void subscribeTo(const int &variable)
    {
        int rank = get_self();
        std::lock_guard<std::mutex> guard(lock);
        subscribers[variable].insert(rank);
        message ms = {SUBSCRIBE_MESSAGE, rank, variable, -1};
        sendMessageToAll(ms);
    }

    void syncSubscriber(int rank, int variable)
    {
        std::lock_guard<std::mutex> guard(lock);
        subscribers[variable].insert(rank);
    }

    void sendMessageToSubscribers(const int &variable, message ms)
    {
        for (int rank : subscribers[variable])
        {
            std::cerr << rank << " rank " << get_self() << " " << ms.message_type << '\n';
            if (rank != get_self())
            {
                send_message(rank, ms);
            }
        }
    }

    void sendMessageToAll(message ms)
    {
        int size = get_size();
        for (int i = 0; i < size; ++i)
        {
            if (ms.message_type == CLOSE_MESSAGE || i != get_self())
            {
                send_message(i, ms);
            }
        }
    }

    void close()
    {
        message ms = {CLOSE_MESSAGE, 0, 0, 0};
        sendMessageToAll(ms);
    }

    void printState() const
    {
        std::lock_guard<std::mutex> guard(lock);
        std::cerr << "DSM State:\n";
        for (const auto &[var, value] : variables)
        {
            std::cerr << "  " << var << " = " << value << "\n";
        }
        for (const auto &[var, subs] : subscribers)
        {
            std::cerr << "  " << var << " subscribers: ";
            for (int sub : subs)
            {
                std::cerr << sub << " ";
            }
            std::cerr << "\n";
        }
    }

private:
    void send_message(int rank, message ms)
    {
        MPI_Send(&ms, sizeof(ms), MPI_BYTE, rank, 0, MPI_COMM_WORLD);

        std::cerr << "Sending message with type " << ms.message_type << '\n';
    }
};

#endif // DSM_H
