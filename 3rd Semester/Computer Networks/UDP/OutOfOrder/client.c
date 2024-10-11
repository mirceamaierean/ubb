/*
Un client UDP trimite unui server toate numerele de la 1 la 100. Serverul primeste numerele si afiseaza un mesaj de fiecare data cand primeste un numar “out of order”.

Acest lucru se intampla deoarece protocolul UDP nu este orientat pe conexiune si nu face validari si verificari in ceea ce priveste trimiterea/receptionarea pachetelor care pot sa soseasca la receptor in alta ordine fata de ordinea in care au fost trimise, sau frecvent, chiar sa se piarda.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main()
{
    // declare sockets
    struct sockaddr_in server;
    int c;

    uint16_t crt;

    // create socket
    c = socket(AF_INET, SOCK_DGRAM, 0);

    if (c < 0)
    {
        perror("Error creating socket!\n");
        exit(1);
    }

    // set server address
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    for (int i = 1; i <= 100; ++i)
    {
        crt = i;
        if (i % 7 == 0)
            ++crt;

        crt = htons(crt);
        sendto(c, &crt, sizeof(crt), 0, (struct sockaddr *)&server, sizeof(server));
    }

    return 0;
}