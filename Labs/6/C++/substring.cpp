#include "substring.h"

std::vector<int> KMP(const std::string& text, const std::string& pattern) {
    if (text.length() < pattern.length())
        return std::vector<int>();
    if (text.length() == pattern.length())
        return std::vector<int>{0};

    std::vector<int> border(pattern.length());
    std::vector<int> result;
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

    int matched_pos = 0;
    for(int current = 0; current < text.length(); current++) {
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
void bordersKMP(const std::string& pattern, std::vector<int> &border) {
    border[0] = 0;
    for (int i = 1; i < border.size(); ++i) {
        border[i] = compareStrings(pattern.substr(0, i), pattern.substr(1, i));
    }
}
int compareStrings(std::string suff, std::string pref) {
    if (suff.empty()) return 0;
    // std::cout << suff << "\t" << pref << std::endl;
    return suff == pref ? suff.length() : 
        compareStrings(suff.substr(0, suff.length() - 1), pref.substr(1));
} 

std::vector<int> BoyerMoore(const std::string& text, const std::string& pattern) {
    if (text.length() < pattern.length())
        return std::vector<int>();
    if (text.length() == pattern.length())
        return std::vector<int>{0};

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

std::vector<int> RabinKarp(const std::string& text, const std::string& pattern) {
    if (text.length() < pattern.length())
        return std::vector<int>();
    if (text.length() == pattern.length())
        return std::vector<int>{0};

    std::vector<int> result;

    const int patternHash = calculateHash(pattern);
    const int length = pattern.length();

    int x_length = 1;
    for (int i = 0; i < length - 1; i++) {
        x_length = (x_length * x) % q;
    }

    int textSubstrHash = calculateHash(text.substr(0, length));

    int i = 0;
    while(true) {
        if (textSubstrHash == patternHash) {
            if (pattern == text.substr(i, length)) {
                result.push_back(i);
            }
        }

        if (text.length() <= i + length)
            break;

        textSubstrHash = ( (int) (textSubstrHash - (text[i] * x_length)) * x + text[i + length]) % q;
        ++i;
    }

    return result;
}
int calculateHash(const std::string& text) {
    return schemeGorner(text) % q;
}
int  schemeGorner(const std::string& text) {
    int result = 0;
    for (int i : text) {
        result = ((result * x) % q + (int) i) % q;
    }
    return result;
}