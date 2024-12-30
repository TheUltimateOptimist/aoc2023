#include "../../util.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

size_t to_number(const string& password) {
    size_t result = 0;
    size_t multiplier = 1;
    for (int i = password.length() - 1; i >= 0; i--) {
        result += (password[i] - 'a')*multiplier;
        multiplier = multiplier*26;
    }
    return result;
}

string to_password(size_t number) {
    string password = "aaaaaaaa";
    int index = 7;
    while (number > 0) {
        password[index] = 'a' + number % 26;
        number = number / 26;
        index--;
    }
    return password;
}

bool has_increasing_straight(const string& password) {
    for (int i = 0; i < password.length() - 2; i++) {
        if (password[i] == (password[i + 1] - 1) && password[i + 1] == (password[i + 2] - 1)) {
            return true;
        }
    } 
    return false;
}

bool has_no_iol(const string& password) {
    for (int i = 0; i < password.length(); i++) {
        if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l') {
            return false;
        }
    }
    return true;
}

bool has_two_pairs(const string& password) {
    string pairs;
    for (int i = 0; i < password.length() - 1; i++) {
        if (password[i] == password[i + 1] && pairs.length() == 0) {
            pairs += password[i];
        }
        else if (password[i] == password[i + 1] && password[i] != pairs[0]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    string input = read(2015, 11, argc);
    while (!(has_increasing_straight(input) && has_no_iol(input) && has_two_pairs(input))) {
        input = to_password(to_number(input) + 1);
    }
    input = to_password(to_number(input) + 1);
    while (!(has_increasing_straight(input) && has_no_iol(input) && has_two_pairs(input))) {
        input = to_password(to_number(input) + 1);
    }
    cout << input << endl;
}