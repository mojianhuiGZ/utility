#ifndef _UTILS_THREAD_H
#define _UTILS_THREAD_H

#include "utils/Errors.h"
#include "utils/Condition.h"

namespace utils {

    class Thread {
    public:
        Thread();

        virtual ~Thread();

        bool run(uint32_t stack = 0);

        void requestExit();

        status_t requestExitAndWait();

        status_t join();

        bool isRunning();

        uint32_t getTid();

        virtual bool readyToRun() { return true; };

        virtual bool threadLoop() { return true; }

    private:
        Thread &operator=(const Thread &) = delete;

        bool exitPending();

        static int _threadLoop(void *user);

        Mutex mLock;
        Condition mThreadExitedCondition;
        volatile bool mExitPending;
        volatile bool mRunning;
    };
}

#endif //_UTILS_THREAD_H
