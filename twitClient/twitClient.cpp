
#include <iostream>
#include <string>
#include "twitClient.h"

using namespace std;


void twitClient :: checkClientName (string clientName){
    
    if (clientName.find('@')!=string::npos||clientName.find(' ')!=string::npos||clientName.length()>30 || clientName.length()==0) {        
        cerr << "client Name is illegel" << endl;
        exit(1);        
    }
    
}


void twitClient :: disconnect() {
    
    if (close(this->sockfd) != -1 ) {
        
        cout <<clientName<< "\t disconnected.\n";  // should be written in the server log not here!!!
        exit(1);
        
    }
    
    else {
        
        cerr << "error in disconnect in client"<<endl;
    }
    
}

void twitClient:: follow (string friendName) {
    
    
}


void twitClient:: unfollow (string friendName) {
    
    
    
}


void twitClient::  twit(string message) {
    
}



void twitClient:: startClient (){
    
    //TODO check if the client name is in use in the sever case insensitevly. if it existed exit(1)
    
    //TODO handle when the user print "EXIT" and close safely the connection and exit
    
    checkClientName(clientName);
    
    //TODO connect the server...
    
    // if succeed: 
    cout <<clientName<< "\t connected.\n";  // should be written in the server log not here!!!
    
    
    
    
    // TODO In case the server exits first the client should behave reasonably (=not crash), but you can choose the way (detail it in the README file)
    
    
}



void twitClient::  directMessage(string friendName, string message) {
    
    
}// message no more than 140 



void twitClient::  who(){
    
}


//request an ordered alphabetically list of clients.
void twitClient:: publicAnnouncment (string message){
    
}










