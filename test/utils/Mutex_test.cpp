#include "gtest/gtest.h"
#include "utils/Mutex.h"

using namespace utils;

Mutex gLock("global test lock");

TEST(Mutex, lock) {
    ASSERT_EQ(gLock.lock(), NO_ERROR);
    ASSERT_FALSE(gLock.tryLock());
    gLock.unlock();
}

TEST(AutoMutex, lock) {
    AutoMutex _l(gLock);
    ASSERT_FALSE(gLock.tryLock());
}
