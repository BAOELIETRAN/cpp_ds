#include <iostream>
#include <new>
#include "vector.h"

namespace mck{
    // create a new empty vector 
    // by allocating some space (capacity)
    // capacity = amount of storage you have to store elements - not relevant to # of elements
    // size = number of elements
    my_vector::my_vector(int start_size){
        // round start_size up to the nearest power of 2
        int real_capacity = 2;
        while (real_capacity < start_size){
            real_capacity = real_capacity * 2;
        }
        // reserve an array for start_size elements
        try{
            m_array_pointer = new int[real_capacity];
            // initialize the array with value 0
            // users can not access slots above start_size yet
            for (int i = 0; i < start_size; i ++){
                m_array_pointer[i] = 0;
            }
        }
        catch (const std::bad_alloc& e){
            std::cerr << "Memory allocation failed: " << e.what() << '\n';
            exit(1);
        }
        // total allocated space of the array
        m_capacity = real_capacity;
        // number of current elements
        m_size = start_size;
    }

    // default constructor
    // call other constructor to initialize this object
    // constructor delegation
    my_vector::my_vector() : my_vector(0){}

    // create a new vector by deep copying from another vector
    // param: const reference to other_vector --> pass by reference
    // const reference --> we can not modify the object we are referencing to
    // pass by value is expensive because c++ needs to copy the whole object
    my_vector::my_vector(const my_vector& other_vector){
        // instantiate fields
        m_size = other_vector.get_size();
        m_capacity = other_vector.get_capacity();
        try{
            m_array_pointer = new int[m_capacity];
            // copy all elements from the other vector to this vector
            for (int i = 0; i < m_size; i ++){
                // if we want to access to an element inside the vector using other_vector[i]
                // --> we need to implement the operator[] func first.
                // --> for now, we can only use the array pointer of this object and access element through it
                m_array_pointer[i] = other_vector.get_array_pointer()[i];
            }
        }
        catch (const std::bad_alloc& e){
            std::cerr << "Memory allocation failed: " << e.what() << '\n';
            exit(1);
        }
    }

}
