#include <vector>
#include <string>
#include <iostream>
#include "util.hpp"

int main() {
    std::vector<int> numbers = {1,2,3, 4};
    for (auto permutation : permutations<int>(numbers)) {
        for (int i = 0; i < permutation.size(); i++) {
            std::cout << permutation[i] << ",";
        }
        std::cout << std::endl;
    }
}