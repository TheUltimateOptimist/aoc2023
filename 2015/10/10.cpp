#include "../../util.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

string next_str(const string& input) {
    string result;
    int count = 0;
    for (int a = 0; a < input.length(); a++) {
        count++;
        if (a == input.length() - 1 || input[a] != input[a + 1]) {
            result += to_string(count);
            result += input[a];
            count = 0;
        }
    }
    return result;
}

int main(int argc, char** argv) {
    string input = read(2015, 10, argc);
    for (int i = 0; i < 40; i++) {
        input = next_str(input); 
        cout << input << " " << input.length() << endl;
    }
}