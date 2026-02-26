#include "doubly_linked_list.h"

namespace ccmk{
    /* constructors & assignments*/
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
        // --> we should use std::make_unique<>() as memory allocation + ownership transfer all happen in 1 function
        while (other_temp != other_dummy_tail){
            // TODO
            cur_temp->next = std::make_unique<Node>(other_temp->val);
            Node* raw_next_node = cur_temp->next.get();
            raw_next_node->prev = cur_temp;
            cur_temp = raw_next_node;
            other_temp = other_temp->next.get();
        }
        // TODO
        cur_temp->next = std::make_unique<Node>();
        dummy_tail = cur_temp->next.get();
        dummy_tail->prev = cur_temp;
        m_size = other_list.m_size;
    }

    // copy assignment - deep copy
    doubly_linked_list& doubly_linked_list::operator=(const doubly_linked_list& other_list){
        // self assignment check
        if (this == &other_list){
            return *this;
        }
        // delete any current data
        dummy_head->next = std::make_unique<Node>();
        dummy_tail = dummy_head->next.get();
        dummy_tail->prev = dummy_head.get();
        m_size = 0;
        // TODO
        // assign new data
        Node* other_temp = other_list.dummy_head->next.get();
        Node* other_temp_tail = other_list.dummy_tail;
        Node* cur_temp = dummy_head.get();
        while (other_temp != other_temp_tail){
            cur_temp->next = std::make_unique<Node>(other_temp->val);
            Node* raw_next_node = cur_temp->next.get();
            raw_next_node->prev = cur_temp;
            cur_temp = raw_next_node;
            other_temp = other_temp->next.get();
        }
        // TODO
        cur_temp->next = std::make_unique<Node>();
        dummy_tail = cur_temp->next.get();
        dummy_tail->prev = cur_temp;
        m_size = other_list.m_size;
        return *this;
    }

    // move constructor
    // when we move other_list to current list --> resource will not be deleted
    // --> dummy head in other list will be nullptr (not holding anything), but other data stays the same
    doubly_linked_list::doubly_linked_list(doubly_linked_list&& other_list) 
    : dummy_head{std::move(other_list.dummy_head)}, dummy_tail{other_list.dummy_tail}, m_size{other_list.m_size}{
        // after done moving, we need to set other list back to valid state (as others still assume other list is valid)
        // valid state: dummy_head <--> dummy_tail
        other_list.dummy_head = std::make_unique<Node>();
        other_list.dummy_head->next = std::make_unique<Node>();
        other_list.dummy_tail = other_list.dummy_head->next.get();
        other_list.dummy_tail->prev = other_list.dummy_head.get();
        other_list.m_size = 0;
    }

    // move assignment
    doubly_linked_list& doubly_linked_list::operator=(doubly_linked_list&& other_list){
        // self assignment check
        if (this == &other_list){
            return *this;
        }
        // clean up old data
        dummy_head->next = std::make_unique<Node>();
        dummy_tail = dummy_head->next.get();
        dummy_tail->prev = dummy_head.get();
        m_size = 0;
        // do the move
        // after the move, dummy_head == nullptr
        dummy_head = std::move(other_list.dummy_head);
        dummy_tail = other_list.dummy_tail;
        m_size = other_list.m_size;
        // convert other_list back to valid state: dummy_head <--> dummy_tail
        other_list.dummy_head = std::make_unique<Node>();
        other_list.dummy_head->next = std::make_unique<Node>();
        other_list.dummy_tail = other_list.dummy_head->next.get();
        other_list.dummy_tail->prev = other_list.dummy_head.get();
        other_list.m_size = 0;
        return *this;
    }

    /* member functions */
    // get value of node at index
    int doubly_linked_list::get(std::size_t index) const{
        // std::size_t is unsigned --> don't need to check < 0
        if (index >= m_size){
            throw std::out_of_range("The index is out of bound!");
        }
        Node* temp = dummy_head->next.get();
        for (int i = 0; i < index; i ++){
            temp = temp->next.get();
        }
        return temp->val;
    }

    // get Node at index
    doubly_linked_list::Node* doubly_linked_list::get_node(std::size_t index) const{
        // std::size_t is unsigned --> don't need to check < 0
        if (index >= m_size){
            throw std::out_of_range("The index is out of bound!");
        }
        Node* temp = dummy_head->next.get();
        for (int i = 0; i < index; i ++){
            temp = temp->next.get();
        }
        return temp;
    }

    // get value of the first element
    int doubly_linked_list::front() const{
        if (m_size == 0){
            throw std::out_of_range("The list is empty!");
        }   
        return dummy_head->next->val;
    }

    // get value of the last element
    int doubly_linked_list::back() const{
        if (m_size == 0){
            throw std::out_of_range("The list is empty!");
        }
        return dummy_tail->prev->val;
    }

    // add a node at head
    void doubly_linked_list::add_at_head(int val){
        // move the ownership of the rest of the list
        // TODO
        auto temp_owner = std::move(dummy_head->next);
        dummy_head->next = std::make_unique<Node>(val);
        Node* temp_next = dummy_head->next.get();
        temp_next->prev = dummy_head.get();
        Node* raw_temp_owner = temp_owner.get();
        raw_temp_owner->prev = temp_next;
        temp_next->next = std::move(temp_owner);
        m_size ++;
    }

    // add a node at tail
    void doubly_linked_list::add_at_tail(int val){
        // move the last node from owning dummy tail to owning new node
        auto new_node_ptr = std::make_unique<Node>(val);
        Node* raw_last_node = dummy_tail->prev;
        new_node_ptr->prev = raw_last_node;
        dummy_tail->prev = new_node_ptr.get();
        new_node_ptr->next = std::move(raw_last_node->next);
        raw_last_node->next = std::move(new_node_ptr);
        m_size ++;
    }

    // add a node at index
    void doubly_linked_list::add_at_index(std::size_t index, int val){
        if (index > m_size){
            throw std::out_of_range("The index is out of bound!");
        }
        else if (index == m_size){
            add_at_tail(val);
        }
        else if (index == 0){
            add_at_head(val);
        }
        else{
            Node* raw_next_node = get_node(index);
            Node* raw_prev_node = raw_next_node->prev;
            auto new_node = std::make_unique<Node>(val);
            new_node->prev = raw_prev_node;
            raw_next_node->prev = new_node.get();
            new_node->next = std::move(raw_prev_node->next);
            raw_prev_node->next = std::move(new_node);
            m_size ++;
        }
    }

    // delete the first node
    void doubly_linked_list::delete_at_head(){
        if (m_size == 0){
            throw std::out_of_range("The list is empty!");
        }
        Node* raw_next_node = dummy_head->next->next.get();
        raw_next_node->prev = dummy_head.get();
        dummy_head->next = std::move(dummy_head->next->next);
        m_size --;
    }
}