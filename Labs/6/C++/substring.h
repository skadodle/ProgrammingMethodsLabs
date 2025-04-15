#pragma once 

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<size_t> KMP(const std::string& text, const std::string& pattern);
void bordersKMP(const std::string& pattern, std::vector<size_t> &border);
size_t compareStrings(std::string suff, std::string pref);

std::vector<int> BoyerMoore(const std::string& text, const std::string& pattern);
void badCharacterRule(const std::string& pattern, std::vector<int>& stop);
void goodSuffixRule(const std::string& pattern, std::vector<int>& suff);