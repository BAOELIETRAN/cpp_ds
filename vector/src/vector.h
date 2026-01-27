#ifndef VECTOR_H
#define VECTOR_H

namespace mck{
    class my_vector{
        private:
            // pointer to the array
            int* m_array_pointer;
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
            // constructor with number of elements:
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
            destructor();

            // const at the end of the member function = this function is not allowed to modify the object
            // setter & getter
            int* get_array_pointer() const;
            void set_array_pointer();
            int get_size() const;
            void set_size();
            size_t get_capacity() const;
            void set_capacity();

            // other important member functions:

            // check if the vector is empty?
            bool is_empty() const;

            // return a reference to the element at specified location pos
            int& operator[](int pos) const;

            // similar to operator[], but with bound checking
            int& at(int pos) const;

            // add an element to the end of the vector
            void push_back(int value);

            // remove the last element of the vector
            void pop_back();

            // remove all elements (size will be 0)
            void clear();
    }
}

#endif
