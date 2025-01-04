#include "../../util.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    string input = read(2015, 18, argc);
    grid<char> gr = grid<char>::from_str(input);
    gr[coords(0, 0)] = '#';
    gr[coords(0, gr.dims.b - 1)] = '#';
    gr[coords(gr.dims.a - 1, 0)] = '#';
    gr[coords(gr.dims.a - 1, gr.dims.b - 1)] = '#';
    for (int i = 0; i < 100; i++) {
        grid<char> new_gr = gr;
        for (auto pair : gr) {
            if (pair.first == coords(0, 0) || pair.first == coords(0, gr.dims.b - 1) || pair.first == coords(gr.dims.a - 1, 0) || pair.first == coords(gr.dims.a - 1, gr.dims.b - 1)) {
                continue;
            }
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