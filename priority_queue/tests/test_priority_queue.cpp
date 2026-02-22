#include "priority_queue.h"
#include <gtest/gtest.h>

TEST(InitializingTest, ZeroElement){
    gio::priority_queue p_queue{};
    EXPECT_EQ(p_queue.size(), 0);
    EXPECT_EQ(p_queue.empty(), true);
}

TEST(MemberTest, PushElement){
    gio::priority_queue p_queue{};
    for (int num = 9; num >= 0; num --){
        p_queue.push(num);
    }
    EXPECT_EQ(p_queue.size(), 10);
    EXPECT_EQ(p_queue.empty(), false);
    EXPECT_EQ(p_queue.top(), 0);
}

TEST(MemberTest, PopElement){
    gio::priority_queue p_queue{};
    for (int num = 9; num >= 0; num --){
        p_queue.push(num);
    }
    EXPECT_EQ(p_queue.top(), 0);
    p_queue.pop();
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), 2);
    EXPECT_EQ(p_queue.size(), 8);
    EXPECT_EQ(p_queue.empty(), false);
}


