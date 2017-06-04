#include <unistd.h>
#include <ctime>
#include <sys/time.h>
#include "utils/Timers.h"

using namespace utils;

bool utils::isSystemClockAvailable(uint32_t clock) {
    switch (clock) {
        case SYSTEM_TIME_REALTIME:
            return true;
        case SYSTEM_TIME_MONOTONIC:
#if (_POSIX_MONOTONIC_CLOCK > 0)
            return true;
#else
            return false;
#endif
        case SYSTEM_TIME_PROCESS:
#if (_POSIX_CPUTIME > 0)
            return true;
#else
            return false;
#endif
        case SYSTEM_TIME_THREAD:
#if (_POSIX_THREAD_CPUTIME > 0)
            return true;
#else
            return false;
#endif
        case SYSTEM_TIME_BOOTTIME:
#if defined(_POSIX_TIMERS)
            return true;
#else
            return false;
#endif
        default:
            return false;
    }
}

nsecs_t utils::getSystemTime(uint32_t clock) {
#if _POSIX_TIMERS
    static const clockid_t clocks[] = {
            CLOCK_REALTIME,
            CLOCK_MONOTONIC,
            CLOCK_PROCESS_CPUTIME_ID,
            CLOCK_THREAD_CPUTIME_ID,
            CLOCK_BOOTTIME
    };
    if (isSystemClockAvailable(clock)) {
        struct timespec t;
        t.tv_sec = t.tv_nsec = 0;
        clock_gettime(clocks[clock], &t);
        return nsecs_t(t.tv_sec) * 1000000000LL + t.tv_nsec;
    }
#endif
    struct timeval t;
    t.tv_sec = t.tv_usec = 0;
    gettimeofday(&t, NULL);
    return nsecs_t(t.tv_sec) * 1000000000LL + nsecs_t(t.tv_usec) * 1000LL;
}
