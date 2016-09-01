
#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int getFileDescriptor(char host[], int port);
void closeSocket(int socket_fd);
void error(const char *msg);

#endif // CLIENT_H
