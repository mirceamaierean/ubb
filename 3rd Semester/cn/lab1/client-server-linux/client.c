#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
typedef int SOCKET;

int main(int argc, char *argv[])
{
	SOCKET c;
	struct sockaddr_in server;
	uint16_t a, b, sum;
	int res;

	c = socket(AF_INET, SOCK_STREAM, 0);

	if (0 > c)
	{
		perror("Error on socket creation.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));

	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.64.3");

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