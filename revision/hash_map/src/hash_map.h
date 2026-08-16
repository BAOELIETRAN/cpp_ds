#ifndef NEW_HASH_MAP_H
#define NEW_HASH_MAP_H

#include <iostream>
#include <cstddef>
#include <vector>
#include <utility>
#include <list>
#include <functional>
#include <iterator>

namespace riyadh{
    template <typename T, typename V>
    class new_hash_map{
        using element = std::pair<T, V>;
        using bucket = std::list<element>;
        private:
            static constexpr std::size_t default_capacity = 11;
            static constexpr double default_load_factor = 0.75;
            // hash table = array of buckets
            std::vector<bucket> m_hash_table{};
            // number of buckets - size of hash table
            std::size_t m_capacity{};
            // load factor = # of stored items / # of buckets
            // fixed after initialized
            double m_load_factor{};
            // max number of elements
            std::size_t m_threshold{};
            // current number of elemens
            std::size_t m_size{};
            // resize the whole hash map
            void resize();
            // get the hash value of the key
            std::size_t get_hash_value(T key, std::size_t capacity) const;
        public:
            /* constructors */
            // default constructor
            new_hash_map();
            // copy constructor
            new_hash_map(const new_hash_map& neigh_hash_map);
            // copy assignment
            new_hash_map& operator=(const new_hash_map& neigh_hash_map);
            // move constructor
            new_hash_map(new_hash_map&& neigh_hash_map);
            // move assignment
            new_hash_map& operator=(new_hash_map&& neigh_hash_map);
            // destructor
            ~new_hash_map();

            // iterator
            class iterator{
                private:
                    bucket* m_cur_bucket{};
                public:
                    explicit iterator(const bucket& cur_bucket);
                    element& operator*();
                    element* operator->();
                    iterator& operator++();
                    iterator operator++(int);
                    iterator& operator--();
                    iterator operator--(int);
                    bool operator==(const iterator& other_it) const;
                    bool operator!=(const iterator& other_it) const;
            };

            /* member methods */
            bool empty() const;
            std::size_t size() const;
            void clear();
            V& operator[](const T& key);
            void erase(const T& key);
            bool contains(const T& key) const;
    };

    // default constructor
    template <typename T, typename V>
    new_hash_map<T, V>::new_hash_map()
    : m_hash_table{std::vector<bucket>(default_capacity, bucket())}, 
        m_capacity{default_capacity}, m_load_factor{default_load_factor},
        m_threshold{m_load_factor * m_capacity}, m_size{0}{}

    // copy constructor
    template <typename T, typename V>
    new_hash_map<T, V>::new_hash_map(const new_hash_map& neigh_hash_map)
    : m_hash_table{neigh_hash_map.m_hash_table}, m_capacity{neigh_hash_map.m_capacity},
    m_load_factor{neigh_hash_map.m_load_factor}, m_threshold{neigh_hash_map.m_threshold},
    m_size{neigh_hash_map.m_size}{}

    // copy assignment
    template <typename T, typename V>
    new_hash_map<T, V>& new_hash_map<T, V>::operator=(const new_hash_map& neigh_hash_map){
        if (this == &neigh_hash_map) return *this;
        m_hash_table = neigh_hash_map.m_hash_table;
        m_capacity = neigh_hash_map.m_capacity;
        m_load_factor = neigh_hash_map.m_load_factor;
        m_threshold = neigh_hash_map.m_threshold;
        m_size = neigh_hash_map.m_size;
        return *this;
    }

    // move constructor
    template <typename T, typename V>
    new_hash_map<T, V>::new_hash_map(new_hash_map&& neigh_hash_map)
    : m_hash_table{std::move(neigh_hash_map.m_hash_table)}, 
    m_capacity{std::move(neigh_hash_map.m_capacity)}, 
    m_load_factor{std::move(neigh_hash_map.m_load_factor)},
    m_threshold{std::move(neigh_hash_map.m_threshold)},
    m_size{std::move(neigh_hash_map.m_size)}{
        neigh_hash_map.m_hash_table = std::vector<bucket>(default_capacity, bucket());
        neigh_hash_map.m_capacity = default_capacity;
        neigh_hash_map.m_load_factor = default_load_factor;
        neigh_hash_map.m_threshold = static_cast<std::size_t>(default_load_factor * default_capacity);
        neigh_hash_map.m_size = 0;
    }

    // move assignment
    template <typename T, typename V>
    new_hash_map<T, V>& new_hash_map<T, V>::operator=(new_hash_map&& neigh_hash_map){
        if (this == &neigh_hash_map) return *this;
        m_hash_table = std::move(neigh_hash_map.m_hash_table);
        m_capacity = std::move(neigh_hash_map.m_capacity);
        m_load_factor = std::move(neigh_hash_map.m_load_factor);
        m_threshold = std::move(neigh_hash_map.m_threshold);
        m_size = std::move(neigh_hash_map.m_size);
        neigh_hash_map.m_hash_table = std::vector<bucket>(default_capacity, bucket());
        neigh_hash_map.m_capacity = default_capacity;
        neigh_hash_map.m_load_factor = default_load_factor;
        neigh_hash_map.m_threshold = static_cast<std::size_t>(default_load_factor * default_capacity);
        neigh_hash_map.m_size = 0;
        return *this;
    }

    // destructor
    template <typename T, typename V>
    new_hash_map<T, V>::~new_hash_map(){
        m_hash_table.clear();
        m_capacity = default_capacity;
        m_load_factor = default_load_factor;
        m_threshold = 0;
        m_size = 0;
    }

    // get the hash value of the key
    template <typename T, typename V>
    std::size_t new_hash_map<T, V>::get_hash_value(T key, std::size_t capacity) const{
        std::hash<T> key_hasher{};
        return key_hasher(key) % capacity;
    }

    // resize the whole hash map
    template <typename T, typename V>
    void new_hash_map<T, V>::resize(){
        m_capacity *= 2;
        std::vector<bucket> new_hash_table(m_capacity, bucket());
        for (auto& cur_bucket : m_hash_table){
            for (element& ele : cur_bucket){
                T key = ele.first;
                std::size_t new_bucket_idx = get_hash_value(key, m_capacity);
                new_hash_table[new_bucket_idx].push_back(std::move(ele));
            }
        }
        m_threshold = static_cast<std::size_t>(m_load_factor * m_capacity);
        m_hash_table = std::move(new_hash_table);
    }

    // empty
    template <typename T, typename V>
    bool new_hash_map<T, V>::empty() const{
        return m_size == 0;
    }

    // size
    template <typename T, typename V>
    std::size_t new_hash_map<T, V>::size() const{
        return m_size;
    }

    // clear
    template <typename T, typename V>
    void new_hash_map<T, V>::clear(){
        m_hash_table = std::vector<bucket>(default_capacity, bucket());
        m_capacity = default_capacity;
        m_load_factor = default_load_factor;
        m_threshold = static_cast<std::size_t>(default_load_factor * default_capacity);
        m_size = 0;
    }

    template <typename T, typename V>
    V& new_hash_map<T, V>::operator[](const T& key){
        std::size_t cur_bucket_idx = get_hash_value(key, m_capacity);
        for (element& ele : m_hash_table[cur_bucket_idx]){
            if (ele.first == key) return ele.second;
        }
        m_hash_table[cur_bucket_idx].push_back({key, V()});
        m_size ++;
        if (m_size > m_threshold){
            resize();
            return operator[](key);
        }
        return m_hash_table[cur_bucket_idx].back().second;
    }

    template <typename T, typename V>
    void new_hash_map<T, V>::erase(const T& key){
        std::size_t cur_bucket_idx = get_hash_value(key, m_capacity);
        bucket& cur_bucket = m_hash_table[cur_bucket_idx];
        for (auto it = cur_bucket.begin(); it != cur_bucket.end(); it ++){
            if (it->first == key){
                cur_bucket.erase(it);
                m_size --;
                return;
            }
        }
    }

    template <typename T, typename V>
    bool new_hash_map<T, V>::contains(const T& key) const{
        std::size_t cur_bucket_idx = get_hash_value(key, m_capacity);
        const bucket& cur_bucket = m_hash_table[cur_bucket_idx];
        for (const element& ele : cur_bucket){
            if (ele.first == key) return true;
        }
        return false;
    }
}

#endif