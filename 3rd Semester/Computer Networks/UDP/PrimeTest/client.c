#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct sockaddr_in server;
    int c;

    uint16_t a, prime;

    c = socket(AF_INET, SOCK_DGRAM, 0);

    if (c < 0)
    {
        printf("Error creating socket!\n");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    printf("a = ");
    scanf("%hu", &a);

    a = htons(a);

    sendto(c, &a, sizeof(a), 0, (struct sockaddr *)&server, sizeof(server));

    int l = sizeof(server);
    recvfrom(c, &prime, sizeof(prime), MSG_WAITALL, (struct sockaddr *)&server, &l);

    prime = ntohs(prime);

    if (prime == 1)
        printf("Prime\n");
    else
        printf("Not prime\n");

    return 0;
}