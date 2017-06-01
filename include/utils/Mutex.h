#ifndef _UTILS_MUTEX_H
#define _UTILS_MUTEX_H

#include <zconf.h>

namespace utils {
    class Mutex {
    public:
        Mutex();

        explicit Mutex(const char *name);

        ~Mutex();

        status_t lock();

        void unlock();

        status_t trylock();

        class AutoLock {
        public:
            inline explicit AutoLock(Mutex &mutex) : mLock(mutex) { mLock.lock(); }

            inline explicit AutoLock(Mutex *mutex) : mLock(*mutex) { mLock.lock(); }

            inline ~AutoLock() { mLock.unlock(); }

        private:
            Mutex &mLock;
        };

    private:
        Mutex(const Mutex &);

        Mutex &operator=(const Mutex &);

        pthread_mutex_t mMutex;

    };
}

inline Mutex::Mutex() {
    pthread_mutex_init(&mMutex, NULL);
}
inline Mutex::Mutex(__attribute__((unused)) const char *name) {

}
inline Mutex::~Mutex() {

}
inline status_t Mutex::lock() {

}
inline void Mutex::unlock() {

}
inline status_t Mutex::tryLock() {

}

typedef Mutex::AutoLock AutoMutex;

#endif //_UTILS_MUTEX_H
