#ifndef _UTILS_MUTEX_H
#define _UTILS_MUTEX_H

#include "config.h"
#include "utils/Errors.h"

#if defined(HAVE_PTHREAD)

#include <pthread.h>

#endif

namespace utils {
    class Mutex {
    public:
        enum {
            PRIVATE = 0,
            SHARED = 1
        };

        Mutex();

        explicit Mutex(const char *name);

        Mutex(uint32_t type, const char *name = nullptr);

        ~Mutex();

        status_t lock();

        void unlock();

        status_t tryLock();

        class AutoLock {
        public:
            inline explicit AutoLock(Mutex &mutex) : mLock(mutex) { mLock.lock(); }

            inline explicit AutoLock(Mutex *mutex) : mLock(*mutex) { mLock.lock(); }

            inline ~AutoLock() { mLock.unlock(); }

        private:
            Mutex &mLock;
        };

    private:
        friend class Condition;

        Mutex(const Mutex &);

        Mutex &operator=(const Mutex &);

#if defined(HAVE_PTHREAD)
        pthread_mutex_t mMutex;
#endif
    };

///////////////////////////////////////////////////////////////////////////////

#if defined(HAVE_PTHREAD)

    inline Mutex::Mutex() {
        pthread_mutex_init(&mMutex, NULL);
    }

    inline Mutex::Mutex(__attribute__((unused)) const char *name) {
        pthread_mutex_init(&mMutex, NULL);
    }

    inline Mutex::Mutex(uint32_t type, __attribute__((unused)) const char *name) {
        if (type == SHARED) {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_mutex_init(&mMutex, &attr);
            pthread_mutexattr_destroy(&attr);
        } else {
            pthread_mutex_init(&mMutex, NULL);
        }
    }

    inline Mutex::~Mutex() {
        pthread_mutex_destroy(&mMutex);
    }

    inline status_t Mutex::lock() {
        return -pthread_mutex_lock(&mMutex);
    }

    inline void Mutex::unlock() {
        pthread_mutex_unlock(&mMutex);
    }

    inline status_t Mutex::tryLock() {
        return -pthread_mutex_trylock(&mMutex);
    }

#endif

    typedef Mutex::AutoLock AutoMutex;

}

#endif //_UTILS_MUTEX_H
