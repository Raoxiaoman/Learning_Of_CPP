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
int main() {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9866);
    while(1){
        int client_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(client_sock < 0){
            cout << "create socket error" << endl;
            return 1;
        }
        if(connect(client_sock, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr))<0){
            cout << "connect socket error" << endl;
            close(client_sock);
            return 1;

        }
        char buf[256];
        read(client_sock,buf,255);
        cout << buf << endl;
    }
    return 0;
}
