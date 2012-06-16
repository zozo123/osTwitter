//
//  twitServer.h
//  twitServer
//
#ifndef twitServer_twitServer_h
#define twitServer_twitServer_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

using namespace std;

void startServer(string port);

#endif
