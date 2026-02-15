#include "bst.h"

namespace sosa{
    /* constructor & destructor*/
    binary_search_tree::TreeNode* binary_search_tree::initialize(const TreeNode* other_root){
        if (other_root == nullptr){
            return;
        }
        TreeNode* new_root = new (std::nothrow) TreeNode(other_root->val);
        new_root->left = initialize(other_root->left);
        new_root->right = initialize(other_root->right);
        return new_root;
    }

    // intialization will end right after member initializer list
    // anything happen inside the constructor function is assigning, not initializing
    binary_search_tree::binary_search_tree(const binary_search_tree& other_tree) : m_root{initialize(other_tree.m_root)}, m_size{other_tree.m_size}{
        // empty
    }

    // clean up the whole tree
    void binary_search_tree::clean_up(const TreeNode* root){
        if (root == nullptr){
            return;
        }
        TreeNode* left_side = root->left;
        TreeNode* right_side = root->right;
        delete root;
        root = nullptr;
        clean_up(left_side);
        clean_up(right_side);
    }

    binary_search_tree::~binary_search_tree(){
        clean_up(m_root);
        m_size = 0;
    }

    /* member functions */
    // pre order print
    void binary_search_tree::pre_order_helper(const TreeNode* root) const{
        if (root == nullptr){
            return;
        }
        std::cout << root->val << ' ';
        pre_order_helper(root->left);
        pre_order_helper(root->right);
    }

    void binary_search_tree::pre_order_print() const{
        pre_order_helper(m_root);
        std::cout << '\n';
    }
    
    // in order print
    void binary_search_tree::in_order_helper(const TreeNode* root) const{
        if (root == nullptr){
            return;
        }
        in_order_helper(root->left);
        std::cout << root->val << ' ';
        in_order_helper(root->right);
    }

    void binary_search_tree::in_order_print() const{
        in_order_helper(m_root);
        std::cout << '\n';
    }

    // post order print
    void binary_search_tree::post_order_helper(const TreeNode* root) const{
        if (root == nullptr){
            return;
        }
        post_order_helper(root->left);
        post_order_helper(root->right);
        std::cout << root->val << ' ';
    }

    void binary_search_tree::post_order_print() const{
        post_order_helper(m_root);
        std::cout << '\n';
    }

    // insert into a tree
    void binary_search_tree::insert_helper(TreeNode* root, int val){
        if (root == nullptr){
            TreeNode* new_node = new TreeNode(val);
            root = new_node;
            m_size ++;
            return;
        }
        if (val < root->val){
            if (root->left == nullptr){
                TreeNode* new_node = new TreeNode(val);
                root->left = new_node;
                m_size ++;
            }
            else{
                insert_helper(root->left, val);
            }
        }
        else if (val >= root->val){
            if (root->right == nullptr){
                TreeNode* new_node = new TreeNode(val);
                root->right = new_node;
                m_size ++;
            }
            else{
                insert_helper(root->right, val);
            }  
        }
    }
    
    void binary_search_tree::insert(int val){
        insert_helper(m_root, val);
    }
}