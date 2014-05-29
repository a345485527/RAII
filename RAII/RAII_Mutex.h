#include <pthread.h>

class CMutexLock;
class CCondition;
class CMutex{

    friend class CMutexLock;
    friend class CCondition;
    public:
        explicit CMutex()
        {
            pthread_mutex_init(&mutex, NULL);
        }
        ~CMutex()
        {
            pthread_mutex_destroy(&mutex);
        }

    // only class CMutexLock or CCondition can access
    private:
        void lock()
        {
            pthread_mutex_lock(&mutex);
        }
        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_t* getMutex()
        {
            return &mutex; 
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

class CCondition{
    public:
        explicit CCondition(CMutex &_mutex):mutex(_mutex)
        {
            pthread_cond_init(&cond, NULL); 
        }
        ~CCondition()
        {
            pthread_cond_destroy(&cond);
        }
        void wait()
        {
            pthread_cond_wait(&cond, mutex.getMutex());
        }
        void notify()
        {
            pthread_cond_signal(&cond);
        }
        void notifyAll()
        {
            pthread_cond_broadcast(&cond);
        }
    private:
        CCondition(const CCondition&);
        CCondition& operator=(const CCondition&);
    private:
        CMutex &mutex;
        pthread_cond_t cond;
};

