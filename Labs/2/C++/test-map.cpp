#include "map.h"

int main() {
    Map<int, string> myMap;
    
    myMap.insert(1, "one");
    myMap.insert(2, "two");
    myMap.insert(3, "three");
    
    cout << "Find 2: " << (myMap.find(2) ? *myMap.find(2) : "not found") << endl;
    cout << "Contains 3: " << myMap.contains(3) << endl;
    
    myMap[4] = "four";
    cout << "Key 4: " << myMap[4] << endl;
    
    Map<int, string> copyMap = myMap;
    cout << "Copy contains 2: " << copyMap.contains(2) << endl;
    
    myMap.erase(2);
    cout << "After erase 2, contains 2: " << myMap.contains(2) << endl;
    
    myMap.clear();
    cout << "After clear, empty: " << myMap.empty() << endl;
    
    return 0;
}
