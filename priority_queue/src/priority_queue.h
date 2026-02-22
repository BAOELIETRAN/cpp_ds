#ifndef GIO_PRIORITY_QUEUE_H
#define GIO_PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <functional>

// add on: function pointer for comparator?
namespace gio{
    template<typename T>
    struct less{
        bool operator()(const T& a, const T& b) const{
            // sort in ascending order
            return a < b;
        }        
    };
    template<typename T, typename comparator = less<T>>
    class priority_queue{
        private:
            // initialize a comparator object
            comparator m_comp{};
            std::vector<T> m_container{};
            std::size_t m_size{};
            // constructor must have a comparator as an input
            /* helper methods */
            // move a node up to ensure heap priority
            void heapify_up(int index);
            // move a node down to ensure heap priority
            void heapify_down(int index);
            // return parent index of current node at index
            int get_parent(int index) const;
            // return index of left child of current node at index
            int get_left_child(int index) const;
            // return index of right child of current node at index
            int get_right_child(int index) const;
        public:
            /* constructors & destructors */
            priority_queue() = default;
            // constructor with comp initialization
            // direct initialization
            priority_queue(comparator comp) : m_comp{comp}{};
            // default copy constructor
            priority_queue(const priority_queue& other_queue) = default;
            // default move constructor
            priority_queue(priority_queue&& other_queue) = default;
            // default copy assignment
            priority_queue& operator=(const priority_queue& other_queue) = default;
            // default move assignment
            priority_queue& operator=(priority_queue&& other_queue) = default;
            ~priority_queue() = default;

            /* member functions */
            // return the top element --- O(1)
            T top() const;
            // check if the queue is empty --- O(1)
            bool empty() const;
            // get size of the queue --- O(1)
            int size() const;
            // push an element to queue --- O(logN)
            void push(T val); 
            // pop the top --- O(logN)
            void pop();
    };

    // O(1)
    template<typename T, typename comparator> 
    int priority_queue<T, comparator>::get_parent(int index) const{
        if (index < 0 || index >= m_size){
            // program will terminate since no catch block is found in call stack
            throw std::out_of_range("The index is invalid!");
        }
        return (index - 1)/2;
    }

    // O(logN)
    template<typename T, typename comparator> 
    void priority_queue<T, comparator>::heapify_up(int index){
        while (index > 0){
            int parent_index = get_parent(index);
            if (m_comp(m_container[parent_index], m_container[index]) == false){
                std::swap(m_container[parent_index], m_container[index]);
                index = parent_index;
            }
            else{
                break;
            }
        }
    }

    // O(1)
    template<typename T, typename comparator> 
    int priority_queue<T, comparator>::get_left_child(int index) const{
        if (index < 0 || index >= m_size){
            throw std::out_of_range("The index is invalid!");
        }
        int left_child_index = 2 * index + 1;
        return (left_child_index >= m_size)? -1 : left_child_index;
    }

    // O(1)
    template<typename T, typename comparator>
    int priority_queue<T, comparator>::get_right_child(int index) const{
        if (index < 0 || index >= m_size){
            throw std::out_of_range("The index is invalid!");
        }
        int right_child_index = 2 * index + 2;
        return (right_child_index >= m_size)? -1 : right_child_index;
    }

    // O(logN)
    template<typename T, typename comparator>
    void priority_queue<T, comparator>::heapify_down(int index){
        while (0 <= index && index < m_size){
            int left_index = get_left_child(index);
            int right_index = get_right_child(index);
            if (left_index == -1 && right_index == -1){
                break;
            }
            if (right_index != -1){
                // violate both
                if (m_comp(m_container[index], m_container[left_index]) == false && m_comp(m_container[index], m_container[right_index]) == false){
                    if (m_comp(m_container[left_index], m_container[right_index]) == true){
                        std::swap(m_container[index], m_container[left_index]);
                        index = left_index;                     
                    }
                    else{
                        std::swap(m_container[index], m_container[right_index]);
                        index = right_index;                      
                    }
                }
                // violate only left
                else if (m_comp(m_container[index], m_container[left_index]) == false && m_comp(m_container[index], m_container[right_index]) == true){
                    std::swap(m_container[index], m_container[left_index]);
                    index = left_index;
                }
                // violate only right
                else if (m_comp(m_container[index], m_container[left_index]) == true && m_comp(m_container[index], m_container[right_index]) == false){
                    std::swap(m_container[index], m_container[right_index]);
                    index = right_index;
                }
                // does not violate anything
                else{
                    break;
                }
            }  
            else{
                // can not find any right child
                if (m_comp(m_container[index], m_container[left_index]) == false){
                    std::swap(m_container[index], m_container[left_index]);
                    index = left_index;
                }
                else{
                    break;
                }
            }
        }
    }

    // O(1)
    template<typename T, typename comparator>
    T priority_queue<T, comparator>::top() const{
        return m_container.front();
    }

    // O(1)
    template<typename T, typename comparator>
    bool priority_queue<T, comparator>::empty() const{
        return m_size == 0;
    }

    // O(1)
    template<typename T, typename comparator>
    int priority_queue<T, comparator>::size() const{
        return m_size;
    }

    // O(logN)
    template<typename T, typename comparator>
    void priority_queue<T, comparator>::push(T val){
        m_container.push_back(val);
        m_size ++;
        // TODO: implement heapify up
        heapify_up(m_size - 1);
    }

    // O(logN)
    template<typename T, typename comparator>
    void priority_queue<T, comparator>::pop(){
        if (empty() == true){
            std::cerr << "The queue is empty!" << '\n';
            return;
        }
        // TODO: implement heapify down
        /**
         * process:
         * - swap root with the last node
         * - delete the last node
         * - heapify down the tree from root
         */
        std::swap(m_container.front(), m_container.back());
        m_container.pop_back();
        m_size --;
        if (empty() == false) heapify_down(0);
    }
}

#endif