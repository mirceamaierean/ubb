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
#include <stdint.h>
#endif

int main(int argc, char *argv[])
{
  SOCKET c;
  struct sockaddr_in server;

  int a[500], n, sum;
  int res;

#ifdef _WIN32
  WSADATA wsaData;
  if (0 > WSAStartup(MAKEWORD(2, 2), &wsaData))
  {
    perror("Error on WSAStartup");
    return 1;
  }
#endif

  c = socket(AF_INET, SOCK_STREAM, 0);

  if (0 > c)
  {
    perror("Error on socket creation.\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));

  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (0 > connect(c, (struct sockaddr *)&server, sizeof(server)))
  {
    perror("Error on connecting to server");
    return 2;
  }

  printf("Size of array: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    printf("a[%d] = ", i);
    scanf("%d", &a[i]);
  }

  int aux = htonl(n);
  res = send(c, &aux, sizeof(aux), 0);
  if (0 > res)
  {
    perror("Error on sending size");
    return 3;
  }

  for (int i = 0; i < n; ++i)
  {
    aux = htonl(a[i]);
    res = send(c, &aux, sizeof(aux), 0);
    if (0 > res)
    {
      perror("Error on sending element");
      return 4;
    }
  }

  res = recv(c, &sum, sizeof(sum), 0);
  if (0 > res)
  {
    perror("Error on receiving sum");
    return 5;
  }

  sum = ntohl(sum);

  printf("Sum = %d\n", sum);

  return 0;
}