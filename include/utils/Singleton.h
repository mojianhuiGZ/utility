#ifndef _UTILS_SINGLETON_H
#define _UTILS_SINGLETON_H

namespace utils {
    /*
     * Singleton模式
     * 线程安全无锁
     */
    template<typename T>
    class Singleton {
    public:
        // C++11保证多线程同时调用下static只初始化一次
        static T &getInstance() {
            static T instance;
            sInstance = &instance;
            return instance;
        }

        static bool hasInstance() {
            return sInstance != nullptr;
        }

    private:
        Singleton() {}

        ~Singleton() {}

        Singleton(const Singleton &) = delete;

        Singleton &operator=(const Singleton &) = delete;

        static T *sInstance;
    };
}

#define SINGLETON_STATIC_INSTANCE(T) \
    template<> T* Singleton<T>::sInstance(nullptr)

#endif //_UTILS_SINGLETON_H
