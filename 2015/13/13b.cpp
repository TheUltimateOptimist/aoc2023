#include "../../util.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <set>

using namespace std;

unordered_map<string, int> mappings;
set<string> people;

int main(int argc, char** argv) {
    string text = read(2015, 13, argc);
    for (auto line : split(text, "\n")) {
        vector<string> parts = split(line.erase(line.size() - 1), " ");
        people.insert(parts[0]);
        people.insert(parts[10]);
        string key = parts[0] + parts[10];
        if (parts[2] == "gain") {
            mappings[key] = atoi(parts[3].c_str());
        }
        else {
            mappings[key] = atoi(parts[3].c_str())*(-1);
        }
    }
    vector<string> people_vec(people.begin(), people.end());
    people_vec.push_back("me");
    int max = 0;
    for (auto perm : permutations<string>(people_vec)) {
        perm.push_back(perm[0]);
        int total = 0;
        for (int i = 0; i < perm.size() - 1; i++) {
            if (mappings.find(perm[i] + perm[i + 1]) != mappings.end()) {
                total += mappings[perm[i] + perm[i + 1]];
            }
        }
        for (int i = perm.size() - 1; i > 0; i--) {
            if (mappings.find(perm[i] + perm[i - 1]) != mappings.end()) {
                total += mappings[perm[i] + perm[i - 1]];
            }
        }
        if (total > max) {
            max = total;
        }
    }
    cout << max << endl;
}