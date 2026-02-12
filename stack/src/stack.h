// implement using vector

#ifndef WXRDIE_STACK_H
#define WXRDIE_STACK_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace wxrdie{
    template<typename T>
    class my_stack{
        private:
            std::vector<T> m_inner_container{};
            std::size_t m_size{};
        public:
            /* constructors */
            // default constructor
            my_stack() = default;
            // copy constructor
            // since copying uses initializing --> member initializer list
            my_stack(const my_stack& other_stack) : m_inner_container{other_stack.m_inner_container}, m_size{other_stack.size()}{};
            // assignment
            my_stack& operator=(const my_stack& other_stack);
            // default destructor
            ~my_stack() = default;

            /* member functions */
            T top() const;
            bool empty() const { return m_size == 0; };
            std::size_t size() const { return m_size; };
            void push(T val);
            void pop();
    };

    template<typename T>
    my_stack<T>& my_stack<T>::operator=(const my_stack<T>& other_stack){
        // copy other stack to this stack
        if (this != &other_stack){
            m_inner_container = other_stack.m_inner_container;
            m_size = other_stack.m_inner_container.size();
        }
        return *this;
    }
    
    template<typename T>
    T my_stack<T>::top() const{
        if (m_size == 0){
            throw std::out_of_range("Stack is currently empty");
        }
        return m_inner_container.back();
    }

    template<typename T>
    void my_stack<T>::push(T val){
        m_inner_container.push_back(val);
        m_size ++;
    }

    template<typename T>
    void my_stack<T>::pop(){
        if (m_size == 0){
            throw std::out_of_range("Stack is currently empty");
        }
        m_inner_container.pop_back();
        m_size --;
    }
}

#endif
