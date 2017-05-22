#include "utils/String.h"
#include "gtest/gtest.h"

using utils::String;

TEST(String, lengthAndCapacity) {
    char buf[100];
    String s(buf, sizeof(buf));
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.capacity(), sizeof(buf));
    s = "hello";
    ASSERT_EQ(s.length(), 5);
    ASSERT_EQ(s.capacity(), sizeof(buf));
}

TEST(String, equal) {
    char buf[100];
    String s(buf, sizeof(buf));
    ASSERT_TRUE(s == "");
    s = "hello";
    ASSERT_TRUE(s == "hello");
    ASSERT_FALSE(s == "hell");
}

TEST(String, notequal) {

}

TEST(String, append) {
    char buf[100];
    String s(buf, sizeof(buf));
    s.append("hello");
    ASSERT_TRUE(s == "hello");
    s.append("World!");
    ASSERT_TRUE(s == "helloWorld!");

    char buf1[100];
    String s1(buf1, sizeof(buf1));
    s1 = "Good";
    s.append(s1);
    ASSERT_TRUE(s == "helloWorld!Good");
}

TEST(String, isStartWith) {
    char buf[100];
    String s(buf, sizeof(buf));
    s = "hello";
    ASSERT_TRUE(s.isStartWith("he"));
}