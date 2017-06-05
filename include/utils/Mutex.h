#ifndef _UTILS_MUTEX_H
#define _UTILS_MUTEX_H

#include "config.h"
#include "utils/Errors.h"
#include "utils/Timers.h"

#if defined(HAVE_FEATURE_PTHREAD)

#include <pthread.h>

#endif

namespace utils {
    class Mutex {
    public:
        Mutex();

        explicit Mutex(const char *name);

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

        Mutex(const Mutex &) = delete;

        Mutex &operator=(const Mutex &) = delete;

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
