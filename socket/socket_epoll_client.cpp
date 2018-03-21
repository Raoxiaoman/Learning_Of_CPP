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
    server_addr.sin_port = htons(9877);
    //for (int i = 0; i < 10; ++i) {
        int client_sock = socket(AF_INET, SOCK_STREAM, 0);
        cout << "client_sock:" <<  client_sock << endl;
        if(client_sock < 0){
            cout << "create socket error" << endl;
            return 1;
        }
        int ret = connect(client_sock, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr));
        if(ret < 0) {
            cout << "connect error" << endl;
            return 1;
        }
        char str[] = "raohui";
        write(client_sock,str,strlen(str));
        char buf[256];
        //read(client_sock,buf,255);
        recv(client_sock, buf, 256, 0);
        cout << buf << endl;
    //}
    return 0;
}
