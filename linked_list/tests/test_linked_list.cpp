#include <gtest/gtest.h>
#include "linked_list.h"

TEST(InitializingTest, DefaultConstructor){
    tlinh::my_linked_list<std::string> vlxx{};
    EXPECT_EQ(vlxx.get_size(), 0);
}

TEST(InitializingTest, CopyConstructor){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_tail("6");
    first_list.add_at_tail("7");
    tlinh::my_linked_list second_list{first_list};
    EXPECT_EQ(second_list.get_size(), 2);
    std::cout << second_list.front() << '\n';
    EXPECT_EQ(second_list.front(), "6");
    EXPECT_EQ(second_list.back(), "7");
}

TEST(InitializingTest, OperatorOverloading){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_tail("6");
    first_list.add_at_tail("7");
    tlinh::my_linked_list<std::string> second_list{};
    // copy assignment - replace the current content with the copy of the contents of the other
    second_list = first_list;
    EXPECT_EQ(second_list.get_size(), 2);
    EXPECT_EQ(second_list.front(), "6");
    EXPECT_EQ(second_list.back(), "7");
}

TEST(MemberFunctionTest, GetTest){
    tlinh::my_linked_list<std::string> first_list{};
    for (int i = 0; i < 3; i ++){
        first_list.add_at_tail(std::to_string(i));
    }
    // valid index
    for (int i = 0; i < 3; i ++){
        EXPECT_EQ(first_list.get(i), std::to_string(i));
    }
    // invalid index
    EXPECT_THROW(first_list.get(-1), std::out_of_range);
    EXPECT_THROW(first_list.get(4), std::out_of_range);
}

TEST(MemberFunctionTest, FrontTest){
    tlinh::my_linked_list<std::string> first_list{};
    // invalid index
    EXPECT_THROW(first_list.front(), std::out_of_range);   
    // valid
    first_list.add_at_head("2");
    first_list.add_at_head("1");
    EXPECT_EQ(first_list.front(), "1");  
}

TEST(MemberFunctionTest, BackTest){
    tlinh::my_linked_list<std::string> first_list{};
    // invalid index
    EXPECT_THROW(first_list.back(), std::out_of_range);   
    // valid
    first_list.add_at_tail("2");
    first_list.add_at_tail("4");
    first_list.add_at_head("12");
    EXPECT_EQ(first_list.back(), "4");  
}

TEST(MemberFunctionTest, AddHeadTest){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_head("1");
    first_list.add_at_head("2");
    first_list.add_at_head("3");
    EXPECT_EQ(first_list.get_size(), 3);
    EXPECT_EQ(first_list.front(), "3"); 
}

TEST(MemberFunctionTest, AddTailTest){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_tail("1");
    first_list.add_at_tail("2");
    first_list.add_at_tail("3");
    EXPECT_EQ(first_list.get_size(), 3);
    EXPECT_EQ(first_list.back(), "3");     
}

TEST(MemberFunctionTest, AddIndexTest){
    tlinh::my_linked_list<std::string> first_list{};
    // invalid index
    EXPECT_THROW(first_list.add_at_index(3, "1"), std::out_of_range);   
    // valid index
    first_list.add_at_index(0, "1");
    first_list.add_at_index(1, "2");
    first_list.add_at_index(0, "3");
    EXPECT_EQ(first_list.get_size(), 3);
    EXPECT_EQ(first_list.front(), "3"); 
    EXPECT_EQ(first_list.back(), "2"); 
}

TEST(MemberFunctionTest, DeleteHeadTest){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_index(0, "1");
    first_list.add_at_index(1, "2");
    first_list.add_at_index(0, "3");
    first_list.delete_at_head();
    EXPECT_EQ(first_list.get_size(), 2);
    EXPECT_EQ(first_list.front(), "1"); 
    EXPECT_EQ(first_list.back(), "2"); 
}

TEST(MemberFunctionTest, DeleteTailTest){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_index(0, "1");
    first_list.add_at_index(1, "2");
    first_list.add_at_index(0, "3");
    first_list.delete_at_tail();
    EXPECT_EQ(first_list.get_size(), 2);
    EXPECT_EQ(first_list.front(), "3"); 
    EXPECT_EQ(first_list.back(), "1"); 
}

TEST(MemberFunctionTest, DeleteIndexTest){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_index(0, "1");
    first_list.add_at_index(1, "2");
    first_list.add_at_index(0, "3");
    // invalid index
    EXPECT_THROW(first_list.delete_at_index(-1), std::out_of_range);
    EXPECT_THROW(first_list.delete_at_index(4), std::out_of_range);
    // valid index
    first_list.delete_at_index(1);
    EXPECT_EQ(first_list.get_size(), 2);
    EXPECT_EQ(first_list.front(), "3"); 
    EXPECT_EQ(first_list.back(), "2"); 
}

TEST(MemberFunctionTest, GetSizeTest){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_tail("1");
    first_list.add_at_tail("2");
    first_list.add_at_tail("3");
    EXPECT_EQ(first_list.get_size(), 3);   
}

TEST(MemberFunctionTest, EmptyTest){
    tlinh::my_linked_list<std::string> first_list{};
    first_list.add_at_tail("1");
    first_list.add_at_tail("2");
    first_list.add_at_tail("3");
    EXPECT_EQ(first_list.is_empty(), false);   
}