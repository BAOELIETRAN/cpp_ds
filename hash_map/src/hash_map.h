#ifndef ANH_PHAN_HASH_MAP_H
#define ANH_PHAN_HASH_MAP_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <array>
#include <list>

// initialization order: base class --> data member (in declaring order) --> constructor body
namespace anh_phan{
    class hash_map{
        private:
            static constexpr std::size_t default_capacity = 11;
            static constexpr float default_load_factor = 0.75f;
            // bucket == doubly linked list --> std::list
            // linked list of <key, value>
            std::array<std::list<std::pair<int, int>>, default_capacity>* hash_table{};
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
            ~hash_map();

            // iterator
            class iterator{

            };
    };
}

#endif