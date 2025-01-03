#ifndef UTIL_HPP
#define UTIL_HPP
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& text, const std::string& delimiter);
std::string read(int year, int day, int argc);

template <typename T>
class permutations {
public:
    permutations<T>(std::vector<T>& data);
    permutations<T> begin();
    permutations<T> end();
    std::vector<T> operator*();
    bool operator!=(const permutations<T>& other);
    permutations<T>& operator++();
private:
    size_t index;
    size_t perm_count;
    std::vector<T>& data;
    void populate_permutation(std::vector<T>& perm, size_t remaining);
};
#endif