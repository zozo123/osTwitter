//
//  main.cpp
//  twitServer


#include <iostream>
#include "twitServer.h"
using namespace std;
int main(int argc, const char * argv[])
{
    if (argc!=2){
        cout << "USAGE: twitServer <Port number>" << endl;
        return 0;
    }
    string serverport(argv[1]);
    startServer(serverport);
    
    
}

