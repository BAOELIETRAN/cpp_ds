#include <gtest/gtest.h>
#include "../src/doubly_linked_list.h"

TEST(InitializingTest, DefaultConstructor){
    tehran::new_list<std::string> list{};
    EXPECT_EQ(list.size(), 0);
}
