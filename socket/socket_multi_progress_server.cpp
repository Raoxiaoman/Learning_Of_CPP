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
    const static int port = 9866;
    
};

int Server::start_server() {
    struct sockaddr_in server_addr;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        cout << "create socket error" << endl;
        close(server_socket);
        return 1;
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(port);
    if(bind(server_socket, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) <0){
        cout << "bind socket error" << endl;
        close(server_socket);
        return 1;
    }
    listen(server_socket, 20);
    int client_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    for (int i = 0;  i < 10; ++ i) {
        client_sock = accept(server_socket, reinterpret_cast<struct sockaddr*>(&clnt_addr), &clnt_addr_size);
        if(client_sock<0){
            cout << "accept socket error" << endl;
            return 1;
        }
        int pid = fork();
        if(pid == -1){
            cout << "fork error!" << endl;
            close(server_socket);
            return 1;
        }else if(pid == 0){
            close(server_socket);
            write(client_sock,"hello",6);
            close(client_sock);
            break;
        }else{
            cout << "pid:" << pid <<endl;
        }
    }

    close(server_socket);
    return 0;

}
int main(int argc, char *argv[])
{
    Server server;
    server.start_server();
    return 0;
}
