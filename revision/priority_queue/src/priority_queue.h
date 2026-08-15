#ifndef NEW_PRIORITY_QUEUE_H
#define NEW_PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <utility>
#include <cstddef>

namespace damascus{
    template <typename T>
    class new_priority_queue{
        private:
            std::vector<T> m_heap{};
            std::size_t m_cur_size{};
        public: 
            /* constructors */
            // default constructor
            new_priority_queue();
            // copy constructor
            explicit new_priority_queue(const new_priority_queue& neigh_queue);
            // copy assignment
            new_priority_queue& operator=(const new_priority_queue& neigh_queue);
            // move constructor
            explicit new_priority_queue(new_priority_queue&& neigh_queue);
            // move assignment
            new_priority_queue& operator=(new_priority_queue&& neigh_queue);
            // destructor
            ~new_priority_queue();

            /* member methods */
            std::size_t get_parent_idx(std::size_t index);
            std::size_t get_left_child_idx(std::size_t index);
            std::size_t get_right_child_idx(std::size_t index);
            void heapify_up(std::size_t index);
            void heapify_down(std::size_t index);
            void push(T val);
            void pop();
            T top();
            std::size_t size();
            bool empty();
    };

    // default constructor
    template <typename T>
    new_priority_queue<T>::new_priority_queue() : m_heap{std::vector<T>()}, m_cur_size{0}{};

    // copy constructor
    template <typename T>
    new_priority_queue<T>::new_priority_queue(const new_priority_queue& neigh_queue) 
        : m_heap{neigh_queue.m_heap}, m_cur_size{neigh_queue.m_cur_size}{}

    // copy assignment
    template <typename T>
    new_priority_queue<T>& new_priority_queue<T>::operator=(const new_priority_queue& neigh_queue){
        if (this == &neigh_queue) return *this;
        m_heap = neigh_queue.m_heap;
        m_cur_size = neigh_queue.m_cur_size;
        return *this;
    }

    // move constructor
    template <typename T>
    new_priority_queue<T>::new_priority_queue(new_priority_queue&& neigh_queue) 
        : m_heap{std::move(neigh_queue.m_heap)}, m_cur_size{std::move(neigh_queue.m_cur_size)}{}

    // move assignment
    template <typename T>
    new_priority_queue<T>& new_priority_queue<T>::operator=(new_priority_queue&& neigh_queue){
        if (this == &neigh_queue) return *this;
        m_heap = std::move(neigh_queue.m_heap);
        m_cur_size = std::move(neigh_queue.m_cur_size);
        return *this;
    }

    // destructor
    template <typename T>
    new_priority_queue<T>::~new_priority_queue(){
        m_heap.clear();
        m_cur_size = 0;
    }

    // get parent index
    template <typename T>
    std::size_t new_priority_queue<T>::get_parent_idx(std::size_t index){
        return (index - 1)/2; 
    }

    // get left child index
    template <typename T>
    std::size_t new_priority_queue<T>::get_left_child_idx(std::size_t index){
        return 2 * index + 1;
    }

    // get right child index
    template <typename T>
    std::size_t new_priority_queue<T>::get_right_child_idx(std::size_t index){
        return 2 * index + 2;
    }

    // heapify up
    template <typename T>
    void new_priority_queue<T>::heapify_up(std::size_t index){
        std::size_t cur_index = index;
        while (cur_index > 0){
            std::size_t parent_index = get_parent_idx(cur_index);
            if (m_heap[parent_index] <= m_heap[cur_index]) break;
            std::swap(m_heap[parent_index], m_heap[cur_index]);
            cur_index = parent_index;
        }
    }

    // heapify down
    template <typename T>
    void new_priority_queue<T>::heapify_down(std::size_t index){
        std::size_t cur_index = index;
        std::size_t left_child_index = get_left_child_idx(index);
        std::size_t right_child_index = get_right_child_idx(index);
        while (left_child_index < m_cur_size){
            T left_child = m_heap[left_child_index];
            if (right_child_index < m_cur_size){
                T right_child = m_heap[right_child_index];
                if (m_heap[cur_index] <= left_child && m_heap[cur_index] <= right_child) break;
                if (left_child < right_child){
                    std::swap(m_heap[cur_index], m_heap[left_child_index]);
                    cur_index = left_child_index;
                }
                else{
                    std::swap(m_heap[cur_index], m_heap[right_child_index]);
                    cur_index = right_child_index;
                }
            }
            else{
                if (m_heap[cur_index] <= left_child) break;
                std::swap(m_heap[cur_index], m_heap[left_child_index]);
                cur_index = left_child_index;
            }
            left_child_index = get_left_child_idx(cur_index);
            right_child_index = get_right_child_idx(cur_index);
        }
    }

    // push to heap
    template <typename T>
    void new_priority_queue<T>::push(T val){
        m_heap.push_back(val);
        m_cur_size ++;
        heapify_up(m_cur_size - 1);
    }

    // pop from heap
    template <typename T>
    void new_priority_queue<T>::pop(){
        std::swap(m_heap[0], m_heap[m_cur_size - 1]);
        m_heap.pop_back();
        m_cur_size --;
        heapify_down(0);
    }

    // return top
    template <typename T>
    T new_priority_queue<T>::top(){
        return m_heap.front();
    }

    // return size
    template <typename T>
    std::size_t new_priority_queue<T>::size(){
        return m_cur_size;
    }

    // return empty?
    template <typename T>
    bool new_priority_queue<T>::empty(){
        return m_cur_size == 0;
    }
}

#endif