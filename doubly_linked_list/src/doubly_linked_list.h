#ifndef CCMK_DOUBLY_LINKED_LIST_H
#define CCMK_DOUBLY_LINKED_LIST_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>

/*
    for this linked list, we use "smart" unique_ptr to delete the whole list
    gracefully (like a domino) when our class goes out of bound.
    if we want to access node --> use raw pointer.
    to get raw address of a block of memory that is owned by an unique_ptr ptr, 
    use ptr.get().
*/
namespace ccmk{
    class doubly_linked_list{
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
            doubly_linked_list() = default;
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