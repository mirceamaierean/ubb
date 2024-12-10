// gcc -Wall client.c -o client -lws2_32
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
	uint16_t a, b, sum;
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
	server.sin_addr.s_addr = inet_addr("192.168.64.1");

	if (0 > connect(c, (struct sockaddr *)&server, sizeof(server)))
	{
		perror("Error on connecting to server");
		return 2;
	}

	printf("a = ");
	scanf("%hu", &a);

	printf("b = ");
	scanf("%hu", &b);

	a = htons(a);
	b = htons(b);

	res = send(c, &a, sizeof(a), 0);
	if (0 > res)
	{
		perror("Error on sending a");
		return 3;
	}

	res = send(c, &b, sizeof(b), 0);
	if (0 > res)
	{
		perror("Error on sending b");
		return 4;
	}

	res = recv(c, &sum, sizeof(sum), 0);
	if (0 > res)
	{
		perror("Error on receiving sum");
		return 5;
	}

	sum = ntohs(sum);

	printf("Sum equals to: %hu\n", sum);

	return 0;
}