#include "substring.h"

std::vector<size_t> KMP(const std::string& text, const std::string& pattern) {
    std::vector<size_t> border(pattern.length());
    std::vector<size_t> result;
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
			
		if(matched_pos == (pattern.length())) {
			result.push_back(current - (pattern.length() - 1));
            matched_pos = 0;
        }
	}

    return result;
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

std::vector<int> BoyerMoore(const std::string& text, const std::string& pattern) {
    size_t n = text.length();
    size_t m = pattern.length();
    std::vector<int> result;

    std::vector<int> stop(256, -1);
    badCharacterRule(pattern, stop);

    std::vector<int> suff(m + 1, m);
    goodSuffixRule(pattern, suff);

    for (size_t i = 0; i <= n - m + 1;) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }
        int delta_stop;
        
        if (j == -1) {
            result.push_back(i);
            delta_stop = 1;
        }
        else {
            delta_stop = j - stop[text[i + j]];
        }

        i += std::max(delta_stop, suff[m - j - 1]);
    }

    return result;
}
void badCharacterRule(const std::string& pattern, std::vector<int>& stop) {
    for (int i = pattern.length() - 2; i >= 0; i--) {
        if (stop[pattern[i]] == -1) {
            stop[pattern[i]] = i;
        }
    }
}
void goodSuffixRule(const std::string& pattern, std::vector<int>& suff) {
    suff[0] = 1;
    size_t m = pattern.length();

    bool flag = false;

    for (size_t len_suff = 1; len_suff <= m; len_suff++){
        for (size_t offset = suff[len_suff - 1]; offset <= m; offset++){
            for (int i = 1; i <= std::min(len_suff, m - offset); i++) {
                if (pattern[m - i] != pattern[m - offset - i]){
                    flag = true;
                    break;
                }
            }
            if (flag) {
                flag = false;
                continue;
            }
            suff[len_suff] = offset;
            break;
        }
    }
}