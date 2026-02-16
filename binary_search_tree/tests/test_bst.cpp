#include <gtest/gtest.h>
#include "bst.h"

TEST(InitializingTest, DefaultConstructor){
    sosa::binary_search_tree tree{};
    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_EQ(tree.empty(), true);
}

TEST(HelperFunctionTest, InsertTest){
    sosa::binary_search_tree tree{};
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
    tree.insert(7);
    tree.insert(9);
    EXPECT_EQ(tree.get_size(), 5);
    EXPECT_EQ(tree.empty(), false);
    EXPECT_EQ(tree.find_min(), 6);
    EXPECT_EQ(tree.find_max(), 9);
    EXPECT_EQ(tree.get_height(), 3);
    EXPECT_EQ(tree.contains(3), false);
    EXPECT_EQ(tree.contains(7), true);
    tree.pre_order_print();
    tree.in_order_print();
    tree.post_order_print();
}

TEST(HelperFunctionTest, RemoveTest){
    sosa::binary_search_tree tree{};
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
    tree.insert(7);
    tree.insert(9);
    // // delete non-existing node
    tree.remove(3);
    EXPECT_EQ(tree.get_size(), 5);
    std::cout << "After removing 3: " << '\n';
    tree.in_order_print();
    // delete a leaf node
    tree.remove(9);
    EXPECT_EQ(tree.get_size(), 4);
    std::cout << "After removing 9: " << '\n';
    tree.in_order_print();
    // delete a node with one child
    tree.remove(8);
    EXPECT_EQ(tree.get_size(), 3);
    std::cout << "After removing 8: " << '\n';
    tree.in_order_print();  
    // delete a node with two children
    tree.remove(7);
    EXPECT_EQ(tree.get_size(), 2);
    std::cout << "After removing 7: " << '\n';
    tree.in_order_print();   
}