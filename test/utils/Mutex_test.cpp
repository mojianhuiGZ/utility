#include "gtest/gtest.h"
#include "utils/Mutex.h"

using namespace utils;

Mutex ALock("global test lock");

TEST(Mutex, lock) {
    ASSERT_EQ(ALock.lock(), NO_ERROR);
    ASSERT_FALSE(ALock.tryLock());
    ALock.unlock();
}

TEST(AutoMutex, lock) {
    AutoMutex _l(ALock);
    ASSERT_FALSE(ALock.tryLock());
}
