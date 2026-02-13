#ifndef SOSA_BST_H
#define SOSA_BST_H

#include <cstddef>
#include <stdexcept>

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
            std::size_t m_num_nodes{};
            TreeNode* root{};
        public:
            /* constructors */
            binary_search_tree() = default;
            binary_search_tree(const binary_search_tree& other_tree);
            ~binary_search_tree() = default;

            /* member functions */
    };
}

#endif
