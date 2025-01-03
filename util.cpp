#include "util.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split(const string& text, const string& delimiter) {
    size_t last = 0; 
    size_t next = 0; 
    vector<string> parts;
    while ((next = text.find(delimiter, last)) != string::npos) {
        parts.push_back( text.substr(last, next-last));
        last = next + delimiter.length(); 
    } 
    parts.push_back(text.substr(last));
    return parts;
}

string read(int year, int day, int argc) {
    string path = "../../../";
    path += to_string(year);
    path += "/";
    if (day < 10) {
        path += "0";
    }
    path += to_string(day);
    if (argc > 1) {
        path += "/test.txt";
    }
    else {
        path += "/input.txt";
    }
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error opening input file with path " << path << std::endl;
    }
    string input;
    getline(file, input, '\0');
    return input;
}

template <typename T>
permutations<T>::permutations(vector<T>& data) : data(data), index(0) {
    perm_count = 1;
    for (int i = 2; i <= data.size(); i++) {
        perm_count *= i;
    }
}

template <typename T>
permutations<T> permutations<T>::begin() {
    return this;
}

template <typename T>
permutations<T> permutations<T>::end() {
    this.index = perm_count;
    return this;
}

template <typename T>
vector<T> permutations<T>::operator*()
{
    vector<T> permutation = data;
    size_t total = perm_count;
    for (int i = 0; i < permutation.size(); i++) {
        size_t with = index / (total / (permutation.size() - i))
    }

}
