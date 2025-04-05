#pragma once

#include <vector>
#include <list>
#include <functional>
#include <stdexcept>

template<typename K, typename V, typename Hash = std::hash<K>>
class hash_map {
private:
    std::vector<std::list< std::pair<K, V> >> table;
    size_t element_count;
    double max_load_factor;
    Hash hasher;

    void rehash_if_needed() {
        if (load_factor() > max_load_factor) {
            size_t new_bucket_count = table.size() * 2 + 1;
            rehash(new_bucket_count);
        }
    }

    void rehash(size_t new_bucket_count) {
        if (new_bucket_count <= table.size()) return;

        std::vector<std::list< std::pair<K, V> >> new_table(new_bucket_count);
        for (const auto& bucket : table) {
            for (const auto& [key, value] : bucket) {
                size_t index = hasher(key) % new_bucket_count;
                new_table[index].emplace_back(key, value);
            }
        }
        table = std::move(new_table);
    }

public:
    hash_map(size_t initial_bucket_count = 8, double load_factor = 2.0)
        : table(initial_bucket_count), element_count(0), max_load_factor(load_factor) {}

    ~hash_map() { 
        clear(); 
        std::cout << "hash_map deleted" << std::endl;
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        element_count = 0;
        std::cout << "hash_map is cleared" << std::endl;
    }

    void insert(const K& key, const V& value) {
        size_t index = hasher(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        ++element_count;
        rehash_if_needed();
    }

    V& operator[](const K& key) {
        size_t index = hasher(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) return pair.second;
        }
        table[index].emplace_back(key, V{});
        ++element_count;
        rehash_if_needed();
        return table[index].back().second;
    }

    void erase(const K& key) {
        size_t index = hasher(key) % table.size();
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --element_count;
                return;
            }
        }
    }

    size_t size() {
        return element_count;
    }

    double get_load_factor() {
        return max_load_factor;
    }

    void set_load_factor(double factor) {
        max_load_factor = factor;
        rehash_if_needed();
    }

    double load_factor() {
        return 1.0 * element_count / table.size();
    }
};
