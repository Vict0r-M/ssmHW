#pragma once
#include "Constants.h"
#include <vector>
#include <fstream>

class DiscreteModel {
public:
    DiscreteModel(int gridSize, int maxRats);
    void simulate();

private:
    struct Rat {
        int x, y, state;
        Rat(int xval, int yval, int stateVal) : x(xval), y(yval), state(stateVal) {}
    };

    std::vector<std::vector<int>> room;
    std::vector<Rat> rats;
    int SIZE, NRAT, T_MAX;
    const int EMPTY, CALM, AGGRESSIVE;

    void reset();
    void checkNeighbors();
    double meanAggressivity();
};