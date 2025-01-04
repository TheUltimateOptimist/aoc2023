#ifndef UTIL_HPP
#define UTIL_HPP
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& text, const std::string& delimiter);
std::string read(int year, int day, int argc);

class coords {
public:
    coords(int a, int b);
    int a;
    int b;
    bool operator==(const coords& other);
    bool operator!=(const coords& other);
    int operator[](size_t index);
    bool in(const coords& other);
};

inline coords operator+(const coords& lhs, const coords& rhs) {
    return coords(lhs.a + rhs.a, lhs.b + rhs.b);
}
inline coords operator-(const coords& lhs, const coords& rhs) {
    return coords(lhs.a - rhs.a, lhs.b - rhs.b);
}
inline coords operator*(const coords& lhs, int rhs) {
    return coords(lhs.a*rhs, lhs.b*rhs);
}
inline coords operator*(int lhs, const coords& rhs) {
    return coords(rhs.a*lhs, rhs.b*lhs);
}

class dirs {
public:
    static coords none;
    static coords up;
    static coords right;
    static coords down;
    static coords left;
    static coords lup;
    static coords rup;
    static coords ldown;
    static coords rdown;

    static std::vector<coords> diagonal;
    static std::vector<coords> straight;
    static std::vector<coords> diagonaln;
    static std::vector<coords> straightn;
    static std::vector<coords> all;
    static std::vector<coords> alln;
};

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

template <typename T>
class griditerator;

template <typename T>
class grid {
public:
    grid<T>(std::vector<std::vector<T>> data);
    T& operator[](coords at);
    griditerator<T> begin();
    griditerator<T> end();
    coords dims;
    static grid<char> from_str(const std::string& text);
private:
    std::vector<std::vector<T>> data;
};

template <typename T>
class griditerator {
public:
    griditerator<T>(grid<T>& grid_ref, size_t r, size_t c);
    bool operator!=(const griditerator<T>& other);
    std::pair<coords, T&> operator*();
    griditerator<T>& operator++();
private:
    grid<T>& grid_ref;
    size_t r;
    size_t c;
};

#include "util.tcc"

#endif