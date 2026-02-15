#ifndef SOSA_BST_H
#define SOSA_BST_H

#include <cstddef>
#include <stdexcept>
#include <vector>

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
        public:
            /* constructors */
            binary_search_tree() = default;
            binary_search_tree(const binary_search_tree& other_tree);
            // need to self-implement to delete nodes
            ~binary_search_tree();

            /* member functions */
            // traversal
            std::vector<int> pre_order_traversal() const;
            std::vector<int> in_order_traversal() const;
            std::vector<int> post_order_traversal() const;

            // basic operations
            // insert a node to the tree
            void insert(int val);
            // delete a node from the tree
            void remove(int val);
            // check whether the tree contains a node with value
            bool contains(int val) const;
            // find the first node with value
            TreeNode* find(int val);
            // find max value of the tree
            int find_max() const;
            // find min value of the tree
            int find_min() const;
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
