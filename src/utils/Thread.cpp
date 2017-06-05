#include "config.h"
#include "utils/Thread.h"
#include "utils/Logger.h"

using namespace utils;

Thread::Thread()
        : mLock(),
          mThreadExitedCondition(),
          mStatus(NO_ERROR),
          mExitPending(false),
          mRunning(false) {
}

Thread::~Thread() {
}

#if defined(HAVE_FEATURE_PTHREAD)

typedef void *(*pthread_entry_t)(void *);

bool Thread::run(uint32_t stack) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (stack) {
        pthread_attr_setstacksize(&attr, stack);
    }

    errno = 0;
    pthread_t thread;
    int result = pthread_create(&thread, &attr,
                                (pthread_entry_t) _threadLoop, this);
    pthread_attr_destroy(&attr);
    if (result != 0) {
        LOGE("pthread_create failed: %s(%d)!\n", strerror(errno), errno);
    }

    return !result;
}

uint32_t Thread::getTid() {
    return pthread_self();
}

#endif

int Thread::_threadLoop(void *user) {
    Thread *const self = static_cast<Thread *>(user);
    bool first = true;
    while (true) {
        bool result;

        if (first) {
            first = false;
            result = self->readyToRun();
            if (result && !self->exitPending()) {
                result = self->threadLoop();
            }
        } else {
            result = self->threadLoop();
        }

        {
            Mutex::AutoLock _l(self->mLock);
            if (!result || self->mExitPending) {
                self->mExitPending = true;
                self->mRunning = false;
                self->mThreadExitedCondition.broadcast();
                break;
            }
        }
    }

    return 0;
}

bool Thread::exitPending() {
    Mutex::AutoLock _l(mLock);
    return mExitPending;
}

void Thread::requestExit() {
    Mutex::AutoLock _l(mLock);
    mExitPending = true;
}

status_t Thread::requestExitAndWait() {
    Mutex::AutoLock _l(mLock);
    mExitPending = true;
    while (mRunning) {
        mThreadExitedCondition.wait(mLock);
    }
    mExitPending = false;
    return OK;
}

status_t Thread::join() {
    Mutex::AutoLock _l(mLock);
    while (mRunning) {
        mThreadExitedCondition.wait(mLock);
    }
    return OK;
}

bool Thread::isRunning() {
    Mutex::AutoLock _l(mLock);
    return mRunning;
}
