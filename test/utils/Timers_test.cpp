#include "utils/Timers.h"
#include "gtest/gtest.h"

using namespace utils;

TEST(Timers, getSystemTime) {
    ASSERT_GT(getSystemTime(SYSTEM_TIME_REALTIME), 0);
    ASSERT_TRUE(!isSystemClockAvailable(SYSTEM_TIME_MONOTONIC) || (getSystemTime(SYSTEM_TIME_MONOTONIC) > 0));
    ASSERT_TRUE(!isSystemClockAvailable(SYSTEM_TIME_PROCESS) || (getSystemTime(SYSTEM_TIME_PROCESS) > 0));
    ASSERT_TRUE(!isSystemClockAvailable(SYSTEM_TIME_THREAD) || (getSystemTime(SYSTEM_TIME_THREAD) > 0));
    ASSERT_TRUE(!isSystemClockAvailable(SYSTEM_TIME_BOOTTIME) || (getSystemTime(SYSTEM_TIME_BOOTTIME) > 0));
}
