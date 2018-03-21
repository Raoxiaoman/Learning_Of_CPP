#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <sys/epoll.h>
#include <fcntl.h>

using namespace std;
class Server{
public:
    // constructors, asssignment, destructor
    Server(){};
    ~Server(){};
    int start_server();
private:
    const static int port = 9877;
    const static int maxEvents = 100;
    int socket_non_blocking (int sfd);
    int bind_and_listen(int socket);
    struct output{
        int fd;
        char buf[256];
    };

};

int Server::bind_and_listen(int listen_sock) {
    if(listen_sock < 0){
        cout << "create socket error" << endl;
        close(listen_sock);
        return 1;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(port);
    if(bind(listen_sock, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) <0){
        cout << "bind socket error" << endl;
        close(listen_sock);
        return 1;
    }
    listen(listen_sock, 128);
    return 0;
}

int Server::socket_non_blocking (int sfd)
{
    int flags, s;
    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }
    return 0;
}

int Server::start_server() {
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(bind_and_listen(listen_sock)){
        perror("bind and listen error");
        return 1;
    }

    int conn_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    char buf[256];

    int sepoll = epoll_create1(0);
    if(sepoll < 0) {
        cout << "create epoll error!" << endl;
        close(listen_sock);
        return 1;
    }

    struct epoll_event event;
    event.data.fd = listen_sock;
    event.events = EPOLLIN;
    if(epoll_ctl(sepoll, EPOLL_CTL_ADD, listen_sock, &event)==-1){
        cout << "ctl epoll error!" << endl;
        close(listen_sock);
        return 1;
    }
    struct epoll_event events[maxEvents];
    int nfds;
    struct output out;

    while(1){

        nfds = epoll_wait(sepoll, events, maxEvents, -1);
        cout << "nfds:" << nfds << endl;
        int sockfd;
        for (int i = 0; i < nfds; ++i) {
            if(events[i].data.fd == listen_sock){
                conn_sock = accept(listen_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
                //socket_non_blocking(conn_sock);
                cout << "conn_sock:" << conn_sock << endl;
                event.events = EPOLLIN;
                event.data.fd = conn_sock;
                if (epoll_ctl(sepoll, EPOLL_CTL_ADD, conn_sock,
                            &event) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            }
            else if(events[i].events & EPOLLIN ){
                if((sockfd = events[i].data.fd)<0){
                    perror("sockfd < 0");
                    continue;
                }
                cout << "Input_sock:" << sockfd<< endl;
                int n = read(sockfd, buf, 256);
                for (int j = 0; j < n; j++){
                    buf[j] = toupper(buf[j]);  
                }  
                strcpy(out.buf, buf);
                out.fd = sockfd;
                event.data.ptr = &out;
                event.events = EPOLLOUT;
                if (epoll_ctl(sepoll, EPOLL_CTL_MOD, sockfd,
                            &event) == -1) {
                    perror("epoll_ctl: sockfdI");
                    exit(EXIT_FAILURE);
                }
            }
            else if(events[i].events & EPOLLOUT){
                struct output *out = (struct output *)events[i].data.ptr;
                cout << "out_fd:" << out->fd <<  endl; 
                send(out->fd, out->buf, strlen(out->buf),0);
                cout << "send!" << endl;
                if (epoll_ctl(sepoll, EPOLL_CTL_DEL, out->fd,
                            &event) == -1) {
                    perror("epoll_ctl: sockfdO");
                    exit(EXIT_FAILURE);
                }
                close(out->fd);
            }
        }
    } 

    close(listen_sock);
    return 0;
}

int main(int argc, char *argv[])
{
    Server server;
    server.start_server();
    return 0;
}
