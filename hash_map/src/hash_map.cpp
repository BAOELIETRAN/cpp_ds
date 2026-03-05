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
    std::size_t hash_map::get_hash_value(int key, std::size_t capacity) const{
        if (capacity == 0){
            throw std::logic_error("The capacity can not be 0");
        }
        std::hash<int> hasher{};
        return hasher(key) % capacity;
    }

    // resize the whole hash map if the threshold is exceeded
    void hash_map::resize(){
        if (m_capacity == 0){
            throw std::logic_error("The hash map can not be empty!");
        }
        // create a new vector with 2x the length
        std::vector<bucket> temp_hash_table(2 * m_capacity);
        // move all elements from old hash map to new hash map
        // while looping through the object, we can use reference to avoid unnecessary copy
        for (bucket& buck : hash_table){
            for (element& pair : buck){
                int cur_key = pair.first;
                std::size_t new_index = get_hash_value(cur_key, 2 * m_capacity);
                // let the temp_hash_table own the <key, value> pair
                temp_hash_table[new_index].push_back(std::move(pair));
            }
        }
        // assign new value
        // using move to avoid unnecessary copy
        hash_table = std::move(temp_hash_table);
        m_capacity = 2 * m_capacity;
        m_threshold = static_cast<std::size_t>(m_capacity * m_load_factor);
    }

    // check whether the hash map contains the key
    // look up needs to be O(1)
    bool hash_map::contains(int key){
        if (m_capacity == 0){
            throw std::logic_error("The hash map can not be empty!");
        }
        std::size_t buck_index = get_hash_value(key, m_capacity);
        for (const element& pair : hash_table[buck_index]){
            if (pair.first == key){
                return true;
            }
        }
        return false;
    }

    // access value of key in hash map
    int& hash_map::operator[](int key){
        std::size_t buck_index = get_hash_value(key, m_capacity);
        for (element& pair : hash_table[buck_index]){
            if (pair.first == key){
                return pair.second;
            }
        }
        // if can not find the key, insert <key, default value> into the map and return reference to the value
        // if there is a spot --> simply add and return reference
        // if there is no spot left --> resize the map, add <key, value> to the map, and return reference
        if (m_size + 1 > m_threshold){
            resize();
            buck_index = get_hash_value(key, m_capacity);
        }
        hash_table[buck_index].push_back(element(key, int()));
        m_size ++;
        return hash_table[buck_index].back().second;
    }

    // erase <key, val> out of the hash map
    void hash_map::erase(int key){
        std::size_t buck_index = get_hash_value(key, m_capacity);
        bucket& buck = hash_table[buck_index];
        for (auto elem_it = buck.begin(); elem_it != buck.end(); elem_it ++){
            if (elem_it->first == key){
                hash_table[buck_index].erase(elem_it);
                m_size --;
                return;
            }
        }
        throw std::logic_error("The key is not in the map!");
    }

    // return the iterator to the <key, value>
    hash_map::iterator hash_map::find(int key){
        std::size_t buck_index = get_hash_value(key, m_capacity);
        const bucket& buck = hash_table[buck_index];
        // iterator to the current bucket
        iterator cur_buck_it(this, buck_index);
        for (auto it = buck.begin(); it != buck.end(); it ++){
            if (it->first == key){
                return cur_buck_it;
            }
            cur_buck_it ++;
        }
        return end();
    }
}