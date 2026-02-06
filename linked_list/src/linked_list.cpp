#include "linked_list.h"

namespace tlinh{
    // copy from
    void my_linked_list::copy_from(const my_linked_list& other_list){
        Node* other_temp = other_list.m_head;
        if (other_temp != nullptr){
            Node* dummy_node = new Node(0);
            Node* temp = dummy_node;
            while (other_temp != nullptr){
                Node* new_node = new Node(other_temp->value);
                if (other_temp == other_list.m_tail){
                    m_tail = new_node;
                }
                temp->next = new_node;
                temp = temp->next;
                other_temp = other_temp->next;
            }
            m_head = dummy_node->next;
            delete dummy_node;
        }
    }

    // copy constructor
    my_linked_list::my_linked_list(const my_linked_list& other_list) : m_head{nullptr}, m_tail{nullptr}, m_size{0}{
        if (this != &other_list){
            // copying
            copy_from(other_list);
        }
    }

    // operator overloading
    my_linked_list& my_linked_list::operator=(const my_linked_list& other_list){
        if (this == &other_list){
            return *this;
        }
        // clear the old node before copying
        clear();
        // copying
        copy_from(other_list);
        // in all member functions, there is always a pointer to the current class (this)
        // since "this" is a pointer --> "*this" is the object itself
        return *this;
    }

    // destructor
    // when an object is destroyed, m_head, m_tail, and m_size will no longer exist
    // --> no need to reset them
    my_linked_list::~my_linked_list(){
        while (m_head != nullptr){
            Node* next_node = m_head->next;
            delete m_head;
            m_head = next_node;
        }
    }

    // get value of a node at index
    int my_linked_list::get(int index) const{
        if (index < 0 || index >= m_size){
            throw std::out_of_range("The index is out of range!");
        }
        Node* temp = m_head;
        while (index > 0){
            temp = temp->next;
            index --;
        }
        return temp->value;
    }

    // get node at index
    my_linked_list::Node* my_linked_list::get_node(int index) const{
        if (index < 0 || index >= m_size){
            throw std::out_of_range("The index is out of range!");
        }
        Node* temp = m_head;
        while (index > 0){
            temp = temp->next;
            index --;
        }
        return temp;
    }

    // add a node at head of the linked list
    void my_linked_list::add_at_head(int val){
        Node* new_node = new Node(val);
        if (m_head == nullptr){
            m_head = new_node;
            m_tail = new_node;
            m_size ++;
            return;
        }
        new_node->next = m_head;
        m_head = new_node;
        m_size ++;
    }

    // add a node at tail of the linked list
    void my_linked_list::add_at_tail(int val){
        Node* new_node = new Node(val);
        if (m_head == nullptr){
            m_head = new_node;
            m_tail = new_node;
            m_size ++;
            return;
        }
        m_tail->next = new_node;
        m_tail = new_node;
        m_size ++;
    }

    // add a node at index
    void my_linked_list::add_at_index(int index, int val){
        if (index < 0 || index >= m_size){
            throw std::out_of_range("The index is out of range");
        }
        if (index == 0){
            add_at_head(val);
            return;
        }
        if (index == m_size - 1){
            add_at_tail(val);
            return;
        }   
        Node* new_node = new Node(val);
        Node* prev_node = get_node(index - 1);
        Node* next_node = get_node(index + 1);
        prev_node->next = new_node;
        new_node->next = next_node;
        m_size ++;
    }

    // delete a node at head
    void my_linked_list::delete_at_head(){
        if (m_head == nullptr){
            return;
        }
        Node* next_node = m_head->next;
        delete m_head;
        m_head = next_node;
        m_size --;
        if (m_head == nullptr){
            m_tail = nullptr;
        }
    }

    // delete a node at tail
    void my_linked_list::delete_at_tail(){
        if (m_head == nullptr){
            return;
        }
        Node* prev_node = get_node(m_size - 1);
        delete m_tail;
        m_tail = prev_node;
        m_size --;
        if (m_tail == nullptr){
            m_head = nullptr;
            return;
        }
        m_tail->next = nullptr;
    }
}