#include "../../util.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string input = read(2015, 8, argc);
    int first = 0;
    int second = 0;
    for (const auto& line : split(input, "\n")) {
        first += line.length();
        int subtract = 2;
        size_t index = 0;
        while ((index = line.find('\\', index)) != string::npos) {
            if (line[index + 1] == 'x') {
                subtract += 3;
            }
            else subtract++;
            index += 2;
        }
        second += line.length() - subtract;
    }
    cout << (first - second) << endl;
}