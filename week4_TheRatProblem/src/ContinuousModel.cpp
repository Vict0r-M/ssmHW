#define _USE_MATH_DEFINES
#include "ContinuousModel.h"
#include <cmath>
#include <cstdlib>

ContinuousModel::ContinuousModel(int numRats)
    : NRAT(numRats), T_MAX(100), L(1.0), R_MIN(0.0001), R_MAX(0.035), R_STEP(0.001) {
    rats.reserve(NRAT);
    for (int i = 0; i < NRAT; i++) {
        rats.emplace_back(0, 0, false);
    }
}

void ContinuousModel::reset() {
    for (auto& rat : rats) {
        rat.x = rand() / (RAND_MAX + 1.0);
        rat.y = rand() / (RAND_MAX + 1.0);
    }
}

void ContinuousModel::checkNeighbors(real radius) {
    double radiusSquared = radius * radius;
    for (auto& rat : rats) {
        bool alone = true;
        for (const auto& other : rats) {
            if (&rat != &other &&
                (rat.x - other.x) * (rat.x - other.x) + (rat.y - other.y) * (rat.y - other.y) < radiusSquared) {
                alone = false;
                if (other.aggressive) {
                    rat.aggressive = true;
                    break;
                }
            }
        }
        if (alone) rat.aggressive = false;
        if (rand() / (RAND_MAX + 1.0) < PROB_SPONTANEOUS) rat.aggressive = true;
    }
}

double ContinuousModel::meanAggressivity() {
    double sum = 0;
    for (const auto& rat : rats) {
        sum += rat.aggressive;
    }
    return sum / rats.size();
}

void ContinuousModel::simulate() {
    std::ofstream f("output/outfile_continuous.txt");
    for (real radius = R_MIN; radius <= R_MAX; radius += R_STEP) {
        for (int t = 0; t < T_MAX; t++) {
            reset();
            checkNeighbors(radius);
        }
        double g = M_PI * radius * radius / (L * L);
        f << NRAT * g << "\t" << meanAggressivity() << "\t"
          << 1.0 - 1.0 / (g * NRAT) * exp(-g * (NRAT - 1)) << std::endl;
    }
    f.close();
}