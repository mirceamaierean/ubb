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
    int c = socket(AF_INET, SOCK_DGRAM, 0);

    if (c < 0)
    {
        printf("Error creating socket!\n");
        exit(1);
    }

    struct sockaddr_in server;

    uint16_t a, b, sum;

    scanf("%hu %hu", &a, &b);

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    a = htons(a);
    b = htons(b);

    sendto(c, &a, sizeof(a), 0, (struct sockaddr *)&server, sizeof(server));
    sendto(c, &b, sizeof(b), 0, (struct sockaddr *)&server, sizeof(server));

    int l = sizeof(server);

    recvfrom(c, &sum, sizeof(sum), MSG_WAITALL, (struct sockaddr *)&server, &l);
    sum = ntohs(sum);

    printf("Sum: %hu\n", sum);

    return 0;
}