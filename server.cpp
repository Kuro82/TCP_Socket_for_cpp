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

void communicateProcessOfServerForBigData(int socketID){
    char buf[100000];
    int dataSize = 0;
    do{
        dataSize += recv(socketID, &(buf[dataSize]), sizeof(buf), 0);
    }while( dataSize < 100000 );
    cout << buf << endl;
}

int main(void){
    SocketServer server;
    server.waitConnectionRequest();

    // main process
    communicateProcessOfServer(server.getClientSocketID());

    return 0;
}