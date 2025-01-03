#include "../../util.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct Reindeer {
    int speed;
    int speed_duration;
    int rest_duration;
    int distance;
    int time_left;
    int points;
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
        reindeer.distance = 0;
        reindeer.time_left = reindeer.speed_duration;
        reindeer.points = 0;
        reindeers.push_back(reindeer);
    }
    for (int i = 0; i < 2503; i++) {
        for (Reindeer& reindeer : reindeers) {
            if (reindeer.time_left >= 1) {
                reindeer.distance += reindeer.speed;
            }
            if (reindeer.time_left == 1) {
                reindeer.time_left = -reindeer.rest_duration;
            }
            else if (reindeer.time_left == -1) {
                reindeer.time_left = reindeer.speed_duration;
            }
            else if (reindeer.time_left > 1) {
                reindeer.time_left--;
            }
            else if (reindeer.time_left < -1) {
                reindeer.time_left++;
            }
        }
        int max_distance = -1;
        for (Reindeer& reindeer : reindeers) {
            if (reindeer.distance > max_distance) {
                max_distance = reindeer.distance;
            }
        }
        for (Reindeer& reindeer : reindeers) {
            if (reindeer.distance == max_distance) {
                reindeer.points++;
            }
        }
    }
    int max_points = 0;
    for (Reindeer& reindeer : reindeers) {
        if (reindeer.points > max_points) {
            max_points = reindeer.points;
        } 
    }
    cout << max_points << endl;
}