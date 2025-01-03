#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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
