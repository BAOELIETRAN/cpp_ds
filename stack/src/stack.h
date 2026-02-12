// implement using vector

#ifndef WXRDIE_STACK_H
#define WXRDIE_STACK_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace wxrdie{
    class my_stack{
        private:
            std::vector<int> m_inner_container{};
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
            int top() const;
            int empty() const { return m_size == 0; };
            std::size_t size() const { return m_size; };
            void push(int val);
            void pop();
    };
}

#endif
