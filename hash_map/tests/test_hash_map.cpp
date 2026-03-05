#include "hash_map.h"
#include <gtest/gtest.h>

TEST(InitializingTest, DefaultConstructor){
    anh_phan::hash_map new_map{};
    EXPECT_EQ(new_map.size(), 0);
    EXPECT_EQ(new_map.empty(), true);
}

TEST(InitializingTest, OtherMembers){
    anh_phan::hash_map new_map{};
    EXPECT_EQ(new_map.contains(22), false);
    new_map[1] = 33;
    new_map[19] = 20;
    new_map[10] = 3333;
    EXPECT_EQ(new_map.size(), 3);
    EXPECT_EQ(new_map.empty(), false);
    EXPECT_EQ(new_map.contains(19), true);
    EXPECT_EQ(new_map[10], 3333);
    new_map.erase(10);
    EXPECT_EQ(new_map.size(), 2);
    EXPECT_EQ(new_map[10], 0);
    anh_phan::hash_map::iterator it = new_map.find(10);
    EXPECT_EQ(it->second, 0);
    it = new_map.find(1);
    EXPECT_EQ(it->second, 33);
}