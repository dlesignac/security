
#include "intruder.h"


int main(int argc, char *argv[])
{
	srand(time(NULL));

	int socket_fd, n;
	char buffer[SIZE];

	socket_fd = getFileDescriptor(HOST, PORT);

	int loop;
	int rs, r, x, inv_i, inv_p;

	for (loop = 0; loop < N_LOOPS; loop++)
	{
		if (rand() % 2)
		{
			printf("\ntry question 1\n");

			r = (rand() % (P - 1)) + 1;
			x = (r * r) % P;

			bzero(buffer, SIZE);
			sprintf(buffer, "%d", x);
			n = write(socket_fd, buffer, strlen(buffer));
			if (n < 0)	error("ERROR writing to socket");

			printf("r %d -> x %d\n", r, x);

			bzero(buffer, SIZE);
			n = read(socket_fd, buffer, SIZE - 1);
			if (n < 0)	error("ERROR reading from socket");
			
			printf("got question %s\n", buffer);

			bzero(buffer, SIZE);
			sprintf(buffer, "%d", r);			
			n = write(socket_fd, buffer, strlen(buffer));
			if (n < 0)	error("ERROR writing to socket");
		}
		else
		{
			printf("\ntry question 0\n");

			rs = (rand() % (P - 1)) + 1;

			inv_i = 0;
			inv_p = 0;

			bezout(I, P, &inv_i, &inv_p);
			if (inv_i < 0)	inv_i += P;
			x = ((rs * rs) * inv_i) % P;

			bzero(buffer, SIZE);			
			sprintf(buffer, "%d", x);			
			n = write(socket_fd, buffer, strlen(buffer));
			if (n < 0)	error("ERROR writing to socket");

			printf("rs %d -> x %d\n", rs, x);

			bzero(buffer, SIZE);
			n = read(socket_fd, buffer, SIZE - 1);
			if (n < 0)	error("ERROR reading from socket");

			printf("got question %s\n", buffer);
			
			bzero(buffer, SIZE);
			sprintf(buffer, "%d", rs);
			n = write(socket_fd, buffer, strlen(buffer));
			if (n < 0)	error("ERROR writing to socket");
		}
	}

	printf("got in\n");

	return(0);
}

int	bezout(int a, int b, int *u_n2, int *v_n2)
{
	if (a == 0 || b == 0) { return -1; }

	int u_n = 1; int u_n1 = 0;
	int v_n = 0; int v_n1 = 1;
	int q   = 0; int r    = 0;

	while (b)
	{
		q = a / b;
		r = a % b;
		*u_n2 = u_n - q * u_n1;
		*v_n2 = v_n - q * v_n1;

		if (r == 1) { return 0; }

		u_n = u_n1; u_n1 = *u_n2;
		v_n = v_n1; v_n1 = *v_n2;
		a = b;
		b = r;
	}

	return -2;
}

