#ifndef NEW_VECTOR_H
#define NEW_VECTOR_H

#include <iostream>
#include <utility>

namespace tel_aviv{
    template<typename T>
    class new_vector{
        private:
            T* m_container{};
            std::size_t m_size{};
            std::size_t m_capacity{2};
            void resize();
        public:
            /* constructors */
            // default constructor
            explicit new_vector();
            // constructor with size
            explicit new_vector(std::size_t size);
            // copy constructor
            explicit new_vector(const new_vector& neigh_vector);
            // copy assignment
            new_vector& operator=(const new_vector& neigh_vector);
            // move constructor
            explicit new_vector(new_vector&& neigh_vector);
            // move assignment
            new_vector& operator=(new_vector&& neigh_vector);
            // destructor
            ~new_vector();

            // TODO: iterator

            /* member methods */
            void push_back(const T& value);
            void push_back(T&& value);
            void pop_back();
            T& operator[](std::size_t pos);
            const T& operator[](std::size_t pos) const;
            T& at(std::size_t pos);
            const T& at(std::size_t pos) const;
            std::size_t size() const;
            std::size_t capacity() const;
            bool empty() const;
            void clear();
    };

    // constructor with size
    template <typename T>
    new_vector<T>::new_vector(std::size_t start_size){
        while (m_capacity < start_size){
            m_capacity *= 2;
        }
        m_container = new T[m_capacity]{};
        m_size = start_size;
    }

    // default constructor
    template <typename T>
    // constructor delegation
    new_vector<T>::new_vector() : new_vector<T>::new_vector(0){}; 

    // copy constructor
    template <typename T>
    new_vector<T>::new_vector(const new_vector& neigh_vector){
        std::size_t neigh_size = neigh_vector.m_size;
        std::size_t neigh_capacity = neigh_vector.m_capacity;
        // set new size & capacity
        m_size = neigh_size;
        m_capacity = neigh_capacity;
        m_container = new T[m_capacity];
        for (std::size_t i = 0; i < m_size; i ++){
            m_container[i] = neigh_vector[i];
        }
    }

    // resize
    template <typename T>
    void new_vector<T>::resize(){
        // x2 the capacity
        m_capacity *= 2;
        T* new_container = new T[m_capacity];
        for (std::size_t i = 0; i < m_size; i ++){
            new_container[i] = m_container[i];
        }
        delete[] m_container;
        m_container = new_container;
    }

    // copy assignment
    template <typename T>
    new_vector<T>& new_vector<T>::operator=(const new_vector& neigh_vector){
        if (this == &neigh_vector) return *this;
        std::size_t neigh_size = neigh_vector.m_size;
        std::size_t neigh_capacity = neigh_vector.m_capacity;
        // free old container
        delete[] m_container;
        m_size = neigh_size;
        m_capacity = neigh_capacity;
        m_container = new T[m_capacity];
        for (std::size_t i = 0; i < m_size; i ++){
            m_container[i] = neigh_vector[i];
        }
        return *this;
    } 

    // move constructor
    template <typename T>
    new_vector<T>::new_vector(new_vector&& neigh_vector){
        m_size = neigh_vector.m_size;
        m_capacity = neigh_vector.m_capacity;
        m_container = neigh_vector.m_container;
        // neigh pointer no longer owning resource
        // reset neighbour
        neigh_vector.m_container = nullptr;
        neigh_vector.m_capacity = 0;
        neigh_vector.m_size = 0;
    }

    // move assignment
    template <typename T>
    new_vector<T>& new_vector<T>::operator=(new_vector&& neigh_vector){
        // this = implicit pointer to the current object instance
        if (this == &neigh_vector) return *this;
        // free the old container
        delete[] m_container;
        m_size = neigh_vector.m_size;
        m_capacity = neigh_vector.m_capacity;
        m_container = neigh_vector.m_container;
        // neigh pointer no longer owning resource
        // reset neighbour
        neigh_vector.m_container = nullptr;
        neigh_vector.m_capacity = 0;
        neigh_vector.m_size = 0;
        return *this;
    }

    // destructor
    template <typename T>
    new_vector<T>::~new_vector(){
        // free the old container and reset 
        m_size = 0;
        m_capacity = 0;
        delete[] m_container;
    }

    // push back
    template <typename T>
    void new_vector<T>::push_back(const T& value){
        if (m_size >= m_capacity) resize();
        m_container[m_size] = value;
        m_size ++;
    }

    template <typename T>
    void new_vector<T>::push_back(T&& value){
        /*
            in function body, a named variable is 
            always l-value.
            --> value here is a l-value.
            --> to make other thing own it --> use
            std::move() to convert the things into
            r-value reference.
        */
        if (m_size >= m_capacity) resize();
        m_container[m_size] = std::move(value);
        m_size ++;
    }

    template <typename T>
    void new_vector<T>::pop_back(){
        if (m_size == 0) return;
        m_container[m_size - 1] = T();
        m_size --;
    }

    template <typename T>
    T& new_vector<T>::operator[](std::size_t pos){
        // no OOB check -- in exchange for speed
        return m_container[pos];
    }

    template <typename T>
    const T& new_vector<T>::operator[](std::size_t pos) const{
        // no OOB check -- in exchange for speed
        return m_container[pos];
    }

    template <typename T>
    T& new_vector<T>::at(std::size_t pos){
        if (pos >= m_size) throw std::out_of_range("Index out of bound");
        return m_container[pos];
    }

    template <typename T>
    const T& new_vector<T>::at(std::size_t pos) const{
        if (pos >= m_size) throw std::out_of_range("Index out of bound");
        return m_container[pos];
    }

    template <typename T>
    std::size_t new_vector<T>::size() const{
        return m_size;
    }

    template <typename T>
    std::size_t new_vector<T>::capacity() const{
        return m_capacity;
    }

    template <typename T>
    bool new_vector<T>::empty() const{
        return m_size == 0;
    }

    template <typename T>
    void new_vector<T>::clear(){
        for (std::size_t i = 0; i < m_size; i ++){
            m_container[i] = T();
        }
        m_size = 0;
    }
}

#endif