
#ifndef twitClient_twitClient_h
#define twitClient_twitClient_h

#include <string>
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

using namespace std;

class twitClient {
    
    string clientName;
    string serverAdd;
    string serverPort;
    int sockfd;
    
public:
    twitClient(string clientname,string serveradd,string serverport):
        serverAdd(serveradd),serverPort(serverport), sockfd(-1) {

        checkClientName(clientname);
        clientName = string(clientname);
        startClient();
    }
    
    
    void follow(string friendName);
    void disconnect();
    void unfollow(string friendName);
    void twit(string message);
    
    // <HOUR>:<MINUTES>::<CLIENT NAME> @<SOME CLIENT NAME>--<MESSAGE>
    //With the hour & minute being the time the message is broadcast.
    void directMessage(string friendName, string message); // message no more than 140

    void who();//request an ordered alphabetically list of clients.
    void publicAnnouncment (string message);
    void checkClientName (string clientName);
    void startClient ();
    
};





 
#endif
