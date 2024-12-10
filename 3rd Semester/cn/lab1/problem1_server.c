// gcc -Wall server.c -o server -lws2_32
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include <stdio.h>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <errno.h>

#define closesocket close
typedef int SOCKET;

#else
#include <WinSock2.h>
#include <cstdint>
#endif

int main(int argc, char *argv[])
{
  SOCKET s;

  struct sockaddr_in server, client;
  int c, l, err;

#ifdef _WIN32
  WSADATA wsaData;
  if (0 > WSAStartup(MAKEWORD(2, 2), &wsaData))
  {
    perror("Error on WSAStartup");
    return 1;
  }
#endif

  s = socket(AF_INET, SOCK_STREAM, 0);

  if (0 > s)
  {
    perror("Error on socket creation");
    return 1;
  }

  memset(&server, 0, sizeof(server));

  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (0 > bind(s, (struct sockaddr *)&server, sizeof(server)))
  {
    perror("Error on bind");
    return 2;
  }

  listen(s, 5);

  l = sizeof(client);

  memset(&client, 0, sizeof(client));

  while (1)
  {
    int n, sum = 0;
    printf("Waiting at port %d...\n", ntohs(server.sin_port));

    c = accept(s, (struct sockaddr *)&client, (socklen_t *)&l);
    err = errno;
#ifdef _WIN32
    err = WSAGetLastError();
#endif
    if (0 > c)
    {
      printf("Error on accept: %d\n", err);
      continue;
    }
    printf("Incomming connected client from: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    int res = recv(c, &n, sizeof(n), 0);

    if (res != sizeof(n))
    {
      printf("Error on receiving a\n");
      closesocket(c);
      continue;
    }

    n = ntohl(n);

    for (int i = 0; i < n; ++i)
    {
      int aux;
      res = recv(c, &aux, sizeof(aux), 0);
      if (0 > res)
      {
        perror("Error on receiving element");
        closesocket(c);
        continue;
      }
      aux = ntohl(aux);
      sum += aux;
    }

    sum = htonl(sum);

    res = send(c, &sum, sizeof(sum), 0);
    if (res != sizeof(sum))
    {
      printf("Error on sending sum\n");
      closesocket(c);
      continue;
    }

    closesocket(c);
  }

#ifdef _WIN32
  WSACleanup();
#endif

  return 0;
}