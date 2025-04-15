#include "substring.h"

int main(int argc, char *argv[]) {
    std::string text = "abbaaababbaababbaabababbabababbababaaabbabbbaba";
    std::string pattern = "abbabababbaba";
    std::cout << KMP(text, pattern) << std::endl;
}