#pragma once
#include "Constants.h"
#include <vector>
#include <fstream>

class ContinuousModel {
public:
    ContinuousModel(int numRats);
    void simulate();

private:
    struct Rat {
        real x, y;
        bool aggressive;
        Rat(real xval, real yval, bool aval) : x(xval), y(yval), aggressive(aval) {}
    };

    std::vector<Rat> rats;
    int NRAT, T_MAX;
    const real L, R_MIN, R_MAX, R_STEP;

    void reset();
    void checkNeighbors(real radius);
    double meanAggressivity();
};