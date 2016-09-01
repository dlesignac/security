
#include "server.h"


int openSocket(int port, int n_clients)
{
	struct sockaddr_in server_addr;
	int socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_fd < 0) { error("ERROR opening socket"); }

	bzero((char *) &server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(
			socket_fd,
			(struct sockaddr *) &server_addr,
			sizeof(server_addr)
		) < 0)
		error("ERROR on binding");

	listen(socket_fd, n_clients);

	return socket_fd;
}

int getClient(int socket_fd)
{
	struct sockaddr_in client_addr;
	socklen_t client_len;
	int client_fd;

	client_len = sizeof(client_addr);
	client_fd =
		accept(socket_fd, (struct sockaddr *) &client_addr, &client_len);

	if (client_fd < 0)	error("ERROR on accept");

	return client_fd;
}

void closeSocket(int socket_fd)
{
	close(socket_fd);
}

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

