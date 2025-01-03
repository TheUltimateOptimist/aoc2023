#include <vector>
#include <string>
#include "../../util.hpp"

using namespace std;

typedef struct Ingredient {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
} Ingredient;

int main(int argc, char** argv) {
    string input = read(2015, 15, argc);
    vector<Ingredient> ingredients;
    for (auto line : split(input, "\n")){
        vector<string> parts = split(line, " ");
        Ingredient ingredient;
        ingredient.capacity = atoi(parts[2].c_str());
        ingredient.durability =  atoi(parts[4].c_str());
        ingredient.flavor = atoi(parts[6].c_str());
        ingredient.texture = atoi(parts[8].c_str());
        ingredient.calories = atoi(parts[10].c_str());
        ingredients.push_back(ingredient);
    }
    int max_score = 0;
    for (int a = 0; a <= 100; a++) {
        for (int b = 0; b <= 100 - a; b++) {
            for (int c = 0; c <= 100 - a - b; c++) {
                int d = 100 - a - b - c;
                int capacity = a*ingredients[0].capacity + b*ingredients[1].capacity + c*ingredients[2].capacity + d*ingredients[3].capacity;
                int durability = a*ingredients[0].durability + b*ingredients[1].durability + c*ingredients[2].durability + d*ingredients[3].durability;
                int flavor = a*ingredients[0].flavor + b*ingredients[1].flavor + c*ingredients[2].flavor + d*ingredients[3].flavor;
                int texture = a*ingredients[0].texture + b*ingredients[1].texture + c*ingredients[2].texture + d*ingredients[3].texture;
                int calories = a*ingredients[0].calories + b*ingredients[1].calories + c*ingredients[2].calories + d*ingredients[3].calories;
                if (capacity > 0 && durability > 0 && flavor > 0 && texture > 0 && capacity*durability*flavor*texture > max_score && calories == 500) {
                    max_score = capacity*durability*flavor*texture;
                }
            }
        }
    }
    cout << max_score << endl;
}