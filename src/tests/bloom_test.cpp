//
// Created by Rahim Ahmedov on 21.03.23.
//

#include <iostream>
#include "../lsmtree/bloom.h"

int main() {

    BloomFilter<std::string> filter(1000, 5);

    filter.insert("apple");
    filter.insert("banana");
    filter.insert("ananas");

    std::cout << (filter.contains("anana") ? "may contain" : "doesnt contain" ) << std::endl;

    return 0;
}