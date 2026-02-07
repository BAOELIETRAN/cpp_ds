// int --> template --> constexpr --> any further optimize

#ifndef TLINH_LINKED_LIST_H
#define TLINH_LINKED_LIST_H

#include <cstddef>
#include <stdexcept>

// singly linked list
namespace tlinh{
    // the class needs to represent a list (a container), not a node
    // --> declare a new type inside the class (Node)
    // since our linked list allocate memory dynamically --> need to write a destructor
    class my_linked_list{
        private:
            // define Node
            // access level - member function can still access to Node
            struct Node{
                int value{};
                Node* next{nullptr};
                // constructor - use default argument to reduce the amount of code
                // explicit - prevent implicit conversion (ex: from 10 --> my_linked_list(10))
                explicit Node(int val, Node* n = nullptr) : value{val}, next{n}{};
            };
            
            // header of the linked list
            Node* m_head{nullptr};
            Node* m_tail{nullptr};
            // size of the list = # of elements (size_t)
            std::size_t m_size{};
            // copy from another linked list
            void copy_from(const my_linked_list& other_list);

        public:
            /* constructors & destructors */
            // default constructor
            my_linked_list() = default;
            // copy constructor - for deep copy
            // access level --> my_linked_list() can access any private members of other_list
            my_linked_list(const my_linked_list& other_list);
            // operator overloading - allow deep copy 
            // return a reference to the current object
            my_linked_list& operator=(const my_linked_list& other_list);
            // destructor
            ~my_linked_list();

            /* member functions */
            // get value of a node at index
            int get(std::size_t index) const;
            
            // get node at index
            Node* get_node(std::size_t index) const;

            // get value of the first element
            int front() const;

            // get the value of the last element
            int back() const;

            // add a node at head
            void add_at_head(int val);

            // add a node at tail
            void add_at_tail(int val);

            // add a node at an index
            void add_at_index(std::size_t index, int val);

            // delete a node at head
            void delete_at_head();

            // delete a node at tail
            void delete_at_tail();

            // delete a node at index
            void delete_at_index(std::size_t index);

            // return the current size (# of elements)
            std::size_t get_size() const {return m_size;};

            // check whether the list is empty
            bool is_empty() const {return m_size == 0;};

            // clear the linked list
            void clear();
    };
}

#endif

