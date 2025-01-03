#include "../../util.hpp"
#include <vector>
#include <string>

using namespace std;

size_t count = 0;

void find_combinations(vector<int>& containers, int index, int litres) {
    if (index >= containers.size()) return;
    for (int i = index; i < containers.size(); i++) {
        if (containers[i] == litres) {
            count++;
        }
        else if (containers[i] < litres) {
            find_combinations(containers, i + 1, litres - containers[i]);
        }
    }
}

int main(int argc, char** argv) {
    string input = read(2015, 17, argc);
    vector<int> containers;
    for (auto line : split(input, "\n")) {
        containers.push_back(atoi(line.c_str()));
    }
    find_combinations(containers, 0, 150);
    cout << count << endl;
}