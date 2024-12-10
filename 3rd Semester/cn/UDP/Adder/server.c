/*
A client sends to the server 2 numbers and the server returns the sum of them.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    struct sockaddr_in server, client;
    uint16_t a, b, sum;

    int s = socket(AF_INET, SOCK_DGRAM, 0);

    if (s < 0)
    {
        printf("Error creating socket!\n");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Error binding!\n");
        exit(1);
    }

    int l = sizeof(client);
    memset(&client, 0, sizeof(client));

    recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr *)&client, &l);
    recvfrom(s, &b, sizeof(b), MSG_WAITALL, (struct sockaddr *)&client, &l);

    a = ntohs(a);
    b = ntohs(b);

    sum = a + b;
    sum = htons(sum);

    sendto(s, &sum, sizeof(sum), 0, (struct sockaddr *)&client, sizeof(client));

    return 0;
}