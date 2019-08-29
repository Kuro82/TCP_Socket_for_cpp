#include<iostream>
#include"mySocket.hpp"

using namespace std;

void communicateProcessOfClient(int socketID){
    char buf[100];
    do{
        cin >> buf;
        write(socketID, buf, sizeof(buf));
    }while( strcmp(buf, "EXIT") != 0 );
}

void communicateProcessOfClientForBigData(int socketID){
    char buf[100000];
    cin >> buf;
    send(socketID, buf, sizeof(buf), 0);
}

int main(void){
    SocketClient client;
    client.sendConnectionRequest();

    // main process
    communicateProcessOfClient(client.getClientSocketID());

    return 0;
}

