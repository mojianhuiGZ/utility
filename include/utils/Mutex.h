#ifndef _UTILS_MUTEX_H
#define _UTILS_MUTEX_H

#include "config.h"
#include "utils/Errors.h"
#include <mutex>

using std::mutex;
using std::system_error;
using std::errc;

namespace utils {
    class Mutex {
    public:
        explicit Mutex(const char *name);

        ~Mutex();

        status_t lock();

        void unlock();

        bool tryLock();

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

        mutex mMutex;
    };

///////////////////////////////////////////////////////////////////////////////

    inline Mutex::Mutex(const char *name) : mMutex() {
    }

    inline Mutex::~Mutex() {}

    inline status_t Mutex::lock() {
        try {
            mMutex.lock();
            return OK;
        } catch (system_error &e) {
            return -e.code().value();
        }
    }

    inline void Mutex::unlock() {
        mMutex.unlock();
    }

    inline bool Mutex::tryLock() {
        return mMutex.try_lock();
    }

    typedef Mutex::AutoLock AutoMutex;

}

#endif //_UTILS_MUTEX_H
