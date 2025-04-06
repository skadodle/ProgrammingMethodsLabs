#include <iostream>
#include "hash_map.h"

int main() {
    hash_map<std::string, int> map;

    map.insert("apple", 1);
    map.insert("banana", 2);
    map["cherry"] = 3;

    std::cout << "banana = " << map["banana"] << "\n";
    std::cout << "size = " << map.size() << "\n";

    map.erase("apple");
    std::cout << "After erasing 'apple', size = " << map.size() << "\n";

    std::cout << "Load factor = " << map.loadFactor() << "\n";

    map.setLoadFactor(1.5);
    std::cout << "Updated max load factor = " << map.getLoadFactor() << "\n";

    return 0;
}

