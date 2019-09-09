#ifndef CPP_MY_SOCKET
#define CPP_MY_SOCKET


#include<iostream>
#include<sys/socket.h>  // socket()
#include<netinet/in.h>  // struct sockaddr_in, htonl(), sizeof()
#include<unistd.h>      // close()
#include<arpa/inet.h>   // inet_addr()

class SocketServer{
    private:
        //data for server
        int serverSocketID;
        struct sockaddr_in addr;
        //data for client
        int clientSocketID;
        struct sockaddr_in client;
        socklen_t clientLen;

    public:
        void makeSocketServer(int portNumber){
            //(1) socket : make Socket : set protocol of TCP/IP or UDP
            serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
            if(serverSocketID < 0){
                perror("server : make socket");
                exit(-1);
            }

            //(2) socket : configurate Socket
            memset(&addr, 0, sizeof(addr));
            addr.sin_family = AF_INET; // AF_INET : IPv4
            addr.sin_port = htons(portNumber);
            addr.sin_addr.s_addr = htonl( INADDR_ANY );
            // sin_addr.s_addr : permit IP address to access
            // INADDR_ANY is permitting All IP address

            //(3) bind() : set port number
            if( bind(serverSocketID, (struct sockaddr *)&addr, sizeof(addr)) < 0 ){
                perror("server : bind");
                exit(-1);
            }
        }
        void waitConnectionRequest(){
            //(4) listen
            if( listen(serverSocketID, 5) < 0 ){
                perror("server : listen");
                exit(-1);
            }

            //(5) accept
            if( clientSocketID = accept(serverSocketID, (struct sockaddr *)&client, &clientLen), clientSocketID < 0 ){
                perror("server : accept");
                exit(-1);
            }
        }
        void closeSession(){
            close(clientSocketID);
        }
        void closeServer(){
            close(serverSocketID);
        }
        int getServerSocketID(){
            return serverSocketID;
        }
        int getClientSocketID(){
            return clientSocketID;
        }
        SocketServer(int portNumber=12345){
            makeSocketServer(portNumber);
        }
        ~SocketServer(){
            closeSession();
            closeServer();
        }
};
class SocketClient{
    private:
        int clientSocketID;
        struct sockaddr_in server;

    public:
        void makeSocketClient(){
            //(1) make socket
            clientSocketID = socket(AF_INET, SOCK_STREAM, 0);
            if(clientSocketID < 0){
                perror("client : make socket");
                exit(-1);
            }
        }
        void sendConnectionRequest(const char * IPAddress="127.0.0.1", int portNumber=12345){
            //(2) socket : configurate Socket
            memset(&server, 0, sizeof(server));
            server.sin_family = AF_INET; // AF_INET : IPv4
            server.sin_port = htons(portNumber);
            server.sin_addr.s_addr = inet_addr(IPAddress);

            //(3) connect server
            connect(clientSocketID, (struct sockaddr *)&server, sizeof(server));

        }
        void closeClient(){
            close(clientSocketID);
        }
        int getClientSocketID(){
            return clientSocketID;
        }
        SocketClient(){
            makeSocketClient();
        }
        ~SocketClient(){
            closeClient();
        }
};


#endif
