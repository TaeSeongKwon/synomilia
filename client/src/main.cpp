#include "core.h"
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <memory>

using namespace synomilia;
using namespace std;
void func_(void *data)
{
    printf(">>>> EVENT : hello\n");
}
int main(int argc, char **argv)
{
	printf("start core\n");
    shared_ptr<Core> obj(new Core());
    obj->addEvent("data", func_); 
    if(obj->start() == 0)
    {
        for(int i = 0; i<10; i++)
        {
            sleep(1);
            string msg = "Hello World";
            obj->sendData((void*)msg.c_str(), msg.size());
        }
        obj->end();
    }
	return 0;
}
