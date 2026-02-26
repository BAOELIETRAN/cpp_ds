#include <gtest/gtest.h>
#include "doubly_linked_list.h"

TEST(InitializingTest, DefaultConstructor){
    ccmk::doubly_linked_list new_list{};
    EXPECT_EQ(new_list.get_size(), 0);
}

TEST(InitializingTest, CopyConstructor){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    ccmk::doubly_linked_list second_list{first_list};
    EXPECT_EQ(second_list.get_size(), 3);
    EXPECT_EQ(second_list.front(), 0);
    EXPECT_EQ(second_list.back(), 2);
}

TEST(InitializingTest, CopyAssignment){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    ccmk::doubly_linked_list second_list{};
    second_list.add_at_tail(33);
    EXPECT_EQ(second_list.get_size(), 1);
    EXPECT_EQ(second_list.front(), 33);
    EXPECT_EQ(second_list.back(), 33);
    second_list = first_list;
    for (int i = 0; i < 3; i ++){
        EXPECT_EQ(second_list.get(i), i);
    }
}

TEST(InitializingTest, MoveConstructor){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    ccmk::doubly_linked_list second_list{std::move(first_list)};
    for (int i = 0; i < 3; i ++){
        EXPECT_EQ(second_list.get(i), i);
    }
}

TEST(InitializingTest, MoveAssignment){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    ccmk::doubly_linked_list second_list{};
    second_list.add_at_tail(33);
    EXPECT_EQ(second_list.get_size(), 1);
    EXPECT_EQ(second_list.front(), 33);
    EXPECT_EQ(second_list.back(), 33);
    second_list = std::move(first_list);
    for (int i = 0; i < 3; i ++){
        EXPECT_EQ(second_list.get(i), i);
    }
}

TEST(IteratingTest, Iterator){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    using Iterator = ccmk::doubly_linked_list::iterator;
    int cur_val = 0;
    for (Iterator it = first_list.begin(); it != first_list.end(); it ++){
        EXPECT_EQ(*it, cur_val);
        cur_val ++;
    }
}

TEST(MemberFunctionTest, AddHead){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_head(i);
    }
    for (int i = 0; i < 3; i ++){
        EXPECT_EQ(first_list.get(i), 3 - i - 1);
    }
}

TEST(MemberFunctionTest, AddIndex){
    ccmk::doubly_linked_list first_list{};
    EXPECT_THROW(first_list.add_at_index(6, 0), std::out_of_range);
    EXPECT_THROW(first_list.add_at_index(-1, 0), std::out_of_range);
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    first_list.add_at_index(1, 0);
    EXPECT_EQ(first_list.get(1), 0);
}

TEST(MemberFunctionTest, DeleteHead){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    first_list.delete_at_head();
    EXPECT_EQ(first_list.get_size(), 2);
    EXPECT_EQ(first_list.front(), 1);
}

TEST(MemberFunctionTest, DeleteTail){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    first_list.delete_at_tail();
    EXPECT_EQ(first_list.get_size(), 2);
    EXPECT_EQ(first_list.back(), 1);
}

TEST(MemberFunctionTest, DeleteAtIndex){
    ccmk::doubly_linked_list first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(i);
    }
    EXPECT_THROW(first_list.delete_at_index(6), std::out_of_range);
    EXPECT_THROW(first_list.delete_at_index(-1), std::out_of_range);
    first_list.delete_at_index(1);
    EXPECT_EQ(first_list.get_size(), 2);
    EXPECT_EQ(first_list.get(1), 2);
}