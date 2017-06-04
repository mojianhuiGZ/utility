#ifndef _UTLS_TIMERS_H
#define _UTLS_TIMERS_H

#include <cstdint>

namespace utils {
    typedef int64_t nsecs_t; // nano-seconds

    static inline nsecs_t seconds_to_nanoseconds(nsecs_t secs) {
        return secs * 1000000000;
    }

    static inline nsecs_t milliseconds_to_nanoseconds(nsecs_t secs) {
        return secs * 1000000;
    }

    static inline nsecs_t microseconds_to_nanoseconds(nsecs_t secs) {
        return secs * 1000;
    }

    static inline nsecs_t nanoseconds_to_seconds(nsecs_t secs) {
        return secs / 1000000000;
    }

    static inline nsecs_t nanoseconds_to_milliseconds(nsecs_t secs) {
        return secs / 1000000;
    }

    static inline nsecs_t nanoseconds_to_microseconds(nsecs_t secs) {
        return secs / 1000;
    }

    static inline nsecs_t s2ns(nsecs_t v) { return seconds_to_nanoseconds(v); }

    static inline nsecs_t ms2ns(nsecs_t v) { return milliseconds_to_nanoseconds(v); }

    static inline nsecs_t us2ns(nsecs_t v) { return microseconds_to_nanoseconds(v); }

    static inline nsecs_t ns2s(nsecs_t v) { return nanoseconds_to_seconds(v); }

    static inline nsecs_t ns2ms(nsecs_t v) { return nanoseconds_to_milliseconds(v); }

    static inline nsecs_t ns2us(nsecs_t v) { return nanoseconds_to_microseconds(v); }

    static inline nsecs_t seconds(nsecs_t v) { return s2ns(v); }

    static inline nsecs_t milliseconds(nsecs_t v) { return ms2ns(v); }

    static inline nsecs_t microseconds(nsecs_t v) { return us2ns(v); }

    enum {
        SYSTEM_TIME_REALTIME = 0,  // system-wide realtime clock, always available
        SYSTEM_TIME_MONOTONIC = 1, // monotonic time since unspecified starting point
        SYSTEM_TIME_PROCESS = 2,   // high-resolution per-process clock
        SYSTEM_TIME_THREAD = 3,    // high-resolution per-thread clock
        SYSTEM_TIME_BOOTTIME = 4   // same as SYSTEM_TIME_MONOTONIC, but including CPU suspend time
    };

    bool isSystemClockAvailable(uint32_t clock);

    // if the specified system clock is not available, SYSTEM_TIME_REALTIME will be used instead
    nsecs_t getSystemTime(uint32_t clock = SYSTEM_TIME_MONOTONIC);
}

#endif //_UTLS_TIMERS_H
