#ifndef ANH_PHAN_HASH_MAP_H
#define ANH_PHAN_HASH_MAP_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <list>

// initialization order: base class --> data member (in declaring order) --> constructor body
namespace anh_phan{
    class hash_map{
        private:
            static constexpr std::size_t default_capacity = 11;
            static constexpr float default_load_factor = 0.75f;
            // bucket == doubly linked list --> std::list
            // linked list of <key, value>
            std::vector<std::list<std::pair<int, int>>> hash_table{};
            // number of buckets -- size of hash table
            std::size_t m_capacity{};
            // load factor = # of stored items / # of available buckets
            float m_load_factor{};
            // max number of elements
            std::size_t m_threshold{};
        public:
            // default constructor
            hash_map();
            // copy constructor
            hash_map(const hash_map& other_map);
            // copy assignment
            hash_map& operator=(const hash_map& other_map);
            // move constructor
            hash_map(hash_map&& other_map);
            // move assignment
            hash_map& operator=(hash_map&& other_map);
            // destructor
            ~hash_map() = default;

            // iterator
            class iterator{
                using bucket = std::list<std::pair<int, int>>;
                using table = std::vector<bucket>;
                private:
                    // hash map 
                    hash_map* m_map_it{};
                    std::size_t m_bucket_index{};
                    bucket::iterator m_bucket_it{};
                    void skip_empty(){
                        while (m_bucket_index < m_map_it->hash_table.size()){
                            if (m_map_it->hash_table[m_bucket_index].empty()){
                                m_bucket_index ++;
                            }
                            else{
                                m_bucket_it = m_map_it->hash_table[m_bucket_index].begin();
                                break;
                            }
                        }
                    }
                public:
                    // default constructor
                    iterator() = default;
                    // direct constructor
                    explicit iterator(hash_map* map_ptr, std::size_t index) : m_map_it{map_ptr}, m_bucket_index{index}{
                        if (m_bucket_index < map_ptr->m_capacity){   
                            m_bucket_it = map_ptr->hash_table[m_bucket_index].begin();
                        }
                        skip_empty();
                    };
                    // copy constructor
                    iterator(const iterator& other_it) = default;
                    // copy assignment
                    iterator& operator=(const iterator& other_it) = default;
            };
            iterator begin(){
                // this -- pointer to the current object (class hash_map)
                iterator begin_it{this, 0};
                return begin_it;
            }
            iterator end(){
                iterator end_it{this, m_capacity};
                return end_it;
            }
    };
}

#endif