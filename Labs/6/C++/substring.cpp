#include "substring.h"

ssize_t KMP(const std::string& text, const std::string& pattern) {
    std::vector<size_t> border(pattern.length());
    bordersKMP(pattern, border);

    // cout border
    {
        for(auto& el : pattern) {
            std::cout << el << "\t";
        }
        std::cout << std::endl;
        for(auto& el : border) {
            std::cout << el << "\t";
        }
        std::cout << std::endl;
    }

    size_t matched_pos = 0;
    for(size_t current = 0; current < text.length(); current++) {
		while (matched_pos > 0 && pattern[matched_pos] != text[current] )
			matched_pos = border[matched_pos - 1];
			
		if(pattern[matched_pos] == text[current])
			matched_pos++;
			
		if(matched_pos == (pattern.length()) )
			return current - (pattern.length() - 1);
	}

    return -1;
}
void bordersKMP(const std::string& pattern, std::vector<size_t> &border) {
    border[0] = 0;
    for (int i = 1; i < border.size(); ++i) {
        border[i] = compareStrings(pattern.substr(0, i), pattern.substr(1, i));
    }
}
size_t compareStrings(std::string suff, std::string pref) {
    if (suff.empty()) return 0;
    // std::cout << suff << "\t" << pref << std::endl;
    return suff == pref ? suff.length() : 
        compareStrings(suff.substr(0, suff.length() - 1), pref.substr(1));
} 