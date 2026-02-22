#include "priority_queue.h"

namespace gio{
    // O(1)
    int priority_queue::get_parent(int index) const{
        if (index < 0 || index >= m_size){
            // program will terminate since no catch block is found in call stack
            throw std::out_of_range("The index is invalid!");
        }
        return (index == 0)? 0 : (index - 1)/2;
    }

    // O(logN)
    void priority_queue::heapify_up(int index){
        while (get_parent(index) >= 0 && m_comp(m_container[get_parent(index)], m_container[index]) == false){
            std::swap(m_container[get_parent(index)], m_container[index]);
            index = get_parent(index);
        }
    }
    
    // O(1)
    int priority_queue::get_left_child(int index) const{
        if (index < 0 || index >= m_size){
            throw std::out_of_range("The index is invalid!");
        }
        int left_child_index = 2 * index + 1;
        return (left_child_index >= m_size)? -1 : left_child_index;
    }

    // O(1)
    int priority_queue::get_right_child(int index) const{
        if (index < 0 || index >= m_size){
            throw std::out_of_range("The index is invalid!");
        }
        int right_child_index = 2 * index + 2;
        return (right_child_index >= m_size)? -1 : right_child_index;
    }

    // O(logN)
    void priority_queue::heapify_down(int index){

    }

    // O(1)
    int priority_queue::top() const{
        return m_container.front();
    }

    // O(1)
    bool priority_queue::empty() const{
        return m_size == 0;
    }

    // O(1)
    int priority_queue::size() const{
        return m_size;
    }

    // O(logN)
    void priority_queue::push(int val){
        m_container.push_back(val);
        m_size ++;
        // TODO: implement heapify up
        heapify_up(m_size - 1);
    }

    // O(logN)
    void priority_queue::pop(){
        if (empty() == true){
            std::cerr << "The queue is empty!" << '\n';
            return;
        }
        // TODO: implement heapify down
        heapify_down(0);
        m_container.pop_back();
        m_size --;
    }
}