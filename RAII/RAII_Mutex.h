#include <pthread.h>

class CMutexLock;
class CMutex{

    friend class CMutexLock;
    public:
        explicit CMutex()
        {
            pthread_mutex_init(&mutex, NULL);
        }
        ~CMutex()
        {
            pthread_mutex_destroy(&mutex);
        }

    // only class CMutexLock can access
    private:
        void lock()
        {
            pthread_mutex_lock(&mutex);
        }
        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }

    //uncopyable
    private:
        CMutex(const CMutex&);
        CMutex& operator=(const CMutex&);
    private:
        pthread_mutex_t mutex;
};


class CMutexLock{

    public:
        explicit CMutexLock(CMutex &_mutex):mutex(_mutex)
        {
            mutex.lock();
        }
        ~CMutexLock()
        {
            mutex.unlock();
        }
    private:
        CMutexLock(const CMutexLock&);
        CMutexLock& operator=(const CMutexLock&);
    private:
        CMutex& mutex;
};
