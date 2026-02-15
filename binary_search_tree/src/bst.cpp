#include "bst.h"

namespace sosa{
    /* constructor & destructor*/
    binary_search_tree::TreeNode* binary_search_tree::initialize(const TreeNode* other_root){
        if (other_root == nullptr){
            return;
        }
        TreeNode* new_root = new (std::nothrow) TreeNode(other_root->val);
        if (new_root != nullptr) new_root->left = initialize(other_root->left);
        if (new_root != nullptr) new_root->right = initialize(other_root->right);
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
            TreeNode* new_node = new (std::nothrow) TreeNode(val);
            root = new_node;
            if (new_node != nullptr) m_size ++;
            return;
        }
        if (val < root->val){
            if (root->left == nullptr){
                TreeNode* new_node = new (std::nothrow) TreeNode(val);
                root->left = new_node;
                if (new_node != nullptr) m_size ++;
            }
            else{
                insert_helper(root->left, val);
            }
        }
        else if (val >= root->val){
            if (root->right == nullptr){
                TreeNode* new_node = new (std::nothrow) TreeNode(val);
                root->right = new_node;
                if (new_node != nullptr) m_size ++;
            }
            else{
                insert_helper(root->right, val);
            }  
        }
    }
    
    void binary_search_tree::insert(int val){
        insert_helper(m_root, val);
    }

    // contain?
    bool binary_search_tree::contains_helper(TreeNode* root, int val) const{
        if (root == nullptr){
            return false;
        }
        if (root->val == val){
            return true;
        }
        return contains_helper(root->left, val) || contains_helper(root->right, val);
    }

    bool binary_search_tree::contains(int val) const{
        contains_helper(m_root, val);
    }

    // find
    binary_search_tree::TreeNode* binary_search_tree::find_helper(TreeNode* root, int val) const{
        if (root == nullptr){
            return nullptr;
        }
        if (root->val == val){
            return root;
        }
        else if (val < root->val){
            find_helper(root->left, val);
        }
        else{
            find_helper(root->right, val);
        }
        return nullptr;
    }

    binary_search_tree::TreeNode* binary_search_tree::find(int val) const{
        return find_helper(m_root, val);
    }

    // remove a node from the tree
    
}