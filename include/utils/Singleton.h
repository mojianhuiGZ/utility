#ifndef _UTILS_SINGLETON_H
#define _UTILS_SINGLETON_H

#include "utils/Mutex.h"

namespace utils {
    template<typename T>
    class Singleton {
    public:
        static T &getInstance() {


        }

        static bool hasInstance() {

        }

    private:
        Singleton(const Singleton &);

        Singleton &operator=(const Singleton &);

        static Mutex sLock;
        static T *sInstance;
    };
}

#endif //_UTILS_SINGLETON_H
