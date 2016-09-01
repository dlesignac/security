
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int openSocket(int port, int n_clients);
int getClient(int socket_fd);
void closeSocket(int socket_fd);
void error(const char *msg);

#endif // SERVER_H
