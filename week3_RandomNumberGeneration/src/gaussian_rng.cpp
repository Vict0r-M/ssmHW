#include "gaussian_rng.h"
#include <random>
#include <fstream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GaussianRNG::GaussianRNG(int seed) : seed(seed) {}

std::vector<double> GaussianRNG::boxMuller(int length, const std::string& filename) {
    std::mt19937 mt(seed);
    std::uniform_real_distribution<> uDis(0.0, 1.0);
    std::vector<double> sequence(length, 0);
    std::ofstream file(filename);

    for (int i = 0; i < length; i += 2) {
        double u1 = uDis(mt);
        double u2 = uDis(mt);
        double R_sq = -2 * std::log(u1);
        double theta = 2 * M_PI * u2;
        sequence[i] = std::sqrt(R_sq) * std::cos(theta);
        file << sequence[i] << std::endl;
        if (i + 1 < length) {
            sequence[i + 1] = std::sqrt(R_sq) * std::sin(theta);
            file << sequence[i + 1] << std::endl;
        }
    }
    file.close();
    return sequence;
}