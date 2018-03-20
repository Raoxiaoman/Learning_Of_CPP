#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>

using namespace std;
class Server{
public:
    // constructors, asssignment, destructor
    Server(){};
    ~Server(){};
    int start_server();
private:
    const static int port[3];
    
};

const int Server::port[3] ={9866,9867,9868};
int Server::start_server() {
    int server_sockets[3];
    for(int i=0;i<3;i++){
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(port[i]);
        server_sockets[i] = socket(AF_INET, SOCK_STREAM, 0);
        if(server_sockets[i] < 0){
            cout << "create socket error" << endl;
            close(server_sockets[i]);
            return 1;
        }
        memset(&server_addr, 0, sizeof(server_addr));
        if(bind(server_sockets[i], reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) <0){
            cout << "bind socket error" << endl;
            close(server_sockets[i]);
            return 1;
        }
        listen(server_sockets[i], 20);
    }

    int client_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    fd_set excefds;
    FD_ZERO(&excefds);
    for(int i=0;i<3;i++){
        FD_SET(server_sockets[i], &excefds);
    }

    int maxfd = server_sockets[0];
    for(int i =1;i<3;i++){
        if(server_sockets[i]<maxfd){
            maxfd = server_sockets[i];
        }
    }
    while(1){
        select(maxfd+1, NULL, NULL,&excefds, NULL);
        for(int i=0;i<maxfd;i++){
            if(FD_ISSET(server_sockets[0], &excefds)){
                client_sock = accept(server_sockets[0], reinterpret_cast<struct sockaddr*>(&clnt_addr), &clnt_addr_size);
                if(client_sock<0){
                    cout << "bind socket error" << endl;
                    close(client_sock);
                    return 1;
                }
                write(client_sock,"elema",6);
                close(client_sock);
            }
            if(FD_ISSET(server_sockets[1], &excefds)){
                client_sock = accept(server_sockets[1], reinterpret_cast<struct sockaddr*>(&clnt_addr), &clnt_addr_size);
                if(client_sock<0){
                    cout << "bind socket error" << endl;
                    close(client_sock);
                    return 1;
                }
                write(client_sock,"hello",6);
                close(client_sock);
            }
            if(FD_ISSET(server_sockets[2], &excefds)){
                client_sock = accept(server_sockets[2], reinterpret_cast<struct sockaddr*>(&clnt_addr), &clnt_addr_size);
                if(client_sock<0){
                    cout << "bind socket error" << endl;
                    close(client_sock);
                    return 1;
                }
                write(client_sock,"raohui",7);
                close(client_sock);
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    Server server;
    server.start_server();
    return 0;
}
