#ifndef __CORE_H__
#define __CORE_H__

#include <pthread.h>
#include <sys/socket.h>
#include <map>

namespace synomilia
{
    typedef void (*Function)(void*);
    void* recvHandler(void* data);
    void* sendHandler(void* data);

    class Core 
    {
    private:
        int socket_fd;
        pthread_t thread;
        std::map<std::string, Function> event;        
    public:
        Core();
        ~Core();
        int start(const char* addr, int port=2911);
        int end();
        void run();
        void addEvent(std::string, Function);
        
    };
}


#endif
