#include "../../util.hpp"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main(int argc, char** argv) {
    unordered_map<string, int> expected = {
        {"children:", 3},
        {"cats:", 7},
        {"samoyeds:", 2},
        {"pomeranians:", 3},
        {"akitas:", 0},
        {"vizslas:", 0},
        {"goldfish:", 5},
        {"trees:", 3},
        {"cars:", 2},
        {"perfumes:", 1}
    };
    string input = read(2015, 16, argc);
    for (auto line : split(input, "\n")) {
        vector<string> parts = split(line, " ");
        for (int i = 2; i <= 6; i += 2) {
            if (expected[parts[i]] != atoi(parts[i + 1].c_str())) {
                break;
            }
            if (i == 6) {
                cout << line << endl;
            }
        }
    }
}