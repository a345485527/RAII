#include <iostream>
#include "./RAII_Mutex.h"
using std::cout;
int var=0;

CMutex mutex;
void *thread1(void*)
{
    CMutexLock lock(mutex);

    for(int i=0;i<100;i++)
    {
        var++;
        cout<<var<<'\n';
    }
    pthread_exit(NULL);
}

int main()
{
   pthread_t tid1,tid2;
   pthread_create(&tid1, NULL, thread1, NULL);
   pthread_create(&tid2,NULL,thread1,NULL);
   pthread_join(tid1 , NULL);
   pthread_join(tid2,NULL);
}
