//
// Created by Rahim Ahmedov on 20.03.23.
//

#ifndef PROJECTX_BLOOM_H
#define PROJECTX_BLOOM_H

#include <bitset>
#include <functional>

template <typename  E>
class BloomFilter {
public:
    BloomFilter(size_t size, size_t num_hashes)
            : m_size(size), m_num_hashes(num_hashes), m_bitset(size) {}

    void insert(const E& value) {
        for (size_t i = 0; i < m_num_hashes; ++i)
            m_bitset[hash(value, i) % m_size] = 1;
    }

    bool contains(const E& value) const {
        for (size_t i = 0; i < m_num_hashes; ++i)
            if (m_bitset[hash(value, i) % m_size] == 0)
                return false;
        return true;
    }

private:
    size_t hash(const E& value, size_t i) const {
        std::hash<E> hash_fn;
        return hash_fn(value) * (i + 1);
    }
    size_t m_size;
    size_t m_num_hashes;
    std::bitset<1000000> m_bitset; // Adjust the size as needed
};

#endif //PROJECTX_BLOOM_H
