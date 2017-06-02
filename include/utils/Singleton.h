#ifndef _UTILS_SINGLETON_H
#define _UTILS_SINGLETON_H

#include "utils/Mutex.h"

namespace utils {
    template<typename T>
    class Singleton {
    public:
        static T &getInstance() {
            Mutex::AutoLock _l(sLock);
            T *instance = sInstance;
            if (instance == nullptr) {
                instance = new T();
                sInstance = instance;
            }
            return *instance;
        }

        static bool hasInstance() {
            Mutex::AutoLock _l(sLock);
            return sInstance != nullptr;
        }

    protected:
        Singleton() {}

        ~Singleton() {}

    private:

        Singleton(const Singleton &);

        Singleton &operator=(const Singleton &);

        static Mutex sLock;
        static T *sInstance;
    };
}

#define SINGLETON_STATIC_INSTANCE(T) \
    template<> Mutex Singleton<T>::sLock(Mutex::PRIVATE); \
    template<> T* Singleton<T>::sInstance(nullptr);

#endif //_UTILS_SINGLETON_H
