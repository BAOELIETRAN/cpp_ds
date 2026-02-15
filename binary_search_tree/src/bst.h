#ifndef SOSA_BST_H
#define SOSA_BST_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <tuple>

namespace sosa{
    class binary_search_tree{
        private:
            struct TreeNode{
                int val{};
                TreeNode* left{};
                TreeNode* right{};
                // default constructor
                TreeNode() = default;
                // initialize --> member initializer list
                TreeNode(int value) : val{value}, left{nullptr}, right{nullptr}{};
            };
            std::size_t m_size{};
            TreeNode* m_root{};
            TreeNode* initialize(const TreeNode* other_root);
            void clean_up(const TreeNode* root);
            /* helper functions */
            void pre_order_helper(const TreeNode* root) const;
            void in_order_helper(const TreeNode* root) const;
            void post_order_helper(const TreeNode* root) const;
            void insert_helper(TreeNode* root, int val);
            bool contains_helper(const TreeNode* root, int val) const;
            std::tuple<TreeNode*, TreeNode*> find_helper(TreeNode* root, int val) const;
            void remove_helper(TreeNode* root, int val);
            TreeNode* find_min_helper(TreeNode* root) const;
            TreeNode* find_max_helper(TreeNode* root) const;
        public:
            /* constructors */
            binary_search_tree() = default;
            binary_search_tree(const binary_search_tree& other_tree);
            // need to self-implement to delete nodes
            ~binary_search_tree();

            /* member functions */
            // traversal
            
            void pre_order_print() const;
            void in_order_print() const;
            void post_order_print() const;

            // basic operations
            // insert a node to the tree
            void insert(int val);
            // delete a node from the tree
            void remove(int val);
            // check whether the tree contains a node with value
            bool contains(int val) const;
            // find the first node with value
            TreeNode* find(int val) const;
            // find max value of the tree
            int find_min() const;
            // find min value of the tree
            int find_max() const;
            // find height of the tree
            int get_height() const;
            // get size of the tree
            int get_size() const { return m_size; };
            // check whether the tree is empty
            bool empty() const { return m_size == 0; };
            // clear the tree
            void clear();
    };
}

#endif
