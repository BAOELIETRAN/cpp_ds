#ifndef NEW_BINARY_SEARCH_TREE_H
#define NEW_BINARY_SEARCH_TREE_H

#include <iostream>

namespace baghdad{
    class new_bst{
        private:
            struct TreeNode{
                int m_value{};
                TreeNode* left{};
                TreeNode* right{};
                TreeNode(){};
                TreeNode(int val) : m_value{val}{};
            };
            TreeNode* m_root{};
            std::size_t m_size{};
            TreeNode* clone_tree(TreeNode* cur_root, TreeNode* neigh_root);
            void clean_tree(TreeNode* cur_root);
            std::pair<TreeNode*, TreeNode*> smallest(TreeNode* cur_root);
        public:
            /* constructors */
            // default constructor
            explicit new_bst();
            // copy constructor
            explicit new_bst(const new_bst& neigh_bst);
            // copy assignment
            new_bst& operator=(const new_bst& neigh_bst);
            // move constructor
            explicit new_bst(new_bst&& neigh_bst);
            // move assignment
            new_bst& operator=(new_bst&& neigh_bst);
            // destructor
            ~new_bst();

            /* member functions */
            // O(h)
            void insert(int val);
            // O(h)
            TreeNode* find(int val);
            // O(h)
            bool erase(int val);
            std::size_t size() const { return m_size; };
            bool empty() const { return m_size == 0; };
            void clear() { clean_tree(m_root); m_root = nullptr; m_size = 0; };
    };

    // clone tree
    new_bst::TreeNode* new_bst::clone_tree(TreeNode* cur_root, TreeNode* neigh_root){
        if (neigh_root == nullptr) return nullptr;
        cur_root = new TreeNode(neigh_root->m_value);
        cur_root->left = clone_tree(cur_root->left, neigh_root->left);
        cur_root->right = clone_tree(cur_root->right, neigh_root->right);
        return cur_root;
    }

    // clean tree
    void new_bst::clean_tree(TreeNode* cur_root){
        if (cur_root == nullptr) return;
        TreeNode* left_tree = cur_root->left;
        TreeNode* right_tree = cur_root->right;
        delete cur_root;
        clean_tree(left_tree);
        clean_tree(right_tree);
    }

    // default constructor
    new_bst::new_bst() : m_root{nullptr}, m_size{0}{}

    // copy constructor
    new_bst::new_bst(const new_bst& neigh_bst){
        if (this == &neigh_bst) return;
        TreeNode* neigh_root = neigh_bst.m_root;
        m_size = neigh_bst.size();
        m_root = clone_tree(m_root, neigh_root);
    }

    // copy assignment
    new_bst& new_bst::operator=(const new_bst& neigh_bst){
        if (this == &neigh_bst) return *this;
        // clean tree
        clean_tree(m_root);
        m_root = nullptr;
        m_size = 0;
        // build new tree
        TreeNode* neigh_root = neigh_bst.m_root;
        m_size = neigh_bst.size();
        m_root = clone_tree(m_root, neigh_root);
        return *this;
    }

    // move constructor
    new_bst::new_bst(new_bst&& neigh_bst){
        if (this == &neigh_bst) return;
        m_root = neigh_bst.m_root;
        neigh_bst.m_root = nullptr;
        m_size = neigh_bst.m_size;
        neigh_bst.m_size = 0;
    }

    // move assignment
    new_bst& new_bst::operator=(new_bst&& neigh_bst){
        if (this == &neigh_bst) return *this;
        // clean tree
        clean_tree(m_root);
        m_root = nullptr;
        m_size = 0;
        // own the neigh tree
        m_root = neigh_bst.m_root;
        neigh_bst.m_root = nullptr;
        m_size = neigh_bst.m_size;
        neigh_bst.m_size = 0;
        return *this;
    }

    // destructor
    new_bst::~new_bst(){
        clean_tree(m_root);
        m_root = nullptr;
        m_size = 0;
    }

    // insert into tree
    void new_bst::insert(int val){
        TreeNode* temp = m_root;
        TreeNode* new_node = new TreeNode(val);
        while (temp != nullptr){
            int cur_val = temp->m_value;
            if (val >= cur_val){  
                if (temp->right == nullptr){
                    temp->right = new_node;
                    break;
                }  
                temp = temp->right;
            }
            else{
                if (temp->left == nullptr){
                    temp->left = new_node;
                    break;
                }
                temp = temp->left;
            }
        }
    }

    // find on the tree
    new_bst::TreeNode* new_bst::find(int val){
        TreeNode* temp = m_root;
        while (temp != nullptr){
            int cur_val = temp->m_value;
            if (cur_val == val) return temp;
            if (val > cur_val) temp = temp->right;
            else temp = temp->left;
        }
        return nullptr;
    }

    // find the smallest node to the right
    std::pair<new_bst::TreeNode*, new_bst::TreeNode*> new_bst::smallest(TreeNode* root){
        TreeNode* parent = nullptr;
        TreeNode* temp = root;
        while (temp->left != nullptr){
            parent = temp;
            temp = temp->left;
        }
        return {parent, temp};
    }

    // erase first node with value = val
    bool new_bst::erase(int val){
        TreeNode* del_node = m_root;
        TreeNode* parent = nullptr;
        while (del_node != nullptr){
            int cur_val = del_node->m_value;
            if (cur_val == val) break;
            parent = del_node;
            if (val > cur_val) del_node = del_node->right;
            else del_node = del_node->left;
        }
        if (del_node == nullptr) return false;
        // leaf node
        if (del_node->left == nullptr && del_node->right == nullptr){
            if (parent != nullptr){
                if (val >= parent->m_value) parent->right = nullptr;
                else parent->left = nullptr;
            }
            if (del_node == m_root) m_root = nullptr;
            delete del_node;
            m_size --;
        }
        // node with one child
        else if (del_node->left != nullptr && del_node->right == nullptr){
            if (parent != nullptr){
                if (val >= parent->m_value) parent->right = del_node->left;
                else parent->left = del_node->left;
            }
            if (del_node == m_root) m_root = del_node->left;
            delete del_node;
            m_size --;
        }
        else if (del_node->left == nullptr && del_node->right != nullptr){
            if (parent != nullptr){
                if (val >= parent->m_value) parent->right = del_node->right;
                else parent->left = del_node->right;
            }
            if (del_node == m_root) m_root = del_node->right;
            delete del_node;
            m_size --;
        }
        // node with two children
        else{
            std::pair<TreeNode*, TreeNode*> smallest_right_pair = smallest(del_node->right);
            TreeNode* smallest_right_parent = smallest_right_pair.first;
            TreeNode* smallest_right = smallest_right_pair.second;
            del_node->m_value = smallest_right->m_value;
            if (smallest_right_parent == nullptr){
                del_node->right = smallest_right->right;
            }
            else smallest_right_parent->left = smallest_right->right;
            delete smallest_right;
            m_size --;
        }
        return true;
    }
}

#endif