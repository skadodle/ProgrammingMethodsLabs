#pragma once

#include <vector>
#include <list>
#include <functional>
#include <stdexcept>

template<typename K, typename V, typename Hash = std::hash<K>>
class hash_map {
private:
    std::vector<std::list< std::pair<K, V> >> table;
    size_t elementCount;
    double maxLoadFactor;
    Hash hasher;

    void rehashIfNeeded() {
        if (loadFactor() > maxLoadFactor) {
            size_t newBucketCount = newIncreasedSize();
            rehash(newBucketCount);
        }
    }

    void rehash(size_t newBucketCount) {
        if (newBucketCount <= table.size()) return;

        std::vector<std::list< std::pair<K, V> >> newTable(newBucketCount);
        for (const auto& bucket : table) {
            for (const auto& [key, value] : bucket) {
                size_t index = getIndex(key, newBucketCount);
                newTable[index].emplace_back(key, value);
            }
        }
        table = std::move(newTable);
    }

    size_t getIndex(K key, size_t bucketCount = 0) {
        return hasher(key) % (bucketCount == 0 ? table.size() : bucketCount);
    }
    
    size_t newIncreasedSize() {
        return table.size() * 2 + 1;
    }

public:
    hash_map(size_t initialBucketCount = 8, double loadFactor = 2.0)
        : table(initialBucketCount), elementCount(0), maxLoadFactor(loadFactor) {}

    ~hash_map() { 
        clear(); 
        std::cout << "hash_map deleted" << std::endl;
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        elementCount = 0;
        std::cout << "hash_map is cleared" << std::endl;
    }

    void insert(K key, V value) {
        size_t index = getIndex(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        ++elementCount;
        rehashIfNeeded();
    }

    V& operator[](K key) {
        size_t index = getIndex(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) return pair.second;
        }
        table[index].emplace_back(key, V{});
        ++elementCount;
        rehashIfNeeded();
        return table[index].back().second;
    }

    void erase(K key) {
        size_t index = getIndex(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --elementCount;
                return;
            }
        }
    }

    size_t size() {
        return elementCount;
    }

    double getLoadFactor() {
        return maxLoadFactor;
    }

    void setLoadFactor(double factor) {
        maxLoadFactor = factor;
        rehashIfNeeded();
    }

    double loadFactor() {
        return 1.0 * elementCount / table.size();
    }
};
