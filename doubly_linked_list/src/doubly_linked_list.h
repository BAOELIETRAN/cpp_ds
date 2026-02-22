#ifndef CCMK_DOUBLY_LINKED_LIST_H
#define CCMK_DOUBLY_LINKED_LIST_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>

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
                // TODO
                // move assignment
                // TODO
            };
            // TODO
        public:
    };
}

#endif