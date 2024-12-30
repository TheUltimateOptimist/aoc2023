#include <vector>
#include <string>
#include <unordered_map>
#include "../../util.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

int max_stations = 0;
int max_cost = 0xFFFFFF;
unordered_map<string, vector<pair<string, int>>> paths;

void traverse(const string& from, vector<string> visited, int cost) {
    visited.push_back(from);
    for (const auto& next : paths[from]) {
        if (find(visited.begin(), visited.end(), next.first) == visited.end()) {
            traverse(next.first, visited, cost + next.second);
        }
    }
    if (visited.size() > max_stations || visited.size() == max_stations && cost < max_cost) {
        max_stations = visited.size();
        max_cost = cost;
    }
}

int main(int argc, char** argv) {
    for (const auto& line : split(read(2015, 9, argc), "\n")) {
        vector<string> parts = split(line, " ");
        if (paths.find(parts[0]) == paths.end()) {
            paths[parts[0]] = vector<pair<string, int>>{};
        }
        if (paths.find(parts[2]) == paths.end()) {
            paths[parts[2]] = vector<pair<string, int>>{};
        }
        int distance = atoi(parts[4].c_str());
        paths[parts[0]].push_back(pair<string, int>(parts[2], distance));
        paths[parts[2]].push_back(pair<string, int>(parts[0], distance));
    }
    for (const auto& path : paths) {
        traverse(path.first, vector<string>{}, 0);
    }
    cout << max_cost << endl;
}