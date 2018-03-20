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
    const static int port = 9999;
    const static int maxclient = 100;
    
};

int Server::start_server() {
    int  client_socks[maxclient];
    for (int i = 0; i < maxclient; ++i) {
        client_socks[i] = -1;
    }
    int currentclient = 0;
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0){
        cout << "create socket error" << endl;
        close(server_sock);
        return 1;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(port);
    cout << server_sock << endl;
    if(bind(server_sock, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) <0){
        cout << "bind socket error" << endl;
        close(server_sock);
        return 1;
    }
    listen(server_sock, 128);
    int client_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    fd_set readfds;
    int maxfd = server_sock;
    struct timeval tv;
    char buf[256];
    int n;
    cout << "maxsock:" << maxfd << endl;
    while(1){
        FD_ZERO(&readfds);
        FD_SET(server_sock, &readfds);
        tv.tv_sec = 30;
        tv.tv_usec = 0;
        int ret = select(maxfd+1, &readfds,NULL, NULL, &tv);
        if (ret < 0) {
            perror("select");
            break;
        } else if (ret == 0) {
            printf("timeout\n");
            continue;
        }
        if(FD_ISSET(server_sock, &readfds)){
            client_sock = accept(server_sock, reinterpret_cast<struct sockaddr*>(&clnt_addr), &clnt_addr_size);
            cout << "accept client_sock:" << client_sock << endl; 
            if(client_sock<0){
                cout << "bind socket error" << endl;
                close(client_sock);
                return 1;
            }
            int i;
            for (i = 0; i < maxclient; ++i) {
                if(client_socks[i] == -1) {
                    client_socks[i] = client_sock;
                    break;
                } 
            }
            if(i==maxclient){
                cout <<"too many connects" << endl;
                continue;
            }
            FD_SET(client_sock, &readfds);
            cout << "add client_sock:" << client_socks << endl;
            if(client_sock > maxfd) {
                maxfd = client_sock;
            }
            if(i > currentclient) {
                currentclient = i;
            }

            if(--ret ==0){
                continue;
            }

        }
        for(int i=0;i<currentclient;i++){
            if(client_socks[i] < 0){
                continue;
            }
            if(FD_ISSET(client_socks[i], &readfds)){
                cout << client_socks[i] << endl;
                if ((n = read(client_socks[i], buf, 256)) == 0)
                {
                    // 当 client 关闭链接时，服务器端也关闭对应链接
                    close(client_socks[i]);
                    FD_CLR(client_socks[i], &readfds); // 解除 select 监控此文件描述符
                    client_socks[i] = -1;
                }else{// 处理每个有数据到达的 fd  
                    int j;  
                    for (j = 0; j < n; j++){
                        buf[j] = toupper(buf[j]);  
                    }  
                    write(client_socks[i], buf, n);  
                }  
                if(--ret == 0){
                    break;
                }
            }
        }
    }

    close(server_sock);
    return 0;
}

int main(int argc, char *argv[])
{
    Server server;
    server.start_server();
    return 0;
}
