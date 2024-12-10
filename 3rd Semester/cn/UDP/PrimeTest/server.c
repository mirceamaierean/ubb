#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>

uint16_t isPrime(uint16_t a)
{
    if (a == 0 || a == 1)
        return 0;

    for (uint16_t i = 2; i * i <= a; ++i)
        if (a % i == 0)
            return 0;

    return 1;
}

int main()
{
    struct sockaddr_in server, client;

    int s;
    uint16_t a, prime;

    s = socket(AF_INET, SOCK_DGRAM, 0);

    if (s < 0)
    {
        perror("Error creating socket!\n");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Error binding!\n");
        exit(1);
    }

    while (1)
    {
        int l = sizeof(client);
        memset(&client, 0, sizeof(client));

        recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr *)&client, &l);

        a = ntohs(a);
        printf("Received: %hu\n", a);
        prime = isPrime(a);

        prime = htons(prime);
        sendto(s, &prime, sizeof(prime), 0, (struct sockaddr *)&client, sizeof(client));
    }

    return 0;
}
