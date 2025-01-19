#ifndef MESSAGE_H
#define MESSAGE_H
#define SUBSCRIBE_MESSAGE 1
#define UPDATE_MESSAGE 2
#define CLOSE_MESSAGE 3
#include <iostream>

struct message
{
    int message_type;
    int rank;
    int variable;
    int value;
};

#endif