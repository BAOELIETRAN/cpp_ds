// #include "stack.h"

// namespace wxrdie{
//     my_stack& my_stack::operator=(const my_stack& other_stack){
//         // copy other stack to this stack
//         if (this != &other_stack){
//             m_inner_container = other_stack.m_inner_container;
//             m_size = other_stack.m_inner_container.size();
//         }
//         return *this;
//     }

//     int my_stack::top() const{
//         if (m_size == 0){
//             throw std::out_of_range("Stack is currently empty");
//         }
//         return m_inner_container.back();
//     }

//     void my_stack::push(int val){
//         m_inner_container.push_back(val);
//         m_size ++;
//     }

//     void my_stack::pop(){
//         if (m_size == 0){
//             throw std::out_of_range("Stack is currently empty");
//         }
//         m_inner_container.pop_back();
//         m_size --;
//     }
// }