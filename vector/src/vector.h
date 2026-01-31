#ifndef VECTOR_H
#define VECTOR_H

#include <new>
#include <stdexcept>

namespace mck{
    template<typename T>
    class my_vector{
        private:
            // pointer to the array
            T* m_array_pointer;
            // number of elements inside the array
            int m_size;
            // total allocated space of the array
            // size_t = unsigned integer, used to represent the size, in bytes, of any object in memory
            size_t m_capacity;
            // if we run out of space for any new element 
            // allocate a new array and copy elements
            // new capacity = 2 * old capacity
            void resize();
        public:
            // default constructor:
            my_vector();
            // constructor with n number of elements:
            my_vector(int n);
            // copy constructor - create deep copy of another vector:
            /**
             * Difference between deep copy and shallow copy:
             * 
             * SHALLOW COPY:
             * - Just copies the pointer value (the memory address)
             * - Both the original and copy point to the SAME data in memory
             * - Changes to one object affect the other
             * - Deleting one object makes the other's pointer invalid (dangling pointer)
             * 
             * DEEP COPY:
             * - Allocates NEW memory and copies the actual data
             * - Each object has its own independent copy of the data
             * - Changes to one object do NOT affect the other
             * - Each object can be safely deleted without affecting the other
             * 
             * Example:
             * Shallow: Both pointers -> [1,2,3] (same array)
             * Deep:    ptr1 -> [1,2,3]  and  ptr2 -> [1,2,3] (two separate arrays)
             */
            my_vector(const my_vector& other_vector);
            // destructor - clean up memory:
            ~my_vector();

            // const at the end of the member function = this function is not allowed to modify the object
            // setter & getter
            T* get_array_pointer() const;
            // void set_array_pointer();
            int get_size() const;
            // void set_size();
            size_t get_capacity() const;
            // void set_capacity();

            // other important member functions:

            // check if the vector is empty?
            bool is_empty() const;

            // return a reference to the element at specified location pos
            T& operator[](int pos);

            // similar to operator[], but with bound checking
            T& at(int pos);

            // add an element to the end of the vector
            void push_back(T value);

            // remove the last element of the vector
            void pop_back();

            // remove all elements (size will be 0)
            void clear();
    };

    // since we use template functions --> we need to put their definitions inside this header file
    template<typename T>
    my_vector<T>::my_vector(int start_size){
        // round start_size up to the nearest power of 2
        int real_capacity = 2;
        while (real_capacity < start_size){
            real_capacity = real_capacity * 2;
        }
        // reserve an array for start_size elements
        try{
            m_array_pointer = new T[real_capacity];
            // initialize the array with value 0
            // users can not access slots above start_size yet
            for (int i = 0; i < start_size; i ++){
                // T() --> default value of any type
                m_array_pointer[i] = T();
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

    template<typename T>
    my_vector<T>::my_vector() : my_vector(0){}

    template<typename T>
    my_vector<T>::my_vector(const my_vector<T>& other_vector){
        // instantiate fields
        m_size = other_vector.get_size();
        m_capacity = other_vector.get_capacity();
        try{
            m_array_pointer = new T[m_capacity];
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

    template<typename T>
    my_vector<T>::~my_vector(){
        if (m_array_pointer != nullptr){
            delete[] m_array_pointer;
        }
    }

    template<typename T>
    void my_vector<T>::resize(){
        m_capacity = m_capacity * 2;
        try{
            // create a new pointer
            T* new_array_pointer = new T[m_capacity];
            // copy all the data from the old vector
            for (int i = 0; i < m_size; i ++){
                new_array_pointer[i] = m_array_pointer[i];
            }
            // if the addr of the new T[] != that of old T[]
            if (m_array_pointer != new_array_pointer){
                delete m_array_pointer;
            }
            m_array_pointer = new_array_pointer;
        }
        catch (const std::bad_alloc& e){
            std::cerr << "Memory allocation failed: " << e.what() << '\n';
            exit(1);
        }
    }

    template<typename T>
    T* my_vector<T>::get_array_pointer() const{
        return m_array_pointer;
    }

    template<typename T>
    int my_vector<T>::get_size() const{
        return m_size; 
    }

    template<typename T>
    size_t my_vector<T>::get_capacity() const{
        return m_capacity;
    }

    template<typename T>
    bool my_vector<T>::is_empty() const{
        if (m_size == 0){
            return true;
        }
        return false;
    }

    template<typename T>
    T& my_vector<T>::operator[](int pos){
        return m_array_pointer[pos];
    }

    template<typename T>
    T& my_vector<T>::at(int pos){
        if (pos < 0 || pos >= m_size){
            throw std::out_of_range("Index out of range");
        }
        return m_array_pointer[pos];
    }

    template<typename T>
    void my_vector<T>::push_back(T value){
        // resize if there is no space left
        if (m_size == m_capacity){
            resize();
        }
        m_array_pointer[m_size] = value;
        m_size ++;
    }

    template<typename T>
    void my_vector<T>::pop_back(){
        if (m_size == 0){
            throw std::out_of_range("Calling pop_back() on an empty vector");
        }
        m_size --;
    }

    template<typename T>
    void my_vector<T>::clear(){
        m_size = 0;
    }
}

#endif
