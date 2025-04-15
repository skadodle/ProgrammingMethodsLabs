#pragma once 

#include <iostream>
#include <string>
#include <vector>

ssize_t KMP(const std::string& text, const std::string& pattern);
void bordersKMP(const std::string& pattern, std::vector<size_t> &border);
size_t compareStrings(std::string suff, std::string pref);