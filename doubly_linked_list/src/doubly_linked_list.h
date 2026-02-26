#ifndef CCMK_DOUBLY_LINKED_LIST_H
#define CCMK_DOUBLY_LINKED_LIST_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <iterator>

/*
    For this linked list, we use "smart" unique_ptr to delete the whole list
    gracefully (like a domino) when our class goes out of bound.

    If we want to access node --> use raw pointer.

    To get raw address of a block of memory that is owned by an unique_ptr ptr, 
    use ptr.get().

    If an unique pointer owns another memory block, current memory block will
    be immediately deleted.

    Smart pointer has a raw pointer inside --> can only manage heap memory.
    --> can not use stack memory for smart pointer.

    Smart pointer only manages lifetime & ownership of a heap memory object
    --> it does not manage data of that object
    --> we can freely modify the object's data (ex: using another raw pointer)
*/
namespace ccmk{
    class doubly_linked_list{
        /*
            just declare stuff in private sector,
            any real work (assigning, creating, ...) --> do them in constructors
        */
        private:
            struct Node{
                int val{};
                // cur node owns the next node --> the head will own the whole list
                // if we assign the unique_ptr to own another node instead of current node
                // --> current node will be immediately deleted
                std::unique_ptr<Node> next{};
                Node* prev{};
                // default constructor - avoid implicit conversion
                explicit Node() = default;
                // direct constructor
                Node(int value) : val{value}{};
                // copy constructor = delete - avoid making copies of node
                Node(const Node& other_node) = delete;
                // copy assignment - avoid making copies of node
                Node& operator=(const Node& other_node) = delete;
                // move constructor 
                Node(Node&& other_node) noexcept = delete;
                // move assignment
                Node& operator=(Node&& other_node) noexcept = delete;
            };
            // domino --> once the dummy head dies --> the whole list dies
            std::unique_ptr<Node> dummy_head{};
            // can not make the dummy tail unique pointer as it will make 2 pointers own a block of memory
            Node* dummy_tail{};
            std::size_t m_size{};
        public:
            /* constructors & destructors*/
            // default constructor of doubly linked list
            doubly_linked_list();
            // copy constructor -- deep copy
            doubly_linked_list(const doubly_linked_list& other_list);
            // copy assignment -- deep copy
            doubly_linked_list& operator=(const doubly_linked_list& other_list);
            // move constructor 
            doubly_linked_list(doubly_linked_list&& other_list) noexcept;
            // move assignment
            doubly_linked_list& operator=(doubly_linked_list&& other_list) noexcept;
            // destructor
            ~doubly_linked_list() = default;

            /* member functions*/
            // TODO: iterator
            class iterator{
                private:
                    // private member
                    Node* m_ptr{};
                public:
                    // declare properties of iterator -- C++ expects this --> make them public
                    using iterator_category = std::bidirectional_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = int;
                    using pointer = int*;
                    using reference = int&;

                    // constructor
                    iterator() = default;
                    explicit iterator(Node* ptr) : m_ptr{ptr}{};
                    // using default destructor as custom destructor will delete data when iterator dies --> not good

                    // member functions
                    // should not expose Node pointer --> others can modify the list
                    pointer operator->() const { return &(m_ptr->val); };
                    reference operator*() const { return m_ptr->val; };

                    // increment
                    // prefix increment
                    iterator& operator++(){
                        // TODO
                        // the iterator up and return the current spot
                        m_ptr = m_ptr->next.get();
                        return *this;
                    }
                    // postfix increment
                    iterator operator++(int){
                        // TODO
                        // make a copy, move the iterator up, and return the copy
                        auto temp = *this;
                        // use prefix increment on current iterator
                        ++(*this);
                        return temp;
                    }
                    // decrement
                    // prefix decrement
                    iterator& operator--(){
                        // TODO
                        m_ptr = m_ptr->prev;
                        return *this;
                    }
                    // postfix decrement
                    iterator operator--(int){
                        // TODO
                        auto temp = *this;
                        // use prefix decrement on current iterator
                        --(*this);
                        return temp;
                    }
                    // compare iterators
                    bool operator==(const iterator& other_iter) const{ 
                        if (m_ptr == other_iter.m_ptr){
                            return true;
                        }
                        return false;
                    }
                    bool operator!=(const iterator& other_iter) const{
                        if (m_ptr != other_iter.m_ptr){
                            return true;
                        }
                        return false;
                    }
            };
            // get iterators and begin() and end()
            iterator begin(){
                iterator begin_iter((dummy_head->next).get());
                return begin_iter;
            }
            // end() should be one past the last element
            iterator end(){
                iterator end_iter(dummy_tail);
                return end_iter;
            }
            // get value of a node at index
            int get(std::size_t index) const;
            // get a node at index
            Node* get_node(std::size_t index) const;
            // get value of the first element
            int front() const;
            // get vaue of the last element
            int back() const;
            // add a node at head
            void add_at_head(int val);
            // add a node at tail
            void add_at_tail(int val);
            // add at index
            void add_at_index(std::size_t index, int val);
            // delete a specific node
            void delete_node(Node* node);
            // delete a node at head
            void delete_at_head();
            // delete a node at tail
            void delete_at_tail();
            // delete a node at index
            void delete_at_index(std::size_t index);
            // get size of the list
            std::size_t get_size() const { return m_size; };
            // check whether the list is empty or not
            bool is_empty() const { return m_size == 0; };
            // clear the linked list
            void clear();
    };
}

#endif