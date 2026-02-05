// int --> template --> constexpr --> any further optimize

#ifndef TLINH_LINKED_LIST_H
#define TLINH_LINKED_LIST_H

#include <cstddef>

// singly linked list
namespace tlinh{
    // the class needs to represent a list (a container), not a node
    // --> declare a new type inside the class (Node)
    // since our linked list allocate memory dynamically --> need to write a destructor
    class my_linked_list{
        private:
            // define Node
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

        public:
            /* constructors & destructors */
            // default constructor
            my_linked_list() = default;
            // copy constructor - for deep copy
            my_linked_list(const my_linked_list& list);
            // operator overloading - allow deep copy 
            // return a reference to the current object
            my_linked_list& operator=(const my_linked_list& other_list);
            // destructor
            ~my_linked_list();

            /* member functions */
            // get a node at index
            int get(int index) const;

            // add a node at head
            void add_at_head(int val);

            // add a node at tail
            void add_at_tail(int val);

            // add a node at an index
            void add_at_index(int val, int index);

            // delete a node at index
            void delete_at_index(int index);

            // return the current size (# of elements)
            std::size_t get_size() const {return m_size;};

            // check whether the list is empty
            bool is_empty() const {return m_size == 0;};

            // clear the linked list
            void clear();
    };
}

#endif

