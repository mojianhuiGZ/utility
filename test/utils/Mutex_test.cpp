#include "gtest/gtest.h"
#include "utils/Mutex.h"
#include "utils/Errors.h"

using namespace utils;

Mutex gLock(Mutex::PRIVATE);

TEST(Mutex, lock) {
    ASSERT_EQ(gLock.lock(), NO_ERROR);
    ASSERT_LT(gLock.tryLock(), 0);
    gLock.unlock();
}

TEST(AutoMutex, lock) {
    AutoMutex _l(gLock);
    ASSERT_LT(gLock.tryLock(), 0);
}
