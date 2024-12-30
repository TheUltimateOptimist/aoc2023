#include <iostream>
#include <string>
#include <fstream>
#include "../../util.hpp"
#include <unordered_map>
#include <cassert>

typedef enum Operation {
    NOT,
    AND,
    OR, 
    LSHIFT,
    RSHIFT,
    MOVE
} Operation;

using namespace std;

typedef struct {
    vector<string> operands;
    Operation operation;
} Mapping;

unordered_map<string, Operation> operations = {
    {"NOT", Operation::NOT},
    {"AND", Operation::AND},
    {"OR", Operation::OR},
    {"LSHIFT", Operation::LSHIFT},
    {"RSHIFT", Operation::RSHIFT},
    {"MOVE", Operation::MOVE}
};

unordered_map<string, uint16_t> cache;

std::uint16_t evaluate(unordered_map<string, Mapping>& mappings, const string& wire) {
    Mapping& mapping = mappings[wire];
    vector<std::uint16_t> operand_values;
    for (const auto& operand : mapping.operands) {
        if (operand[0] >= '0' && operand[0] <= '9') {
            operand_values.push_back(atoi(operand.c_str()));
        }
        else {
            auto some = cache.find(operand);
            if (some == cache.end()) {
                uint16_t value = evaluate(mappings, operand);
                cache[operand] = value;
                operand_values.push_back(value);
            }
            else {
                operand_values.push_back((*some).second);
            }
        }
    }
    switch (mapping.operation) {
        case Operation::MOVE: {
            return operand_values[0];
        }
        case Operation::NOT: {
            return ~operand_values[0];
        }
        case Operation::AND: {
            return operand_values[0] & operand_values[1];
        }
        case Operation::OR: {
            return operand_values[0] | operand_values[1];
        }
        case Operation::LSHIFT: {
            return operand_values[0] << operand_values[1];
        }
        case Operation::RSHIFT: {
            return operand_values[0] >> operand_values[1];
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    string input = read(2015, 7, argc);
    unordered_map<string, Mapping> mappings;
    for (auto& line : split(input, "\n")) {
        vector<string> leftright = split(line, " -> ");
        vector<string> operands;
        Operation operation;
        vector<string> leftparts = split(leftright[0], " "); 
        assert(leftparts.size() >= 1 && leftparts.size() <= 3);
        if (leftparts.size() == 1) {
            operands.push_back(leftparts[0]);
            operation = Operation::MOVE;
        }
        else if (leftparts.size() == 2) {
            operands.push_back(leftparts[1]);
            operation = Operation::NOT;
        }
        else if (leftparts.size() == 3) {
            operands.push_back(leftparts[0]);
            operands.push_back(leftparts[2]);
            operation = operations[leftparts[1]];
        }
        Mapping mapping;
        mapping.operands = operands;
        mapping.operation = operation;
        mappings[leftright[1]] = mapping;
    }
    uint16_t a = evaluate(mappings, "a");
    Mapping mapping;
    mapping.operands = {to_string(a)};
    mapping.operation = Operation::MOVE;
    mappings["b"] = mapping;
    cache.clear();
    cout << evaluate(mappings, "a") << endl;
    return 0;
}