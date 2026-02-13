#ifndef BETEKAR_QUEUE_H
#define BETEKAR_QUEUE_H

#include <list>
#include <cstddef>
#include <stdexcept>

namespace betekar{
    // std::list - implemented by doubly linked list -- O(1) insert & O(1) removal
    template<typename T>
    class my_queue{
        private:
            std::list<T> m_inner_container{};
            std::size_t m_size{};
        public:
            /* constructors */
            // default constructor
            my_queue() = default;
            // copy constructor
            my_queue(const my_queue& other_queue) : m_inner_container{other_queue.m_inner_container}, m_size{other_queue.m_size}{};
            my_queue& operator=(const my_queue& other_queue);
            // destructor
            ~my_queue() = default;

            /* member functions */
            T front() const;
            T back() const;
            bool empty() const {return m_size == 0;};
            std::size_t size() const {return m_size;};
            void push(T val);
            void pop();
    };

    template<typename T>
    my_queue<T>& my_queue<T>::operator=(const my_queue<T>& other_queue){
        if (this != &other_queue){
            m_inner_container = other_queue.m_inner_container;
            m_size = other_queue.m_size;
        }
        return *this;
    }

    template<typename T>
    T my_queue<T>::front() const{
        return m_inner_container.front();
    }

    template<typename T>
    T my_queue<T>::back() const{
        return m_inner_container.back();
    }

    template<typename T>
    void my_queue<T>::push(T val){
        m_inner_container.push_back(val);
        m_size ++;
    }

    template<typename T>
    void my_queue<T>::pop(){
        m_inner_container.pop_front();
        m_size --;
    }
}

#endif