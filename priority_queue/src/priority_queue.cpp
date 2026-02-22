#include "priority_queue.h"

namespace gio{
    // O(1)
    int priority_queue::get_parent(int index) const{
        if (index < 0 || index >= m_size){
            // program will terminate since no catch block is found in call stack
            throw std::out_of_range("The index is invalid!");
        }
        return (index - 1)/2;
    }

    // O(logN)
    void priority_queue::heapify_up(int index){
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