#include "../../util.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct Reindeer {
    int speed;
    int speed_duration;
    int rest_duration;
} Reindeer;

int main(int argc, char** argv) {
    string text = read(2015, 14, argc);
    vector<Reindeer> reindeers;
    for (auto line : split(text, "\n")) {
        vector<string> parts = split(line, " ");
        Reindeer reindeer;
        reindeer.speed = atoi(parts[3].c_str());
        reindeer.speed_duration = atoi(parts[6].c_str());
        reindeer.rest_duration = atoi(parts[13].c_str());
        reindeers.push_back(reindeer);
    }
    int max_distance = 0;
    for (Reindeer reindeer : reindeers) {
        int distance = 0;
        int time = 2503;
        while (time > 0) {
            cout << distance << endl;
            if (reindeer.speed_duration <= time) {
                distance += reindeer.speed*reindeer.speed_duration;
            }
            else {
                distance += reindeer.speed*time;
            }
            time -= reindeer.speed_duration;
            time -= reindeer.rest_duration;
        }
        if (distance > max_distance) {
            max_distance = distance;
        }
    }
    cout << max_distance << endl;
}