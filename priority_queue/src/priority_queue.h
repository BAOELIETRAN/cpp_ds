#ifndef GIO_PRIORITY_QUEUE_H
#define GIO_PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept>

// add on: use move semantics (constructors + assignment) and smart pointer in this ds
namespace gio{
    class priority_queue{
        private:
            struct comparator{
                bool operator()(const int& a, const int& b) const{
                    // sort in ascending order
                    return a < b;
                }
            };
            // initialize a comparator object
            comparator m_comp{};
            std::vector<int> m_container{};
            std::size_t m_size{};
            // constructor must have a comparator as an input
            /* helper methods */
            // move a node up to ensure heap priority
            void heapify_up(int index);
            // move a node down to ensure heap priority
            void heapify_down(int index);
            // return parent index of current node at index
            int get_parent(int index) const;
            // return left child of current node at index
            int get_left_child(int index) const;
            // return right child of current node at index
        public:
            /* constructors & destructors */
            priority_queue() = default;
            priority_queue(const priority_queue& other_queue) = default;
            priority_queue& operator=(const priority_queue& other_queue) = default;
            ~priority_queue() = default;

            /* member functions */
            // return the top element --- O(1)
            int top() const;
            // check if the queue is empty --- O(1)
            bool empty() const;
            // get size of the queue --- O(1)
            int size() const;
            // push an element to queue --- O(logN)
            void push(int val); 
            // pop the top --- O(logN)
            void pop();
    };
}

#endif