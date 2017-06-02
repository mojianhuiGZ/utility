#ifndef _UTILS_CONDITION_H
#define _UTILS_CONDITION_H

#include "utils/Timers.h"
#include "utils/Mutex.h"

namespace utils {
    class Condition {
    public:
        enum {
            PRIVATE = 0,
            SHARED = 1
        };

        enum WakeUpType {
            WAKE_UP_ONE = 0,
            WAKE_UP_ALL = 1
        };

        Condition();

        Condition(uint32_t type);

        ~Condition();

        status_t wait(Mutex &mutex);

        status_t waitRelative(Mutex &mutex, nsecs_t reltime);

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
#if defined(HAVE_PTHREAD)
        pthread_cond_t mCond;
#endif
    };

///////////////////////////////////////////////////////////////////////////////

#if defined(HAVE_PTHREAD)

    inline Condition::Condition() {
        pthread_cond_init(&mCond, NULL);
    }

    inline Condition::Condition(uint32_t type) {
        if (type == SHARED) {
            pthread_condattr_t attr;
            pthread_condattr_init(&attr);
            pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_cond_init(&mCond, &attr);
            pthread_condattr_destroy(&attr);
        } else {
            pthread_cond_init(&mCond, NULL);
        }
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

#endif

}

#endif //_UTILS_CONDITION_H
