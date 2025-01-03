#ifndef UTIL_HPP
#define UTIL_HPP
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& text, const std::string& delimiter);
std::string read(int year, int day, int argc);

template <typename T>
class permutations {
public:
    permutations<T>(const std::vector<T>& data);
    permutations<T> begin();
    permutations<T> end();
    std::vector<T> operator[](size_t index);
    bool operator!=(const permutations<T>& other);
    std::vector<T> operator*();
    permutations<T>& operator++();
private:
    size_t index;
    size_t perm_count;
    const std::vector<T>& data;
};
#include "util.tcc"

#endif