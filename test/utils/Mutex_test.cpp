#include "gtest/gtest.h"
#include "utils/Mutex.h"
#include "utils/Errors.h"

using utils::Mutex;
using utils::AutoMutex;

Mutex gLock(Mutex::PRIVATE);

TEST(Mutex, lock) {
    ASSERT_EQ(gLock.lock(), utils::NO_ERROR);
    ASSERT_LT(gLock.tryLock(), 0);
    gLock.unlock();
}

TEST(AutoMutex, lock) {
    AutoMutex _l(gLock);
    ASSERT_LT(gLock.tryLock(), 0);
}


