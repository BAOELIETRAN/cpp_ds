#ifndef ANH_PHAN_HASH_MAP_H
#define ANH_PHAN_HASH_MAP_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <utility>
#include <functional>
#include <list>

// initialization order: base class --> data member (in declaring order) --> constructor body
namespace anh_phan{
    class hash_map{
        using bucket = std::list<std::pair<int, int>>;
        using element = std::pair<int, int>;
        private:
            static constexpr std::size_t default_capacity = 11;
            static constexpr float default_load_factor = 0.75f;
            // bucket == doubly linked list --> std::list
            // linked list of <key, value>
            std::vector<bucket> hash_table{};
            // number of buckets -- size of hash table
            std::size_t m_capacity{};
            // load factor = # of stored items / # of available buckets
            float m_load_factor{};
            // max number of elements
            std::size_t m_threshold{};
            // current number of elements
            std::size_t m_size{};
            // resize the hash map if the threshold is exceeded
            void resize();
            // reset the other_map after being moved
            void reset_after_move(hash_map& other_map);
            // get the hash value
            std::size_t get_hash_value(int key, std::size_t capacity) const;
        public:
            // default constructor
            hash_map();
            // direct constructor
            hash_map(std::size_t capacity, float load_factor);
            // copy constructor
            hash_map(const hash_map& other_map);
            // copy assignment
            hash_map& operator=(const hash_map& other_map);
            // move constructor
            hash_map(hash_map&& other_map) noexcept;
            // move assignment
            hash_map& operator=(hash_map&& other_map) noexcept; 
            // destructor
            ~hash_map() = default;

            // iterator
            // although it is hash map iterator, its core is the bucket iterator
            // hash map iterator is actually bucket iterator
            class iterator{
                private:
                    hash_map* m_map_ptr{};
                    std::size_t m_bucket_index{};
                    bucket::iterator m_bucket_it{};
                    void skip_empty(){
                        while (m_bucket_index < m_map_ptr->hash_table.size()){
                            if (m_map_ptr->hash_table[m_bucket_index].empty()){
                                m_bucket_index ++;
                            }
                            else{
                                m_bucket_it = m_map_ptr->hash_table[m_bucket_index].begin();
                                break;
                            }
                        }
                    }
                public:
                    // declare properties of iterator -- C++ expects this --> make them public
                    using iterator_category = std::forward_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = std::pair<int, int>;
                    using pointer = value_type*;
                    using reference = value_type&;

                    // default constructor
                    iterator() = delete;
                    // direct constructor
                    // if same map --> differentiate by m_bucket_index
                    iterator(hash_map* map_ptr, std::size_t index) : m_map_ptr{map_ptr}, m_bucket_index{index}{
                        if (m_bucket_index < m_map_ptr->hash_table.size()){
                            m_bucket_it = m_map_ptr->hash_table[m_bucket_index].begin();
                        }
                        skip_empty();
                    }
                    // copy constructor
                    iterator(const iterator& other_iter) = default;
                    // copy assignment
                    iterator& operator=(const iterator& other_iter) = default;

                    /* member functions */
                    // return the address of the current element
                    pointer operator->() const{
                        return m_bucket_it.operator->();
                    }

                    // return the value of the current element
                    reference operator*() const{
                        return m_bucket_it.operator*();
                    }
        
                    // prefix increment
                    // move the m_bucket_it
                    iterator& operator++(){
                        if (m_bucket_index == m_map_ptr->hash_table.size()){   
                            return *this;
                        }
                        m_bucket_it ++;
                        if (m_bucket_it == m_map_ptr->hash_table[m_bucket_index].end()){
                            m_bucket_index ++;
                            skip_empty();
                        }
                        return *this;
                    }

                    // postfix increment
                    // move the m_bucket_it
                    iterator operator++(int){
                        auto temp = *this;
                        (*this).operator++();
                        return temp;
                    }

                    // get the key from the iterator
                    // always ensure that m_bucket_it != bucket.end()
                    int get_key() const{
                        return m_bucket_it->first;
                    }

                    // get the value from the iterator
                    // always ensure that m_bucket_it != bucket.end()
                    int get_value() const{ 
                        return m_bucket_it->second;
                    }

                    // whether 2 iterators are the same
                    bool operator==(const iterator& other_it) const{
                        if (m_map_ptr != other_it.m_map_ptr){
                            return false;
                        }
                        if (m_bucket_index != other_it.m_bucket_index){
                            return false;
                        }
                        // if both are at ends
                        if (m_bucket_index == m_map_ptr->hash_table.size()){
                            return true;
                        }
                        return m_bucket_it == other_it.m_bucket_it;
                    }

                    // whether 2 iterators are not the same
                    bool operator!=(const iterator& other_it) const{
                        return !((*this).operator==(other_it));
                    }
            };

            // return the begin iterator of the hash map
            iterator begin(){
                iterator begin_it(this, 0);
                return begin_it;
            }
            // return the end iterator of the hash map
            iterator end(){
                iterator end_it(this, hash_table.size());
                return end_it;
            }
            // check whether the hash map is empty
            bool empty() const { return m_size == 0; }
            // return the current capacity (# of buckets) of hash map
            std::size_t size() const { return m_size; }
            // empty out the hash map
            void clear();
            // get the value of the key + modify the value of the key
            // access to the value of the key --> int&
            int& operator[](int key);
            // erase an element <key, val> out of the hash map
            void erase(int key);
            // whether the hash map contains key or not
            bool contains(int key);
            // find an element with key in the hash map
            // return an iterator to that element
            iterator find(int key);
    };
}

#endif