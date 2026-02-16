#include "bst.h"

namespace sosa{
    /* constructor & destructor*/
    binary_search_tree::TreeNode* binary_search_tree::initialize(TreeNode* other_root){
        if (other_root == nullptr){
            return nullptr;
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
    void binary_search_tree::clean_up(TreeNode*& root){
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
    // need to pass by pointer reference because pointer is just a variable that holds address
    //  if we just change the value of the param (pointer) --> does not mean anything
    void binary_search_tree::insert_helper(TreeNode*& root, int val){
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
    bool binary_search_tree::contains_helper(const TreeNode* root, int val) const{
        if (root == nullptr){
            return false;
        }
        if (root->val == val){
            return true;
        }
        return contains_helper(root->left, val) || contains_helper(root->right, val);
    }

    bool binary_search_tree::contains(int val) const{
        return contains_helper(m_root, val);
    }

    // find
    std::tuple<binary_search_tree::TreeNode*, binary_search_tree::TreeNode*> binary_search_tree::find_helper(TreeNode* root, int val) const{
        TreeNode* cur_parent = nullptr;
        TreeNode* cur_node = nullptr;
        TreeNode* temp = root;
        if (root == nullptr){
            std::cerr << "Tree is currently empty!" << '\n';
            return std::make_tuple(nullptr, nullptr);
        }
        // using iteration
        while (temp != nullptr){
            if (val == temp->val){
                break;
            }
            else if (val < temp->val){
                cur_parent = temp;
                temp = temp->left;
            }
            else if (val > temp->val){
                cur_parent = temp;
                temp = temp->right;
            }
        }
        cur_node = temp;
        if (cur_node == nullptr){
            std::cerr << "Can not find node!" << '\n';
        }
        return std::make_tuple(cur_parent, cur_node);
    }

    binary_search_tree::TreeNode* binary_search_tree::find(int val) const{
        auto tree_tuple = find_helper(m_root, val);
        return std::get<1>(tree_tuple);
    }

    // find min on a tree
    binary_search_tree::TreeNode* binary_search_tree::find_min_helper(TreeNode* root) const{
        if (root == nullptr){
            return nullptr;
        }
        TreeNode* temp = root;
        while (temp->left != nullptr){
            temp = temp->left;
        }
        return temp;
    }   

    int binary_search_tree::find_min() const{
        TreeNode* cur_node = find_min_helper(m_root);
        return (cur_node == nullptr)? INT_MIN : cur_node->val;
    }

    // find max on a tree
    binary_search_tree::TreeNode* binary_search_tree::find_max_helper(TreeNode* root) const{
        if (root == nullptr){
            return nullptr;
        }
        TreeNode* temp = root;
        while (temp->right != nullptr){
            temp = temp->right;
        }
        return temp;
    }

    int binary_search_tree::find_max() const{
        TreeNode* cur_node = find_max_helper(m_root);
        return (cur_node == nullptr)? INT_MIN : cur_node->val;
    }

    // remove a node from the tree
    void binary_search_tree::remove_helper(TreeNode*& root, int val){
        if (root == nullptr){
            std::cerr << "Tree is currently empty!" << '\n';
            return;
        }
        auto tree_tuple = find_helper(root, val);
        TreeNode* cur_parent = std::get<0>(tree_tuple);
        TreeNode* cur_node = std::get<1>(tree_tuple);
        // can not find node
        if (cur_node == nullptr){
            return;
        }
        bool is_left = (cur_parent != nullptr && cur_node->val < cur_parent->val)? true : false;
        bool is_root = false;
        // if delete root node
        if (cur_parent == nullptr && cur_node != nullptr){
            is_root = true;
        }
        // case 1: delete a leaf node
        if (cur_node->left == nullptr && cur_node->right == nullptr){
            delete cur_node;
            cur_node = nullptr;
            if (is_root == false){
                if (is_left) cur_parent->left = nullptr;
                else cur_parent->right = nullptr;
            }
        }
        // case 2: delete a node with 1 child
        else if (cur_node->left != nullptr && cur_node->right == nullptr){
            TreeNode* next_node = cur_node->left;
            delete cur_node;
            cur_node = nullptr;
            cur_node = next_node;
            if (is_root == false){
                if (is_left) cur_parent->left = cur_node;
                else cur_parent->right = cur_node;
            }
        }
        else if (cur_node->left == nullptr && cur_node->right != nullptr){
            TreeNode* next_node = cur_node->right;
            delete cur_node;
            cur_node = nullptr;
            cur_node = next_node;
            if (is_root == false){
                if (is_left) cur_parent->left = cur_node;
                else cur_parent->right = cur_node;
            }
        }
        // case 3: delete a node with 2 children
        // replace with:
        // - max on the left tree
        // OR
        // - min on the right tree
        // case 3: delete a node with 2 children
        else{
            // find min on the right tree
            TreeNode* min_right = find_min_helper(cur_node->right);
            int min_right_val = min_right->val;
            std::tuple<TreeNode*, TreeNode*> min_right_tuple = find_helper(cur_node->right, min_right_val);
            TreeNode* min_right_parent_temp = std::get<0>(min_right_tuple);
            TreeNode* min_right_found = std::get<1>(min_right_tuple);
            cur_node->val = min_right_val;
            TreeNode* min_right_parent = (min_right_parent_temp == nullptr) ? cur_node : min_right_parent_temp;
            // can not go any further left, but what if right is not null?
            if (min_right->right != nullptr){
                if (min_right_parent == cur_node){
                    cur_node->right = min_right->right;
                }
                else{
                    min_right_parent->left = min_right->right;
                }
            }
            else{
                if (min_right_parent == cur_node){
                    min_right_parent->right = nullptr;
                }
                else{
                    min_right_parent->left = nullptr;
                }
            }
            delete min_right;
            min_right = nullptr;
        }
        m_size--;
    }

    void binary_search_tree::remove(int val){
        remove_helper(m_root, val);
    }

    // get height 
    // using lambda (C++ 23)
    // this (not "this" pointer in class):
    // - treat this lambda object as a parameter
    // - auto& - reference to a lambda
    int binary_search_tree::get_height() const{
        auto cal_height = [](this auto& self, TreeNode* root) -> int{
            if (root == nullptr){
                return 0;
            }
            int left_height = self(root->left);
            int right_height = self(root->right);
            return std::max(left_height, right_height) + 1;
        };
        return cal_height(m_root);
    }

    // clear the tree
    void binary_search_tree::clear(){
        clean_up(m_root);
        m_size = 0;
    }
}