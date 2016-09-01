
#include "grantee.h"


int main(int argc, char *argv[])
{
	srand(time(NULL));

	int socket_fd, n;
	char buffer[SIZE];

	socket_fd = getFileDescriptor(HOST, PORT);

	int loop, question;
	int rs, r, x;

	for (loop = 0; loop < N_LOOPS; loop++)
	{
		r = (rand() % (P - 1)) + 1;
		x = (r * r) % P;
		rs = (r * S) % P;

		printf("\nr = %d ; x = %d ; rs = %d\n", r, x, rs);

		bzero(buffer, SIZE);
		sprintf(buffer, "%d", x);
		n = write(socket_fd, buffer, strlen(buffer));
		if (n < 0)	error("ERROR writing to socket");

		bzero(buffer, SIZE);
		n = read(socket_fd, buffer, SIZE - 1);
		if (n < 0)	error("ERROR reading from socket");
		question = atoi(buffer);

		printf("got question %d\n", question);

		if (question)
		{
			printf("sent r = %d\n", r);

			bzero(buffer, SIZE);
			sprintf(buffer, "%d", r);
			n = write(socket_fd, buffer, strlen(buffer));
			if (n < 0)	error("ERROR writing to socket");
		}
		else
		{
			printf("sent rs = %d\n", rs);

			bzero(buffer, SIZE);
			sprintf(buffer, "%d", rs);
			n = write(socket_fd, buffer, strlen(buffer));
			if (n < 0)	error("ERROR writing to socket");
		}
	}

	printf("\ngot in\n");

	return(0);
}
