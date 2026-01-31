#include <gtest/gtest.h>
#include "vector.h"

// first arg: name of test suite
// second arg: name of test case
// the name should not contain "_"
// tests from different test suites can have the same name
TEST(InitializingTest, ZeroElement){
    mck::my_vector<std::string> vlxx;
    EXPECT_EQ(vlxx.get_size(), 0);
}

TEST(InitializingTest, SomeElements){
    mck::my_vector<std::string> vlxx(3);
    EXPECT_EQ(vlxx.get_size(), 3);
    for (int i = 0; i < vlxx.get_size(); i ++){
        EXPECT_EQ(vlxx[i], std::string());
    }
}

TEST(InitializingTest, CopyVector){
    mck::my_vector<std::string> vlxx(2);
    vlxx[0] = "aaa";
    vlxx[1] = "bbb";
    mck::my_vector copy_vlxx(vlxx);
    EXPECT_EQ(copy_vlxx.get_size(), 2);
    EXPECT_EQ(copy_vlxx[0], "aaa");
    EXPECT_EQ(copy_vlxx[1], "bbb");
}

TEST(MemberFunctionTest, EmptyTest){
    mck::my_vector<std::string> vlxx(2);
    EXPECT_EQ(vlxx.is_empty(), false);
    mck::my_vector<std::string> xnxx;
    EXPECT_EQ(xnxx.is_empty(), true);
}

TEST(MemberFunctionTest, AtTest){
    mck::my_vector<std::string> vlxx(2);
    vlxx[0] = "aaa";
    vlxx[1] = "bbb";
    EXPECT_EQ(vlxx.at(0), "aaa");
    EXPECT_EQ(vlxx.at(1), "bbb");
    EXPECT_THROW(vlxx.at(-1), std::out_of_range);
    EXPECT_THROW(vlxx.at(3), std::out_of_range);
}

TEST(MemberFunctionTest, PushBack){
    mck::my_vector<std::string> vlxx;
    vlxx.push_back("aaa");
    vlxx.push_back("bbb");
    EXPECT_EQ(vlxx.get_size(), 2);
    EXPECT_EQ(vlxx[0], "aaa");
    EXPECT_EQ(vlxx[1], "bbb");
}

TEST(MemberFunctionTest, PopBack){
    mck::my_vector<std::string> vlxx;
    vlxx.push_back("aaa");
    vlxx.push_back("bbb");
    vlxx.pop_back();
    EXPECT_EQ(vlxx.get_size(), 1);
    EXPECT_THROW(vlxx.at(1), std::out_of_range);
}

TEST(MemberFunctionTest, Clear){
    mck::my_vector<std::string> vlxx;
    vlxx.push_back("aaa");
    vlxx.push_back("bbb");
    vlxx.clear();
    EXPECT_EQ(vlxx.get_size(), 0);
    EXPECT_THROW(vlxx.at(1), std::out_of_range);
}
