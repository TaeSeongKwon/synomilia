#include "core.h"
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <memory>

using namespace synomilia;
using namespace std;
void func_(void *data)
{
    printf("hello\n");
}
int main(int argc, char **argv)
{
	printf("start core\n");
    shared_ptr<Core> obj(new Core());
    obj->addEvent("data", func_); 
    if(obj->start("127.0.0.1") == 0)
    {
        obj->run();
        sleep(10);
        obj->end();
    }
	return 0;
}
