#ifndef _UTILS_MUTEX_H
#define _UTILS_MUTEX_H

namespace utils {
    class Mutex {
    public:
        Mutex();
        explicit Mutex(const char *name);
        ~Mutex();
        int lock();
        void unlock();
        int trylock();
        int timedLock();

        class AutoLock {
        public:
            inline explicit AutoLock(Mutex& mutex);
            inline explicit AutoLock(Mutex* mutex);
            inline ~AutoLock() {}
        private:
            Mutex& Lock;
        };
    private:
        Mutex(const Mutex&);
        Mutex& operator=(const Mutex&);

#if !define(_WIN32)
#endif
    };
}

#if defined(HAVE_PTHREADS)
inline Mutex::Mutex() {
}
#endif

#endif //_UTILS_MUTEX_H
