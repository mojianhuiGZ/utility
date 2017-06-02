#include "gtest/gtest.h"
#include "utils/Singleton.h"

using utils::Singleton;
using utils::Mutex;

class Add : public Singleton<Add> {
public:
    int add(int a, int b) {
        return a + b;
    }
};

SINGLETON_STATIC_INSTANCE(Add);

TEST(Singleton, getInstance) {
    ASSERT_TRUE(!Add::hasInstance());
    ASSERT_EQ(Add::getInstance().add(1, 2), 3);
    ASSERT_TRUE(Add::hasInstance());
}

