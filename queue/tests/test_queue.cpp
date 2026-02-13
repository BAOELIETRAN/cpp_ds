#include "queue.h"
#include <string>
#include <gtest/gtest.h>

TEST(InitializingTest, ZeroElement){
    betekar::my_queue<std::string> queue{};
    EXPECT_EQ(queue.size(), 0);
}

TEST(InitializingTest, CopyConstruct){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    betekar::my_queue<std::string> second_queue{first_queue};
    EXPECT_EQ(second_queue.size(), 3);
}

TEST(InitializingTest, CopyAssign){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    betekar::my_queue<std::string> second_queue{};
    second_queue.push("1");
    second_queue.push("2");
    second_queue.push("3");
    second_queue.push("4");
    second_queue.push("5");
    second_queue.push("6");
    second_queue = first_queue;
    EXPECT_EQ(second_queue.size(), 3);
}

TEST(InitializingTest, TestFront){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    EXPECT_EQ(first_queue.front(), "sdfsdf");
}

TEST(InitializingTest, TestBack){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    EXPECT_EQ(first_queue.back(), "aaaaa");
}

TEST(InitializingTest, TestPush){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    EXPECT_EQ(first_queue.size(), 3);
}

TEST(InitializingTest, TestPop){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    first_queue.pop();
    EXPECT_EQ(first_queue.front(), "qqqq");
}

TEST(InitializingTest, TestEmpty){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    EXPECT_EQ(first_queue.empty(), false);
}

TEST(InitializingTest, TestSize){
    betekar::my_queue<std::string> first_queue{};
    first_queue.push("sdfsdf");
    first_queue.push("qqqq");
    first_queue.push("aaaaa");
    EXPECT_EQ(first_queue.size(), 3);
}