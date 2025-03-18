#include "b_tree_map.h"

int main(int argc, char**argv) {
    BTreeMap<int, std::string> btm(3);
    btm.insert(1, "Tom");
    btm.insert(2, "Jerry");
    btm.insert(3, "Dog");
    btm.insert(5, "Girl");
    btm.insert(12, "Jackson");
    btm.insert(41, "Portal");
    btm.insert(24, "Square Pants");
    btm.insert(22, "Patrick");
    btm.insert(18, "Sandy");
    btm.insert(35, "Mr Krabs");
    btm.insert(30, "Plankton");

    btm.print();

    if (btm.empty())
        std::cout << "Empty!";
    else 
        std::cout << "Not empty!";
    std::cout << std::endl;

    std::string val;
    std::cout << (btm.find(11, val) ? "Found" : "Not found") << " is " << val << std::endl;

    /* btm.clear();
    if (btm.empty())
        std::cout << "Empty!";
    else 
        std::cout << "Not empty!";
    std::cout << std::endl; */
}