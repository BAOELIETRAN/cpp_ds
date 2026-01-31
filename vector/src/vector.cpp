// #include <iostream>
// #include <new>
// #include <stdexcept>
// #include "vector.h"

// /**
//  * optimize with:
//  * - template
//  * - constexpr
//  * - pass by reference
//  */
// namespace mck{
//     // create a new empty vector 
//     // by allocating some space (capacity)
//     // capacity = amount of storage you have to store elements - not relevant to # of elements
//     // size = number of elements
//     my_vector::my_vector(int start_size){
//         // round start_size up to the nearest power of 2
//         int real_capacity = 2;
//         while (real_capacity < start_size){
//             real_capacity = real_capacity * 2;
//         }
//         // reserve an array for start_size elements
//         try{
//             m_array_pointer = new int[real_capacity];
//             // initialize the array with value 0
//             // users can not access slots above start_size yet
//             for (int i = 0; i < start_size; i ++){
//                 m_array_pointer[i] = 0;
//             }
//         }
//         catch (const std::bad_alloc& e){
//             std::cerr << "Memory allocation failed: " << e.what() << '\n';
//             exit(1);
//         }
//         // total allocated space of the array
//         m_capacity = real_capacity;
//         // number of current elements
//         m_size = start_size;
//     }

//     // default constructor
//     // call other constructor to initialize this object
//     // constructor delegation
//     my_vector::my_vector() : my_vector(0){}

//     // create a new vector by deep copying from another vector
//     // param: const reference to other_vector --> pass by reference
//     // const reference --> we can not modify the object we are referencing to
//     // pass by value is expensive because c++ needs to copy the whole object
//     my_vector::my_vector(const my_vector& other_vector){
//         // instantiate fields
//         m_size = other_vector.get_size();
//         m_capacity = other_vector.get_capacity();
//         try{
//             m_array_pointer = new int[m_capacity];
//             // copy all elements from the other vector to this vector
//             for (int i = 0; i < m_size; i ++){
//                 // if we want to access to an element inside the vector using other_vector[i]
//                 // --> we need to implement the operator[] func first.
//                 // --> for now, we can only use the array pointer of this object and access element through it
//                 m_array_pointer[i] = other_vector.get_array_pointer()[i];
//             }
//         }
//         catch (const std::bad_alloc& e){
//             std::cerr << "Memory allocation failed: " << e.what() << '\n';
//             exit(1);
//         }
//     }

//     // destructor - clean up memory
//     my_vector::~my_vector(){
//         if (m_array_pointer != nullptr){
//             delete[] m_array_pointer;
//         }
//     }

//     // allocate a new array and copy elements
//     // new capacity = 2 * old capacity
//     void my_vector::resize(){
//         m_capacity = m_capacity * 2;
//         try{
//             // create a new pointer
//             int* new_array_pointer = new int[m_capacity];
//             // copy all the data from the old vector
//             for (int i = 0; i < m_size; i ++){
//                 new_array_pointer[i] = m_array_pointer[i];
//             }
//             // if the addr of the new int[] != that of old int[]
//             if (m_array_pointer != new_array_pointer){
//                 delete m_array_pointer;
//             }
//             m_array_pointer = new_array_pointer;
//         }
//         catch (const std::bad_alloc& e){
//             std::cerr << "Memory allocation failed: " << e.what() << '\n';
//             exit(1);
//         }
//     }

//     // get m_array_pointer
//     int* my_vector::get_array_pointer() const{
//         return m_array_pointer;
//     }

//     // get the number of elements inside the vector
//     int my_vector::get_size() const{
//         return m_size; 
//     }

//     // get the current capacity of the vector (size of the array)
//     size_t my_vector::get_capacity() const{
//         return m_capacity;
//     }

//     // check if the vector is empty?
//     bool my_vector::is_empty() const{
//         if (m_size == 0){
//             return true;
//         }
//         return false;
//     }

//     // return a reference (not a pointer) to the element at specified location pos
//     // this function can not be const because when we return a reference to an element,
//     // the caller can modify that element --> can not const
//     // this is "operator overloading" - we overload the operator "[]"
//     // why we return int&: vec[2] = 10. int& a = vec[2], a = 10 ~ vec[2] = 10
//     int& my_vector::operator[](int pos){
//         return m_array_pointer[pos];
//     }

//     // similar to operator[], but with bound checking
//     int& my_vector::at(int pos){
//         if (pos < 0 || pos >= m_size){
//             throw std::out_of_range("Index out of range");
//         }
//         return m_array_pointer[pos];
//     }

//     // add an element to the end of the vector
//     void my_vector::push_back(int value){
//         // resize if there is no space left
//         if (m_size == m_capacity){
//             resize();
//         }
//         m_array_pointer[m_size] = value;
//         m_size ++;
//     }

//     // remove the last element of the vector
//     void my_vector::pop_back(){
//         if (m_size == 0){
//             throw std::out_of_range("Calling pop_back() on an empty vector");
//         }
//         m_size --;
//     }

//     // remove all elements (size will be 0)
//     void my_vector::clear(){
//         m_size = 0;
//     }
// }
