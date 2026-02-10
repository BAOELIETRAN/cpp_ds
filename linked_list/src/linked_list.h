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
    template<typename T>
    class my_linked_list{
        private:
            // define Node
            // access level - member function can still access to Node
            struct Node{
                T value{};
                Node* next{nullptr};
                // constructor - use default argument to reduce the amount of code
                // explicit - prevent implicit conversion (ex: from 10 --> my_linked_list(10))
                explicit Node(const T& val, Node* n = nullptr) : value{val}, next{n}{};
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
            // copy assignment
            my_linked_list& operator=(const my_linked_list& other_list);
            // destructor
            ~my_linked_list();

            /* member functions */
            // get value of a node at index
            T get(std::size_t index) const;
            
            // get node at index
            Node* get_node(std::size_t index) const;

            // get value of the first element
            T front() const;

            // get the value of the last element
            T back() const;

            // add a node at head
            void add_at_head(const T& val);

            // add a node at tail
            void add_at_tail(const T& val);

            // add a node at an index
            void add_at_index(std::size_t index, const T& val);

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

    // define functions here
    // we can implement the defintion of member function outside of class defintion
    // as long as we provide the location of that function (namespace::class::...)
    template<typename T>
    void my_linked_list<T>::copy_from(const my_linked_list<T>& other_list){
        Node* other_temp = other_list.m_head;
        if (other_temp != nullptr){
            Node* dummy_node = new Node(T());
            Node* temp = dummy_node;
            while (other_temp != nullptr){
                Node* new_node = new Node(other_temp->value);
                if (other_temp == other_list.m_tail){
                    m_tail = new_node;
                }
                temp->next = new_node;
                temp = temp->next;
                m_size ++;
                other_temp = other_temp->next;
            }
            m_head = dummy_node->next;
            delete dummy_node;
        }
    }

    template<typename T>
    my_linked_list<T>::my_linked_list(const my_linked_list<T>& other_list) : m_head{nullptr}, m_tail{nullptr}, m_size{0}{
        // copying
        copy_from(other_list);
    }

    template<typename T>
    my_linked_list<T>& my_linked_list<T>::operator=(const my_linked_list<T>& other_list){
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

    template<typename T>
    my_linked_list<T>::~my_linked_list(){
        while (m_head != nullptr){
            Node* next_node = m_head->next;
            delete m_head;
            m_head = next_node;
        }
    }

    template<typename T>
    T my_linked_list<T>::get(std::size_t index) const{
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

    template<typename T>
    my_linked_list<T>::Node* my_linked_list<T>::get_node(std::size_t index) const{
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

    template<typename T>
    void my_linked_list<T>::add_at_head(const T& val){
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

    template<typename T>
    void my_linked_list<T>::add_at_tail(const T& val){
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

    template<typename T>
    void my_linked_list<T>::add_at_index(std::size_t index, const T& val){
        if (index < 0 || index > m_size){
            throw std::out_of_range("The index is out of range");
        }
        if (index == 0){
            add_at_head(val);
            return;
        }
        if (index == m_size){
            add_at_tail(val);
            return;
        }   
        Node* new_node = new Node(val);
        Node* prev_node = get_node(index - 1);
        Node* curr_node = prev_node->next;
        prev_node->next = new_node;
        new_node->next = curr_node;
        m_size ++;
    }

    template<typename T>
    void my_linked_list<T>::delete_at_head(){
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

    template<typename T>
    void my_linked_list<T>::delete_at_tail(){
        if (m_head == nullptr){
            return;
        }
        if (m_size == 1){
            delete_at_head();
            return;
        }
        Node* prev_node = get_node(m_size - 2);
        delete m_tail;
        m_tail = prev_node;
        m_size --;
        m_tail->next = nullptr;
    }

    template<typename T>
    void my_linked_list<T>::delete_at_index(std::size_t index){
        if (index < 0 || index >= m_size){
            throw std::out_of_range("the index is out of range");
        }
        if (index == 0){
            delete_at_head();
            return;
        }
        if (index == m_size - 1){
            delete_at_tail();
            return;
        }
        Node* prev_node = get_node(index - 1);
        Node* curr_node = get_node(index);
        Node* next_node = curr_node->next;
        prev_node->next = next_node;
        delete curr_node;
        m_size --;
    }

    template<typename T>
    void my_linked_list<T>::clear(){
        if (m_head == nullptr){
            return;
        }
        Node* temp = m_head;
        while (temp != nullptr){
            Node* next_node = temp->next;
            delete temp;
            temp = next_node;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    template<typename T>
    T my_linked_list<T>::front() const{
        if (m_head == nullptr){
            throw std::out_of_range("The list is empty!");
        }
        return m_head->value;
    }

    template<typename T>
    T my_linked_list<T>::back() const{
        if (m_head == nullptr){
            throw std::out_of_range("The list is empty!");
        }
        return m_tail->value;
    }
}

#endif

