
#include "sentry.h"


int main(int argc, char *argv[])
{
	srand(time(NULL));

	char buffer[SIZE];
	int socket_fd, client_fd;
	int n, question;

	socket_fd = openSocket(PORT, N_CLIENTS);
	client_fd = getClient(socket_fd);

	int loop = 0;
	int keep = 1;

	int rs, r, x, x_, a, b;

	while (loop < N_LOOPS && keep)
	{
		bzero(buffer, SIZE);
		n = read(client_fd, buffer, SIZE - 1);
		if (n < 0)	error("ERROR reading from socket");
		x = atoi(buffer);

		printf("\nx = %d\n", x);

		question = rand () % 2;

		bzero(buffer, SIZE);
		sprintf(buffer, "%d", question);
		n = write(client_fd, buffer, strlen(buffer));
		if (n < 0) error("ERROR writing to socket");

		if (question)
		{
			printf("sent question 1\n");

			bzero(buffer, SIZE);
			n = read(client_fd, buffer, SIZE - 1);
			if (n < 0)	error("ERROR reading from socket");
			r = atoi(buffer);

			printf("got %d -> ", r);
			x_ = (r * r) % P;

			if (x_ == x)
			{
				printf("passed\n");
				loop++;
			}
			else
			{
				printf("failed");
				keep = 0;
			}
		}
		else
		{
			printf("sent question 0\n");

			bzero(buffer, SIZE);
			n = read(client_fd, buffer, SIZE - 1);
			if (n < 0)	error("ERROR reading from socket");
			rs = atoi(buffer);

			printf("got %d -> ", rs);
			a = (rs * rs) % P;
			b = (x * I) % P;

			if (a == b)
			{
				printf("passed\n");
				loop++;
			}
			else
			{
				printf("failed\n");
				keep = 0;
			}
		}
	}

	if (keep)	printf("\nclient accepted\n");
	else	printf("\nclient refused\n");

	closeSocket(client_fd);
	closeSocket(socket_fd);

	return 0; 
}
