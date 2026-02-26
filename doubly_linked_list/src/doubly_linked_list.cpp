#include "doubly_linked_list.h"

namespace ccmk{
    // default constructor
    doubly_linked_list::doubly_linked_list(){
        // should use std::make_unique --> safer & cleaner
        dummy_head = std::make_unique<Node>();
        dummy_head->next = std::make_unique<Node>();
        dummy_tail = dummy_head->next.get();
        dummy_tail->prev = dummy_head.get();
        m_size = 0;
    }

    // copy constructor - deep copy
    // using delegate constructor here to initialize dummy_head and dummy_tail
    doubly_linked_list::doubly_linked_list(const doubly_linked_list& other_list) : doubly_linked_list(){
        // for viewing, just use raw pointer (as unique_pointer is move only)
        Node* other_temp = other_list.dummy_head->next.get();
        Node* other_dummy_tail = other_list.dummy_tail;
        Node* cur_temp = dummy_head.get();
        while (other_temp != other_dummy_tail){
            // TODO
        }
        // TODO
    }

    // copy assignment - deep copy
    doubly_linked_list& doubly_linked_list::operator=(const doubly_linked_list& other_list){
        // self assignment check
        if (this == &other_list){
            return *this;
        }
        // delete any current data
        // TODO
        // assign new data
        // TODO
        return *this;
    }
}