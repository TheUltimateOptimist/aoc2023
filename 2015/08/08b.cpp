#include "../../util.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string input = read(2015, 8, argc);
    int first = 0;
    int second = 0;
    for (const auto& line : split(input, "\n")) {
        second += line.length();
        int add = 4;
        size_t index = 0;
        while ((index = line.find('\\', index)) != string::npos) {
            if (line[index + 1] == 'x') {
                add++;
            }
            else add += 2;
            index += 2;
        }
        first += line.length() + add;
    }
    cout << (first - second) << endl;
}