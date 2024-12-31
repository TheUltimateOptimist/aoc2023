#include "../../util.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int i = 0;

int get_total(const string& text) {
    int total = 0;
    int multiplier = 1;
    string number;
    while(i < text.length()) {
        if (text[i] == '-' || text[i] >= '0' && text[i] <= '9') {
            number += text[i];
            i++;
            continue;
        }
        else if (number.length() > 0) {
            total += atoi(number.c_str());
            number.clear();
        }
        if (text[i] == '{') {
            i++;
            total += get_total(text);
        }
        else if (text[i] == '}') {
            i++;
            return total*multiplier;
        }
        else if (text[i] == ':' && text[i + 1] == '"' && text[i + 2] == 'r') {
            multiplier = 0;
            i++;
        }
        else {
            i++;
        }
    }
    return total*multiplier;
}

int main(int argc, char** argv) {
    string text = read(2015, 12, argc);
    cout << get_total(text) << endl;
}