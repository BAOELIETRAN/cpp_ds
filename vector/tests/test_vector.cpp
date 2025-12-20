#include <gtest/gtest.h>
#include "vector.h"

// first arg: name of test suite
// second arg: name of test case
// the name should not contain "_"
// tests from different test suites can have the same name
TEST(AddingTest, HandleNegativeInt){
    EXPECT_EQ(add(4, -5), -1);
    EXPECT_EQ(add(1, -3), -2);
}

TEST(AddingTest, HandlePositiveInt){
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(3, 5), 8);
}
