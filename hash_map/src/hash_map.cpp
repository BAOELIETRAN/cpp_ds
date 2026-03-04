#include "hash_map.h"

namespace anh_phan{
    // default constructor 
    hash_map::hash_map(){
        m_capacity = default_capacity;
        m_load_factor = default_load_factor;
        m_threshold = m_capacity * m_load_factor;
        hash_table.resize(m_capacity);
        m_size = 0;
    }

    // direct constructor
    hash_map::hash_map(std::size_t capacity, float load_factor) 
    : m_capacity{capacity}, m_load_factor{load_factor}, m_threshold{capacity * load_factor}{
        // it is ok to throw an exception inside constructor body
        if (m_capacity == 0 || m_load_factor == 0.0f || m_threshold == 0){
            throw std::logic_error("The hash map can not be empty!");
        }
        hash_table.resize(m_capacity);
    }

    // copy constructor
    hash_map::hash_map(const hash_map& other_map) 
    : m_capacity{other_map.m_capacity}, m_load_factor{other_map.m_load_factor}, 
        m_threshold{other_map.m_threshold}, m_size{other_map.m_size}, hash_table{other_map.hash_table}{
        // it is ok to throw an exception inside constructor body
        if (m_capacity == 0 || m_load_factor == 0.0f || m_threshold == 0){
            throw std::logic_error("The hash map can not be empty!");
        }
    }

    // copy assignment
    hash_map& hash_map::operator=(const hash_map& other_map){
        // self assignment check
        if (this == &other_map){
            return *this;
        }
        if (other_map.m_capacity == 0 || other_map.m_load_factor == 0.0f || other_map.m_threshold == 0){
            throw std::logic_error("The hash map can not be empty!");
        }
        // set to new data
        hash_table = other_map.hash_table;
        m_capacity = other_map.m_capacity;
        m_load_factor = other_map.m_load_factor;
        m_threshold = other_map.m_threshold;
        m_size = other_map.m_size;
        return *this;
    }

    // reset after move
    void hash_map::reset_after_move(hash_map& other_map){
        other_map.hash_table = std::vector<bucket>();
        other_map.m_capacity = 0;
        other_map.m_load_factor = 0.0f;
        other_map.m_threshold = 0;
        other_map.m_size = 0;
    }

    // move constructor
    hash_map::hash_map(hash_map&& other_map) noexcept
    : m_capacity{std::move(other_map.m_capacity)}, m_load_factor{std::move(other_map.m_load_factor)},
        m_threshold{std::move(other_map.m_threshold)}, m_size{std::move(other_map.m_size)},
        hash_table{std::move(other_map.hash_table)}{
            if (m_capacity == 0 || m_load_factor == 0.0f || m_threshold == 0){
                throw std::logic_error("The hash map can not be empty!");
            }
            // reset other_map after being moved
            reset_after_move(other_map);
        }

    // move assignment
    hash_map& hash_map::operator=(hash_map&& other_map) noexcept{
        // check self assignment
        if (this == &other_map){
            return *this;
        }
        if (other_map.m_capacity == 0 || other_map.m_load_factor == 0.0f || other_map.m_threshold == 0){
            throw std::logic_error("The hash map can not be empty!");
        }
        // move data
        hash_table = std::move(other_map.hash_table);
        m_capacity = std::move(other_map.m_capacity);
        m_load_factor = std::move(other_map.m_load_factor);
        m_threshold = std::move(other_map.m_threshold);
        m_size = std::move(other_map.m_size);
        // reset other_map after being moved
        // r-value reference variable is used in an expression here --> l-value
        reset_after_move(other_map);
        return *this;
    }

    // empty out the hash map
    void hash_map::clear(){
        hash_table = std::vector<bucket>();
        m_capacity = 0;
        m_load_factor = 0.0f;
        m_threshold = 0;
        m_size = 0;
    }

    // get hash value of a key
    std::size_t hash_map::get_hash_value(int key) const{
        if (m_capacity == 0){
            throw std::logic_error("The hash map can not be empty");
        }
        std::hash<int> hasher{};
        return hasher(key) % m_capacity;
    }

    // resize the whole hash map if the threshold is exceeded
    void hash_map::resize(){
        // create a new vector with 2x the length
        std::vector<bucket> temp_hash_table(2 * m_capacity);
        // move all elements from old hash map to new hash map
        for (bucket buck : hash_table){
            for (element pair : buck){
                int cur_key = pair.first;
                std::size_t new_index = get_hash_value(cur_key);
                temp_hash_table[new_index].push_back(pair);
            }
        }
        // assign new value
        hash_table = temp_hash_table;
        m_capacity = 2 * m_capacity;
        m_threshold = m_capacity * m_load_factor;
    }
}