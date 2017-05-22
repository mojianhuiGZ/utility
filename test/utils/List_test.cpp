#include "utils/List.h"
#include "gtest/gtest.h"

using utils::ListNode;

static ListNode gCars;

class Car {
public:
    Car(int number) { mNumber = number; }
    ListNode mNode;
    int mNumber;
};

TEST(List, pushBack) {
    Car a(1), b(2);
    gCars.pushBack(a.mNode);
    gCars.pushBack(b.mNode);
    ListNode *p;
    int i = 1;
    ForeachListNode(p, &gCars) {
        Car *c = GetContainerOfListNode(p, Car, mNode);
        ASSERT_EQ(c->mNumber, i);
        i++;
    }
}

TEST(List, pushFront) {
    Car a(1), b(2);
    gCars.pushFront(a.mNode);
    gCars.pushFront(b.mNode);
    ListNode *p;
    int i = 2;
    ForeachListNode(p, &gCars) {
        Car *c = GetContainerOfListNode(p, Car, mNode);
        ASSERT_EQ(c->mNumber, i);
        i--;
    }
}
