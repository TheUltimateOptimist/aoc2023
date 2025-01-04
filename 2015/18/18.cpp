#include "../../util.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    string input = read(2015, 18, argc);
    grid<char> gr = grid<char>::from_str(input);
    for (int i = 0; i < 100; i++) {
        grid<char> new_gr = gr;
        for (auto pair : gr) {
            int on_count = 0;
            for (coords dir : dirs::all) {
                if ((pair.first + dir).in(gr.dims) && gr[pair.first + dir] == '#') {
                    on_count++;
                }
            }
            if (pair.second == '#' && (on_count < 2 || on_count > 3)) {
                new_gr[pair.first] = '.';
            }
            if (pair.second == '.' && on_count == 3) {
                new_gr[pair.first] = '#';
            }
        }
        gr = new_gr;
    }
    int on_count = 0;
    for (auto pair : gr) {
        if (pair.second == '#') {
            on_count++;
        }
    }
    cout << on_count << endl;
}