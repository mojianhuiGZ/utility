#ifndef _UTILS_MUTEX_H
#define _UTILS_MUTEX_H

#include "config.h"
#include "utils/Errors.h"
#include "utils/Timers.h"

#if defined(HAVE_FEATURE_PTHREAD)

#include <pthread.h>

#endif

namespace utils {
    /*
     * Simple mutex.
     * new code should use std::mutex and std::lock_guard instead.
     */
    class Mutex {
    public:
        enum {
            PRIVATE = 0,    // 进程内线程互斥锁，不可重入
            SHARED = 1      // 多进程间线程互斥锁，不可重入
        };

        Mutex();

        explicit Mutex(const char *name);

        Mutex(uint32_t type, const char *name = nullptr);

        ~Mutex();

        status_t lock();

        void unlock();

        status_t tryLock();

        // Manages the mutex automatically. It'll be locked when Autolock is
        // constructed and released when Autolock goes out of scope.
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

        // A mutex cannot be copied
        Mutex(const Mutex &);

        Mutex &operator=(const Mutex &);

#if defined(HAVE_FEATURE_PTHREAD)
        pthread_mutex_t mMutex;
#endif
    };

///////////////////////////////////////////////////////////////////////////////

#if defined(HAVE_FEATURE_PTHREAD)

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

#else
#error Mutex is not implemented in this system!
#endif

    typedef Mutex::AutoLock AutoMutex;

}

#endif //_UTILS_MUTEX_H
