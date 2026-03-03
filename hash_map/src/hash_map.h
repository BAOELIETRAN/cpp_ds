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
        // load factor = # of stored items / # of available buckets
        // bucket == doubly linked list --> std::list
        private:
            static constexpr std::size_t default_capacity = 11;
            static constexpr float default_load_factor = 0.75f;
            std::array<std::list<std::pair<int, int>>, default_capacity>* hash_table{};
            // number of buckets -- size of hash table
            std::size_t m_bucket_count{default_capacity};
            // max number of elements
            std::size_t m_threshold{static_cast<std::size_t>(m_bucket_count * default_load_factor)};
        public:
            // TODO
    };
}

#endif