#include "core.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>

const char* synomilia::DFT_HOST = "127.0.0.1";
const int synomilia::DFT_PORT = 2911;
synomilia::Core::Core()
{
    printf("before create socket\n");
    this->socket_fd = socket(AF_INET,SOCK_STREAM, 0); 
    printf("after create socket : %d \n", this->socket_fd);

}

synomilia::Core::~Core()
{
   printf("destroy\n");
}
/*
 *  @brief The start() method starts thread after create socket and bind address, port
 *  @param *addr This is IPv4 String of Server. (default 127.0.0.1)
 *  @param port This is Port Number of Server. (default 2911)
 *  @return if thread is successfully started, return 0 otherwise, number except 0.
 */
int synomilia::Core::start(const char *addr, int port)
{
    this->remote_addr = addr;
    this->remote_port = port;

    printf(">>> try connect to server\n");
    printf(">>> HOST : %s\n", this->remote_addr.c_str());
    printf(">>> PORT : %d\n", this->remote_port);

    struct sockaddr_in server_addr;
    struct in_addr server_in;

    // check ip format 
    if( inet_pton(AF_INET, this->remote_addr.c_str(), &server_in) <= 0)
    {
        printf(">> Connect fail..(%d)\n", errno);
        return -1;
    }

    // Set address informatin
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(this->remote_addr.c_str());
    server_addr.sin_port = htons(this->remote_port);
    
    // Try connect
    int client_len = sizeof(server_addr);
    if(connect(this->socket_fd, (struct sockaddr*)&server_addr, client_len) <0)
    {
        printf(">> Connect fail..(%d)\n", errno);
        return -1;
    }
    printf(">> Connect Success!\n"); 

    return this->run();
}

int synomilia::Core::end()
{
    if(this->socket_fd < 0) return -1;
    close(this->socket_fd);
    return 0;
}

/*
 * @brief This is thread run method
 */
int synomilia::Core::run()
{
    std::pair<int , std::map<std::string, Function>* > *arg = new std::pair<int, std::map<std::string, Function> *>();
    arg->first = this->socket_fd;
    arg->second = &this->evt_map;
    int ret = pthread_create(&this->thread, 0, recvHandler, (void*)arg);

    if(ret != 0) return ret;
    return pthread_detach(this->thread);
}


void synomilia::Core::addEvent(std::string evt, Function func)
{
    this->evt_map[evt] = func;
}

int synomilia::Core::sendData(void *buff, size_t length)
{
    std::pair<int, std::pair<void*, size_t> > *arg = new std::pair<int, std::pair<void*, size_t> >();
    arg->first = this->socket_fd;
    arg->second = {buff, length};
    pthread_t sendThread;
    int is_create = pthread_create(&sendThread, 0, sendHandler, (void*)arg);
    if(is_create != 0 ) return is_create;
    int ret = pthread_detach(sendThread);
    return ret;
}

void* synomilia::sendHandler(void* arg)
{
    std::pair<int, std::pair<void*, size_t> > *data = (std::pair<int, std::pair<void*, size_t> >*)arg;
    int socket_fd = data->first;
    void* buff = data->second.first;
    size_t length = data->second.second;
    int ret = 0 ;

    if( (ret = send(socket_fd, buff, length, 0)) <= 0 )
    {
        printf("[ERROR] fail the message send.(%s)\n", strerror(errno));
    }
    else 
    {
        printf("[SEND] %s\n", (char*)buff); 
    }

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
        if( read(socket_fd, buff, 255) <= 0)
        {
            printf(">>> fail recv msg\n");
            break;
        }

        printf(">>> recv : %s\n", buff);
        auto itr = events->find(std::string(buff));
        if(itr != events->end())
        {
            std::pair<Function, char*> *obj = new std::pair<Function, char*>();
            obj->first = itr->second;
            obj->second = (char*)std::string(buff).c_str();
            pthread_t thread;
            pthread_create(&thread, 0, eventHandler, (void*)obj);
            // printf(">> call event : %s\n", buff);
            // itr->second(nullptr);
        }
    }
}

/*
 * @brief This is thread method to call the event 
 */
void* synomilia::eventHandler(void *arg)
{
    std::pair<Function, char *> *obj = (std::pair<Function, char *> *)arg;
    Function func = obj->first;
    char* data = obj->second;
    // TODO Event data
    func(nullptr);

}

