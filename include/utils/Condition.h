#ifndef _UTILS_CONDITION_H
#define _UTILS_CONDITION_H

#include "config.h"
#include "utils/Timers.h"
#include "utils/Mutex.h"
#include <condition_variable>

using std::condition_variable;
using std::unique_lock;

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
        Condition(const Condition &) = delete;

        Condition &operator=(const Condition &) = delete;

        condition_variable mCond;
    };

///////////////////////////////////////////////////////////////////////////////

    inline Condition::Condition() : mCond() {}

    inline Condition::~Condition() {}

    inline status_t Condition::wait(Mutex &mutex) {
        unique_lock<std::mutex> lock(mutex.mMutex);
        try {
            mCond.wait(lock);
        } catch (system_error &e) {
            return -e.code().value();
        }
    }

    inline void Condition::signal() {
        mCond.notify_one();
    }

    inline void Condition::broadcast() {
        mCond.notify_all();
    }

}

#endif //_UTILS_CONDITION_H
