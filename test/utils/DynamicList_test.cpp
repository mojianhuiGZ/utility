#include "utils/DynamicList.h"
#include "gtest/gtest.h"

using utils::DynamicList;

// TODO: memory leak test

TEST(DynamicList, isEmpty) {
    DynamicList<int> list;
    ASSERT_TRUE(list.isEmpty());
}

TEST(DynamicList, size) {
    DynamicList<int> list;
    ASSERT_EQ(list.size(), 0);

    int n = 10;
    for (int i = 0; i < n; i++) {
        list.pushBack(i);
    }
    ASSERT_EQ(list.size(), n);
}

TEST(DynamicList, clear) {
    DynamicList<int> list;
    int n = 10;
    for (int i = 0; i < n; i++) {
        list.pushBack(i);
    }
    list.clear();
    ASSERT_TRUE(list.isEmpty());
}

TEST(DynamicList, pushBack) {
    DynamicList<int> list;
    DynamicList<int>::Iterator it(list);
    int i, n = 10;
    for (i = 0; i < n; i++) {
        list.pushBack(i);
    }
    for (it = list.begin(), i = 0; !it.isNull(); it++, i++) {
        ASSERT_EQ(*it.getVal(), i);
    }
}

TEST(DynamicList, pushFront) {
    DynamicList<int> list;
    DynamicList<int>::Iterator it(list);
    int i, n = 10;
    for (i = 0; i < n; i++) {
        list.pushFront(i);
    }
    for (it = list.end(), i = 0; !it.isNull(); it--, i++) {
        ASSERT_EQ(*it.getVal(), i);
    }
}

//TEST(DynamicList, popBack) {
//    DynamicList<int> list;
//    int val;
//    int n = 10;
//    for (int i = 0; i < n; i++) {
//        list.pushFront(i);
//    }
//    for (int i = 0; i < n; i++) {
//        list.popBack(val);
//        ASSERT_EQ(val, i);
//    }
//    ASSERT_TRUE(!list.popBack(val));
//}
//
//TEST(DynamicList, popFront) {
//    DynamicList<int> list;
//    int val;
//    int n = 10;
//    for (int i = 0; i < n; i++) {
//        list.pushBack(i);
//    }
//    for (int i = 0; i < n; i++) {
//        list.popFront(val);
//        ASSERT_EQ(val, i);
//    }
//    ASSERT_TRUE(!list.popFront(val));
//}
