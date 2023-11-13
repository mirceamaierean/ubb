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
    int s;
    struct sockaddr_in server, client;
    int c;

    uint16_t crt;

    // create socket
    s = socket(AF_INET, SOCK_DGRAM, 0);

    if (s < 0)
    {
        perror("Error creating socket!\n");
        exit(1);
    }

    // set server address
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    // bind socket to server address
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Error binding!\n");
        exit(2);
    }

    // receive numbers from client
    int l = sizeof(client);

    memset(&client, 0, sizeof(client));

    for (int i = 1; i <= 100; ++i)
    {
        recvfrom(s, &crt, sizeof(crt), MSG_WAITALL, (struct sockaddr *)&client, &l);

        crt = ntohs(crt);

        if (crt != i)
            printf("Out of order: %hu\n", crt);
    }

    return 0;
}