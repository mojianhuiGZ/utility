#ifndef _UTILS_CONDITION_H
#define _UTILS_CONDITION_H

#include "config.h"
#include "utils/Timers.h"
#include "utils/Mutex.h"

namespace utils {
    class Condition {
    public:
        enum WakeUpType {
            WAKE_UP_ONE = 0,
            WAKE_UP_ALL = 1
        };

        Condition();

        ~Condition();

        status_t wait(Mutex &mutex);

        void signal();

        void signal(WakeUpType type) {
            if (type == WAKE_UP_ONE) {
                signal();
            } else {
                broadcast();
            }
        }

        void broadcast();

    private:
#if defined(HAVE_FEATURE_PTHREAD)
        pthread_cond_t mCond;
#endif
    };

///////////////////////////////////////////////////////////////////////////////

#if defined(HAVE_FEATURE_PTHREAD)

    inline Condition::Condition() {
        pthread_cond_init(&mCond, NULL);
    }

    inline Condition::~Condition() {
        pthread_cond_destroy(&mCond);
    }

    inline status_t Condition::wait(Mutex &mutex) {
        return -pthread_cond_wait(&mCond, &mutex.mMutex);
    }

    inline void Condition::signal() {
        pthread_cond_signal(&mCond);
    }

    inline void Condition::broadcast() {
        pthread_cond_broadcast(&mCond);
    }

#else
#error Condition is not implemented in this system!
#endif

}

#endif //_UTILS_CONDITION_H
