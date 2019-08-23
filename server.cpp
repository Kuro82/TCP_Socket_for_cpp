#include<iostream>
#include"mySocket.hpp"

using namespace std;

void communicateProcessOfServer(int socketID){
    char buf[100];
    do{
        read(socketID, buf, sizeof(buf));
        cout << buf << endl;
    }while( strcmp(buf, "EXIT") != 0 );
}

int main(void){
    SocketServer server;
    server.waitConnectionRequest();

    // main process
    communicateProcessOfServer(server.getClientSocketID());

    return 0;
}