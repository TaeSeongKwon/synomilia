#include "core.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>

synomilia::Core::Core()
{
   printf("before socket\n");
   this->socket_fd = socket(AF_INET,SOCK_STREAM, 0); 
   printf("after socket : %d \n", this->socket_fd);
}

synomilia::Core::~Core()
{
   printf("destroy\n");
}


int synomilia::Core::start(const char *addr, int port)
{
    printf(">>> try connect to server\n");
    struct sockaddr_in server_addr;
    struct in_addr server_in;

    if( inet_pton(AF_INET, addr, &server_in) <= 0)
    {
        printf(">> Connect fail..(%d)\n", errno);
        return -1;
    }
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(addr);
    server_addr.sin_port = htons(port);
    
    int client_len = sizeof(server_addr);
    if(connect(this->socket_fd, (struct sockaddr*)&server_addr, client_len) <0)
    {
        printf(">> Connect fail..(%d)\n", errno);
        return -1;
    }
    printf(">> Connect Success!\n"); 
    return 0;
}
int synomilia::Core::end()
{
    if(this->socket_fd < 0) return -1;
    close(this->socket_fd);
    return 0;
}


void synomilia::Core::run()
{
    std::pair<int , std::map<std::string, Function>* > *arg = new std::pair<int, std::map<std::string, Function> *>();
    arg->first = this->socket_fd;
    arg->second = &this->event;
    pthread_create(&this->thread, 0, recvHandler, (void*)arg);
    //int p = 0;
    //pthread_join(this->thread, (void**)&p);
    pthread_detach(this->thread);
}
void synomilia::Core::addEvent(std::string evt, Function func)
{
    this->event[evt] = func;
}

void* synomilia::recvHandler(void* data)
{
    printf(">> initialize recieve handler - 1 \n");
    std::pair<int, std::map<std::string, Function>* >* arg;
    arg  = (std::pair<int, std::map<std::string, Function>* >*)data;
    printf(">> initialize recieve handler - 2 \n");
    int socket_fd = arg->first;
    std::map<std::string, Function> *events = arg->second;
    printf(">> initialize recieve handler - 3\n");

    printf(">> start reciving thread %d\n", socket_fd);
    char buff[255];
    while(1)
    {
        memset(buff,0, 255);
        printf(">> clear buff\n");
        if( read(socket_fd, buff, 255) <= 0)
        {
            printf(">>> fail recv msg\n");
            break;
        }
        printf(">>> recv : %s\n", buff);
        auto itr = events->find(std::string(buff));
        if(itr != events->end())
        {
            printf(">> call event : %s\n", buff);
            itr->second(nullptr);
        }
    }
}
