#include "../../util.hpp"
#include <vector>
#include <string>

using namespace std;

size_t min_count = 0;
size_t min_container_count = 100;

void find_combinations(vector<int>& containers, int index, int litres, int container_count) {
    if (index >= containers.size()) return;
    for (int i = index; i < containers.size(); i++) {
        if (containers[i] == litres) {
            if (container_count + 1 < min_container_count) {
                min_container_count = container_count + 1;
                min_count = 1;
            }
            else if (container_count + 1 == min_container_count) {
                min_count++;
            }
        }
        else if (containers[i] < litres) {
            find_combinations(containers, i + 1, litres - containers[i], container_count + 1);
        }
    }
}

int main(int argc, char** argv) {
    string input = read(2015, 17, argc);
    vector<int> containers;
    for (auto line : split(input, "\n")) {
        containers.push_back(atoi(line.c_str()));
    }
    find_combinations(containers, 0, 150, 0);
    cout << min_count << endl;
}