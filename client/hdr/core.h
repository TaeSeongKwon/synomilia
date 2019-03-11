#ifndef __CORE_H__
#define __CORE_H__

#include <pthread.h>
#include <sys/socket.h>
#include <map>

namespace synomilia
{
    // Define User Variable
    extern const int DFT_PORT;
    extern const char* DFT_HOST;

    // Declare callback function
    typedef void (*Function)(void*);

    // Declare thread callback function
    void* recvHandler(void* data);
    void* eventHandler(void* data);
    void* sendHandler(void* data);

    // Declare Core Class
    class Core 
    {
    private:
        int socket_fd;
        pthread_t thread;

        // Remote information 
        int remote_port;
        std::string remote_addr;

        // event function 
        std::map<std::string, Function> evt_map; 

        // thread start function
        int run();

    public:
        // Constructor
        Core();
        // Destroyer
        ~Core();

        // start method
        int start(const char *addr=DFT_HOST, int port=DFT_PORT);

        // end method
        int end();

        // register event callbak
        void addEvent(std::string, Function);

        /* method for communication */
        int sendData(void *buff, size_t length);

    };
}


#endif
