// int --> template --> constexpr --> any further optimize

#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

// singly linked list
namespace tlinh{
    class my_linked_list{
        private:
            int m_value{};
            my_linked_list* m_next{};
        public:
            /* constructors & destructors */
            // request compiler to give a default constructor --> put in header file
            my_linked_list() = default;
            // explicit - prevent implicit conversion (ex: from 10 --> my_linked_list(10))
            explicit my_linked_list(int value);
            my_linked_list(int value, my_linked_list* next);
            my_linked_list(const my_linked_list* const linked_list);
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
    };
}

#endif

