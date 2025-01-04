#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "util.hpp"
//#include "util.hpp"

using namespace std;

template <typename T>
permutations<T>::permutations(const vector<T>& data) : data(data), index(0) {
    perm_count = 1;
    for (int i = 2; i <= data.size(); i++) {
        perm_count *= i;
    }
}

template <typename T>
permutations<T> permutations<T>::begin() {
    permutations<T> copy = *this;
    copy.index = 0;
    return copy;
}

template <typename T>
permutations<T> permutations<T>::end() {
    permutations<T> copy = *this;
    copy.index = perm_count;
    return copy;
}

template<typename T>
vector<T> permutations<T>::operator[](size_t index) {
    size_t total = perm_count;
    vector<T> permutation = data;
    for (int i = 0; i < permutation.size() - 1; i++) {
        total = total / (permutation.size() - i);
        size_t switch_with = index / total + i;
        if (switch_with != i) {
            T intermediate = permutation[i];
            permutation[i] = permutation[switch_with];
            permutation[switch_with] = intermediate;
        };
        index = index - (switch_with - i)*total;
    }
    return permutation;
}

template <typename T>
bool permutations<T>::operator!=(const permutations<T> &other)
{
    return other.index != index;
}

template <typename T>
vector<T> permutations<T>::operator*()
{
    return (*this)[index];
}

template <typename T>
permutations<T> &permutations<T>::operator++()
{
    index++;
    return *this;
}

template <typename T>
grid<T>::grid(vector<vector<T>> data) : data(data), dims(coords(data.size(), data[0].size())) {}

template <typename T>
T& grid<T>::operator[](coords at) {
    return data[at.a][at.b];
}

template <typename T>
grid<char> grid<T>::from_str(const string &text) {
    vector<string> parts = split(text, "\n");
    vector<vector<char>> chars;
    for (auto& part : parts) {
        chars.push_back(vector<char>(part.begin(), part.end()));
    }
    return grid<char>(chars);
}

template <typename T>
griditerator<T> grid<T>::begin() {
    return griditerator<T>(*this, 0, 0);
}

template <typename T>
griditerator<T> grid<T>::end() {
    return griditerator<T>(*this, dims.a, 0);
}

template <typename T>
griditerator<T>::griditerator(grid<T> &grid_ref, size_t r, size_t c) : grid_ref(grid_ref), r(r), c(c) {}

template <typename T>
bool griditerator<T>::operator!=(const griditerator<T>& other) {
    return r != other.r || c != other.c;
}

template <typename T>
pair<coords, T&> griditerator<T>::operator*() {
    return pair<coords, T&>(coords(r, c), grid_ref[coords(r, c)]);
}

template <typename T>
griditerator<T>& griditerator<T>::operator++() {
    if (c < grid_ref.dims.b - 1) {
        c++;
    }
    else {
        r++;
        c = 0;
    }
    return *this;
}