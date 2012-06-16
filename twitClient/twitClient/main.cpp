//
//  main.cpp
//  twitClient


#include <iostream>
#include "twitClient.h"

using namespace std;
int main(int argc, const char * argv[])
{
    if (argc != 4){
        cout<< "twitClient <CLIENT NAME> <SERVER ADDRESS> <SERVER PORT>" << endl;
        return 0;
    }
    
    
    string clientName (argv[1]);
    string serverAdd (argv[2]);
    string serverPort (argv[3]);
    
    cout << clientName << " " << serverAdd<< "   " << serverPort<< endl;
    
    
    startClient (clientName,serverAdd, serverPort);
    
}

