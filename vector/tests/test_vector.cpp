#include <gtest/gtest.h>
#include "vector.h"

// first arg: name of test suite
// second arg: name of test case
// the name should not contain "_"
// tests from different test suites can have the same name
TEST(InitializingTest, ZeroElement){
    mck::my_vector vlxx;
    EXPECT_EQ(vlxx.get_size(), 0);
}

TEST(InitializingTest, SomeElements){
    mck::my_vector vlxx(3);
    EXPECT_EQ(vlxx.get_size(), 3);
    for (int i = 0; i < vlxx.get_size(); i ++){
        EXPECT_EQ(vlxx[i], 0);
    }
}

TEST(InitializingTest, CopyVector){
    mck::my_vector vlxx(2);
    vlxx[0] = 1;
    vlxx[1] = 7;
    mck::my_vector copy_vlxx(vlxx);
    EXPECT_EQ(copy_vlxx.get_size(), 2);
    EXPECT_EQ(copy_vlxx[0], 1);
    EXPECT_EQ(copy_vlxx[1], 7);
}

TEST(MemberFunctionTest, EmptyTest){
    mck::my_vector vlxx(2);
    EXPECT_EQ(vlxx.is_empty(), false);
    mck::my_vector xnxx;
    EXPECT_EQ(xnxx.is_empty(), true);
}

TEST(MemberFunctionTest, AtTest){
    mck::my_vector vlxx(2);
    vlxx[0] = 6;
    vlxx[1] = 7;
    EXPECT_EQ(vlxx.at(0), 6);
    EXPECT_EQ(vlxx.at(1), 7);
    EXPECT_THROW(vlxx.at(-1), std::out_of_range);
    EXPECT_THROW(vlxx.at(3), std::out_of_range);
}

TEST(MemberFunctionTest, PushBack){
    mck::my_vector vlxx;
    vlxx.push_back(1);
    vlxx.push_back(3);
    EXPECT_EQ(vlxx.get_size(), 2);
    EXPECT_EQ(vlxx[0], 1);
    EXPECT_EQ(vlxx[1], 3);
}

TEST(MemberFunctionTest, PopBack){
    mck::my_vector vlxx;
    vlxx.push_back(1);
    vlxx.push_back(3);
    vlxx.pop_back();
    EXPECT_EQ(vlxx.get_size(), 1);
    EXPECT_THROW(vlxx.at(1), std::out_of_range);
}

TEST(MemberFunctionTest, Clear){
    mck::my_vector vlxx;
    vlxx.push_back(1);
    vlxx.push_back(3);
    vlxx.clear();
    EXPECT_EQ(vlxx.get_size(), 0);
    EXPECT_THROW(vlxx.at(1), std::out_of_range);
}
