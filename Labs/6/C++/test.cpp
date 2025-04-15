#include "substring.h"

int main(int argc, char *argv[]) {
    std::string text = "abbaaababbaababbaabababbabababbababaaabbabbbabbabababbabaaba";
    std::string pattern = "abbabababbaba";
    for (auto& el : KMP(text, pattern)) {    
        std::cout << el << std::endl;
    }
    for (auto& el : BoyerMoore(text, pattern)) {    
        std::cout << el << std::endl;
    }
}