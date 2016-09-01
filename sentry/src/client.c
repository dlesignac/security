
#include "client.h"


int getFileDescriptor(char host[], int port)
{
	struct sockaddr_in server_addr;
	struct hostent *server;

	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_fd < 0)	error("ERROR opening socket");

	server = gethostbyname(host);

	if (server == NULL)
	{
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}

	bzero((char*) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	bcopy(
		(char*) server->h_addr, 
		(char*) &server_addr.sin_addr.s_addr,
		server->h_length
	);
	server_addr.sin_port = htons(port);

	if (connect(
			socket_fd,
			(struct sockaddr *) &server_addr,
			sizeof(server_addr)
		) < 0) 
		error("ERROR connecting");

	return(socket_fd);
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
