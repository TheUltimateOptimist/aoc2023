#include "../../util.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string text = read(2015, 12, argc);
    string number;
    int total = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == '-' || text[i] >= '0' && text[i] <= '9') {
            number += text[i];
        }
        else if (number.length() > 0) {
            total += atoi(number.c_str());
            number.clear();
        }
    }
    cout << total << endl;
}