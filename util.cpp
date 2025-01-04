#include <vector>
#include <string>
#include "util.hpp"

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

coords::coords(int a, int b) : a(a), b(b){}
bool coords::operator==(const coords& other) {
    return other.a == a && other.b == b;
}
bool coords::operator!=(const coords& other) {
    return *this == other;
}
int coords::operator[](size_t index) {
    if (index < 0 || index > 1) {
        throw std::out_of_range("");
    }
    return index == 0 ? a : b;
}
bool coords::in(const coords& other) {
    return a >= 0 && b >= 0 and a < other.a && b < other.b;
}

coords dirs::none = coords(0, 0);
coords dirs::up = coords(-1, 0);
coords dirs::right = coords(0, 1);
coords dirs::down = coords(1, 0);
coords dirs::left = coords(0, -1);
coords dirs::lup = coords(-1, -1);
coords dirs::rup = coords(-1, 1);
coords dirs::ldown = coords(1, -1);
coords dirs::rdown = coords(1, 1);
vector<coords> dirs::diagonal = vector<coords>{dirs::lup, dirs::rup, dirs::rdown, dirs::ldown};
vector<coords> dirs::straight = vector<coords>{dirs::up, dirs::right, dirs::down, dirs::left};
vector<coords> dirs::diagonaln = vector<coords>{dirs::none, dirs::lup, dirs::rup, dirs::rdown, dirs::ldown};
vector<coords> dirs::straightn = vector<coords>{dirs::none, dirs::up, dirs::right, dirs::down, dirs::left};
vector<coords> dirs::all = vector<coords>{dirs::up, dirs::rup, dirs::right, dirs::rdown, dirs::down, dirs::ldown, dirs::left, dirs::lup};
vector<coords> dirs::alln = vector<coords>{dirs::none, dirs::up, dirs::rup, dirs::right, dirs::rdown, dirs::down, dirs::ldown, dirs::left, dirs::lup};