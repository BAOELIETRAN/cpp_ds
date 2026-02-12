#include "stack.h"
#include <gtest/gtest.h>

// first arg: name of test suite
// second arg: name of test case
// the name should not contain "_"
// tests from different test suites can have the same name
TEST(InitializingTest, ZeroElement){
    wxrdie::my_stack<int> stack{};
    EXPECT_EQ(stack.size(), 0);
}

TEST(InitializingTest, CopyConstruct){
    wxrdie::my_stack<int> first_stack{};
    first_stack.push(2);
    first_stack.push(9);
    first_stack.push(1);
    wxrdie::my_stack<int> second_stack{first_stack};
    EXPECT_EQ(second_stack.size(), 3);
}

TEST(InitializingTest, CopyAssign){
    wxrdie::my_stack<int> first_stack{};
    wxrdie::my_stack<int> second_stack{};
    second_stack.push(2);
    second_stack.push(9);
    second_stack.push(1);
    first_stack = second_stack;
    EXPECT_EQ(first_stack.size(), 3);
}

TEST(InitializingTest, GetTop){
    wxrdie::my_stack<int> first_stack{};
    first_stack.push(2);
    first_stack.push(9);
    first_stack.push(1);
    EXPECT_EQ(first_stack.top(), 1);
}

TEST(InitializingTest, CheckEmpty){
    wxrdie::my_stack<int> first_stack{};
    first_stack.push(2);
    first_stack.push(9);
    first_stack.push(1);
    EXPECT_EQ(first_stack.empty(), false);
}

TEST(InitializingTest, GetSize){
    wxrdie::my_stack<int> first_stack{};
    first_stack.push(2);
    first_stack.push(9);
    first_stack.push(1);
    EXPECT_EQ(first_stack.size(), 3);
}

TEST(InitializingTest, CheckPush){
    wxrdie::my_stack<int> first_stack{};
    first_stack.push(2);
    first_stack.push(9);
    first_stack.push(1);
    EXPECT_EQ(first_stack.size(), 3);
}

TEST(InitializingTest, CheckPop){
    wxrdie::my_stack<int> first_stack{};
    first_stack.push(2);
    first_stack.push(9);
    first_stack.push(1);
    EXPECT_EQ(first_stack.size(), 3);
    EXPECT_EQ(first_stack.top(), 1);
    first_stack.pop();
    EXPECT_EQ(first_stack.size(), 2);
    EXPECT_EQ(first_stack.top(), 9);
}