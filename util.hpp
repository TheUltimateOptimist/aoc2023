#ifndef UTIL_HPP
#define UTIL_HPP
#include <vector>
#include <string>
std::vector<std::string> split(const std::string& text, const std::string& delimiter);
std::string read(int year, int day, int argc);
#endif