#ifndef NEW_DOUBLY_LINKED_LIST
#define NEW_DOUBLY_LINKED_LIST

#include <iostream>
#include <cstddef>
#include <utility>

namespace tehran{
    template <typename T>
    class new_list{
        private:
            struct Node{
                T value{};
                Node* next{};
                Node* prev{};
                Node(){};
                Node(T val) : value{std::move(val)}{};
            };
            Node* m_head{};
            Node* m_tail{};
            std::size_t m_size{};
        public:
            /* constructors */
            // default constructor
            explicit new_list();
            // copy constructor
            explicit new_list(const new_list& neigh_list);
            // copy assignment
            new_list& operator=(const new_list& neigh_list);
            // move constructor
            explicit new_list(new_list&& neigh_list);
            // move assignment
            new_list& operator=(new_list&& neigh_list);
            // destructor
            ~new_list();

            /* iterator */
            class iterator{
                private:
                    Node* m_node{};
                public:
                    explicit iterator(Node* node);
                    T& operator*();
                    T* operator->();
                    iterator& operator++();
                    iterator operator++(int);
                    iterator& operator--();
                    iterator operator--(int);
                    bool operator==(const iterator& other_it) const;
                    bool operator!=(const iterator& other_it) const;
            };

            /* member functions */
            iterator begin();
            iterator end();
            void push_back(const T& value);
            void push_back(T&& value);
            void push_front(const T& value);
            void push_front(T&& value);
            void pop_back();
            void pop_front();
            T& front();
            T& back();
            std::size_t size() const;
            bool empty() const;
            void clear();
    };

    // default constructor
    template <typename T>
    new_list<T>::new_list(){
        m_head = new Node();
        m_tail = new Node();
        m_head->next = m_tail;
        m_tail->prev = m_head;
        m_size = 0;
    }

    // copy constructor
    template <typename T>
    new_list<T>::new_list(const new_list& neigh_list) : new_list<T>::new_list(){
        Node* neigh_head = neigh_list.m_head;
        Node* neigh_tail = neigh_list.m_tail;
        Node* cur_temp = m_head;
        Node* neigh_temp = neigh_head->next;
        while (neigh_temp != neigh_tail){
            Node* new_node = new Node(neigh_temp->value);
            cur_temp->next = new_node;
            new_node->next = m_tail;
            new_node->prev = cur_temp;
            m_tail->prev = new_node;
            m_size ++;
            neigh_temp = neigh_temp->next;
            cur_temp = cur_temp->next;
        }
    }

    // copy assignment
    template <typename T>
    new_list<T>& new_list<T>::operator=(const new_list& neigh_list){
        if (this == &neigh_list) return *this;
        // clear the cur list
        Node* del_temp = m_head->next;
        while (m_size > 0){
            Node* next_node = del_temp->next;
            delete del_temp;
            del_temp = next_node;
            m_size --;
        }
        delete m_head;
        delete m_tail;
        // assign the cur list
        Node* neigh_head = neigh_list.m_head;
        Node* neigh_tail = neigh_list.m_tail;
        Node* cur_temp = m_head;
        Node* neigh_temp = neigh_head->next;
        while (neigh_temp != neigh_tail){
            Node* new_node = new Node(neigh_temp->value);
            cur_temp->next = new_node;
            new_node->next = m_tail;
            new_node->prev = cur_temp;
            m_tail->prev = new_node;
            m_size ++;
            neigh_temp = neigh_temp->next;
            cur_temp = cur_temp->next;
        }
        return *this;
    }

    // move constructor
    template <typename T>
    new_list<T>::new_list(new_list&& neigh_list){
        m_head = neigh_list.m_head;
        m_tail = neigh_list.m_tail;
        m_size = neigh_list.m_size;
        neigh_list.m_head = new Node();
        neigh_list.m_tail = new Node();
        neigh_list.m_head->next = neigh_list.m_tail;
        neigh_list.m_tail->prev = neigh_list.m_head;
        neigh_list.m_size = 0;
    }

    // move assignment 
    template <typename T>
    new_list<T>& new_list<T>::operator=(new_list&& neigh_list){
        if (this == &neigh_list) return *this;
        // clear the cur list
        Node* del_temp = m_head->next;
        while (m_size > 0){
            Node* next_node = del_temp->next;
            delete del_temp;
            del_temp = next_node;
            m_size --;
        }
        delete m_head;
        delete m_tail;
        // own the new list
        m_head = neigh_list.m_head;
        m_tail = neigh_list.m_tail;
        m_size = neigh_list.m_size;
        neigh_list.m_head = new Node();
        neigh_list.m_tail = new Node();
        neigh_list.m_head->next = neigh_list.m_tail;
        neigh_list.m_tail->prev = neigh_list.m_head;
        neigh_list.m_size = 0;
        return *this;
    }

    // destructor
    template <typename T>
    new_list<T>::~new_list(){
        Node* temp = m_head->next;
        while (temp != m_tail){
            Node* next_node = temp->next;
            delete temp;
            temp = next_node;
        }
        delete m_head;
        delete m_tail;
        m_size = 0;
    }

    // push back
    template <typename T>
    void new_list<T>::push_back(const T& value){
        Node* new_node = new Node(value);
        Node* prev_node = m_tail->prev;
        prev_node->next = new_node;
        new_node->next = m_tail;
        new_node->prev = prev_node;
        m_tail->prev = new_node;
        m_size ++;
    }

    template <typename T>
    void new_list<T>::push_back(T&& value){
        Node* new_node = new Node(std::move(value));
        Node* prev_node = m_tail->prev;
        prev_node->next = new_node;
        new_node->next = m_tail;
        new_node->prev = prev_node;
        m_tail->prev = new_node;
        m_size ++;
    }

    template <typename T>
    void new_list<T>::push_front(const T& value){
        Node* new_node = new Node(value);
        Node* next_node = m_head->next;
        m_head->next = new_node;
        new_node->next = next_node;
        new_node->prev = m_head;
        next_node->prev = new_node;
        m_size ++;
    }

    template <typename T>
    void new_list<T>::push_front(T&& value){
        Node* new_node = new Node(std::move(value));
        Node* next_node = m_head->next;
        m_head->next = new_node;
        new_node->next = next_node;
        new_node->prev = m_head;
        next_node->prev = new_node;
        m_size ++;
    }

    template <typename T>
    void new_list<T>::pop_back(){
        if (m_size == 0) return;
        Node* del_node = m_tail->prev;
        Node* prev_node = del_node->prev;
        prev_node->next = m_tail;
        m_tail->prev = prev_node;
        delete del_node;
        m_size --;
    }

    template <typename T>
    void new_list<T>::pop_front(){
        if (m_size == 0) return;
        Node* del_node = m_head->next;
        Node* next_node = del_node->next;
        m_head->next = next_node;
        next_node->prev = m_head;
        delete del_node;
        m_size --;
    }

    template <typename T>
    T& new_list<T>::front(){
        return m_head->next->value;
    }

    template <typename T>
    T& new_list<T>::back(){
        return m_tail->prev->value;
    }

    template <typename T>
    std::size_t new_list<T>::size() const{
        return m_size;
    }

    template <typename T>
    bool new_list<T>::empty() const{
        return m_size == 0;
    }

    template <typename T>
    void new_list<T>::clear(){
        Node* temp = m_head->next;
        while (temp != m_tail){
            Node* next_node = temp->next;
            delete temp;
            temp = next_node;
        }
        m_head->next = m_tail;
        m_tail->prev = m_head;
        m_size = 0;
    }

    // iterator constructor
    template <typename T>
    new_list<T>::iterator::iterator(new_list<T>::Node* node) : m_node{node}{};

    // dereference
    template <typename T>
    T& new_list<T>::iterator::operator*(){
        return m_node->value;
    }

    // return pointer
    template <typename T>
    T* new_list<T>::iterator::operator->(){
        return &m_node->value;
    }

    // prefix increment
    template <typename T>
    new_list<T>::iterator& new_list<T>::iterator::operator++(){
        m_node = m_node->next;
        return *this;
    }

    // postfix increment
    template <typename T>
    new_list<T>::iterator new_list<T>::iterator::operator++(int){
        iterator cur_it{m_node};
        m_node = m_node->next;
        return cur_it;
    }

    // prefix decrement
    template <typename T>
    new_list<T>::iterator& new_list<T>::iterator::operator--(){
        m_node = m_node->prev;
        return *this;
    }

    // postfix decrement
    template <typename T>
    new_list<T>::iterator new_list<T>::iterator::operator--(int){
        iterator cur_it{m_node};
        m_node = m_node->prev;
        return cur_it;
    }

    // equal
    template <typename T>
    bool new_list<T>::iterator::operator==(const new_list<T>::iterator& other_it) const{
        return m_node == other_it.m_node;
    }

    // different
    template <typename T>
    bool new_list<T>::iterator::operator!=(const new_list<T>::iterator& other_it) const{
        return m_node != other_it.m_node;
    }

    // return begin of the list
    template <typename T>
    new_list<T>::iterator new_list<T>::begin(){
        return iterator(m_head->next);
    }

    // return end point of the list
    template <typename T>
    new_list<T>::iterator new_list<T>::end(){
        return iterator(m_tail);
    }
}

#endif