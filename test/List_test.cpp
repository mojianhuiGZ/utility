#include "utils/List.h"
#include "gtest/gtest.h"

using utils::List;

TEST(List, empty) {
    List<int> list;
    ASSERT_TRUE(list.isEmpty());
    ASSERT_EQ(list.size(), 0);
}

TEST(List, traversal) {
    List<int> list;
    List<int>::Iterator it(list);
    int i;

    for (i = 0; i < 10; i++) {
        list.pushBack(i);
    }

    for (it = list.begin(), i = 0; !it.isNull(); it++, i++) {
        ASSERT_EQ(*it.getVal(), i);
    }

    for (it = list.end(), i--; !it.isNull(); it--, i--) {
        ASSERT_EQ(*it.getVal(), i);
    }
}