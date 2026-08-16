#ifndef NEW_UNIQUE_PTR_H
#define NEW_UNIQUE_PTR_H

#include <iostream>

namespace abu_dhabi{
    template <typename T>
    class new_unique_ptr{
        private:
            T* m_inner_ptr{};
        public:
            /* constructors */
            // default constructor
            new_unique_ptr();
            // constructor from raw pointer
            explicit new_unique_ptr(T* other_ptr);
            // copy constructor
            explicit new_unique_ptr(const new_unique_ptr& other_unique_ptr) = delete;
            // copy assignment
            new_unique_ptr& operator=(const new_unique_ptr& other_unique_ptr) = delete;
            // move constructor
            explicit new_unique_ptr(new_unique_ptr&& other_unique_ptr);
            // move assignment
            new_unique_ptr& operator=(new_unique_ptr&& other_unique_ptr);
            // destructor
            ~new_unique_ptr();

            /* member methods */
            T& operator*() const;
            T* operator->() const;
            // return the raw pointer without releasing the ownership
            T* get() const;
            // return the raw pointer and give up on ownership
            // not deleting the resource
            T* release();
            // delete the currently owned resource, then take ownership 
            // of new resource
            void reset(T* new_ptr = nullptr);
            // check whether *this owns an object
            explicit operator bool() const;
            // swap the managed objects
            void swap(new_unique_ptr& other_unique_ptr);
    };

    template <typename T>
    // default constructor
    new_unique_ptr<T>::new_unique_ptr() : m_inner_ptr{nullptr}{}
    
    // constructor from raw pointer
    template <typename T>
    new_unique_ptr<T>::new_unique_ptr(T* other_ptr) : m_inner_ptr{other_ptr}{}

    // move constructor
    template <typename T>
    new_unique_ptr<T>::new_unique_ptr(new_unique_ptr&& other_unique_ptr)
    : m_inner_ptr{other_unique_ptr.m_inner_ptr}{
        other_unique_ptr.m_inner_ptr = nullptr;
    }

    // move assignment 
    template <typename T>
    new_unique_ptr<T>& new_unique_ptr<T>::operator=(new_unique_ptr&& other_unique_ptr){
        if (this == &other_unique_ptr) return *this;
        delete m_inner_ptr;
        m_inner_ptr = other_unique_ptr.m_inner_ptr;
        other_unique_ptr.m_inner_ptr = nullptr;
        return *this;
    }

    // destructor
    template <typename T>
    new_unique_ptr<T>::~new_unique_ptr(){
        delete m_inner_ptr;
        m_inner_ptr = nullptr;
    }

    template <typename T>
    T& new_unique_ptr<T>::operator*() const{
        return *m_inner_ptr;
    }

    template <typename T>
    T* new_unique_ptr<T>::operator->() const{
        return m_inner_ptr;
    }

    template <typename T>
    T* new_unique_ptr<T>::get() const{
        return m_inner_ptr;
    }

    template <typename T>
    T* new_unique_ptr<T>::release(){
        T* cur_ptr = m_inner_ptr;
        m_inner_ptr = nullptr;
        return cur_ptr;
    }

    template <typename T>
    void new_unique_ptr<T>::reset(T* new_ptr){
        T* old_pointer = m_inner_ptr;
        m_inner_ptr = new_ptr;
        if (old_pointer != new_ptr) delete old_pointer;
    }

    template <typename T>
    new_unique_ptr<T>::operator bool() const{
        if (m_inner_ptr != nullptr) return true;
        return false;
    }

    template <typename T>
    void new_unique_ptr<T>::swap(new_unique_ptr<T>& other_unique_ptr){
        T* temp_ptr = m_inner_ptr;
        m_inner_ptr = other_unique_ptr.m_inner_ptr;
        other_unique_ptr.m_inner_ptr = temp_ptr;
    }
}

#endif