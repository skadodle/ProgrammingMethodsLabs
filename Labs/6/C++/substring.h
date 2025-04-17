#pragma once 

#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>

#define q 2147483647
#define x 31

std::vector<int> KMP(const std::string& text, const std::string& pattern);
void bordersKMP(const std::string& pattern, std::vector<int> &border);
int compareStrings(std::string suff, std::string pref);

std::vector<int> BoyerMoore(const std::string& text, const std::string& pattern);
void badCharacterRule(const std::string& pattern, std::vector<int>& stop);
void goodSuffixRule(const std::string& pattern, std::vector<int>& suff);

std::vector<int> RabinKarp(const std::string& text, const std::string& pattern);
int calculateHash(const std::string& text);
int schemeGorner(const std::string& text);