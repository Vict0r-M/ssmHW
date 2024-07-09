#include "distribution_generators.h"
#include <random>
#include <fstream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

DistributionGenerators::DistributionGenerators(int seed) : seed(seed) {}

double fc(double x, double p) {
    return x * x * x - 3 * x + 4 * p - 2;
}

double dfc(double x, double p) {
    return 3 * x * x - 3;
}

double fd(double x, double p) {
    return 2.0 * M_PI * p - 2.0 * (std::sqrt(1.0 - x * x) * x + std::asin(x)) - M_PI;
}

double dfd(double x, double p) {
    return -4.0 * std::sqrt(1.0 - x * x);
}

double DistributionGenerators::newtonMethod(double x, double p, double (*func)(double, double), double (*derivFunc)(double, double)) {
    double h = func(x, p) / derivFunc(x, p);
    while (std::abs(h) >= 1E-4) {
        h = func(x, p) / derivFunc(x, p);
        x = x - h;
    }
    return x;
}

std::vector<double> DistributionGenerators::generateX2_01(int length, const std::string& filename) {
    std::mt19937 mt(seed);
    std::uniform_real_distribution<> uDis(0.0, 1.0);
    std::vector<double> sequence(length, 0);
    std::ofstream file(filename);

    for (int i = 0; i < length; ++i) {
        double x = uDis(mt);
        sequence[i] = std::pow(x, 1.0 / 3.0);
        file << sequence[i] << std::endl;
    }
    file.close();
    return sequence;
}

std::vector<double> DistributionGenerators::generateX2_12(int length, const std::string& filename) {
    std::mt19937 mt(seed);
    std::uniform_real_distribution<> uDis(0.0, 1.0);
    std::vector<double> sequence(length, 0);
    std::ofstream file(filename);

    for (int i = 0; i < length; ++i) {
        double x = uDis(mt);
        sequence[i] = std::pow((7.0 * x + 1.0), 1.0 / 3.0);
        file << sequence[i] << std::endl;
    }
    file.close();
    return sequence;
}

std::vector<double> DistributionGenerators::generate1MinusX2(int length, const std::string& filename) {
    std::mt19937 mt(seed);
    std::uniform_real_distribution<> uDis(0.0, 1.0);
    std::vector<double> sequence(length, 0);
    std::ofstream file(filename);

    for (int i = 0; i < length; ++i) {
        double x = uDis(mt);
        sequence[i] = newtonMethod(0, x, fc, dfc);
        file << sequence[i] << std::endl;
    }
    file.close();
    return sequence;
}

std::vector<double> DistributionGenerators::generateSemiCircular(int length, const std::string& filename) {
    std::mt19937 mt(seed);
    std::uniform_real_distribution<> uDis(0.0, 1.0);
    std::vector<double> sequence(length, 0);
    std::ofstream file(filename);

    for (int i = 0; i < length; ++i) {
        double x = uDis(mt);
        sequence[i] = newtonMethod(0, x, fd, dfd);
        file << sequence[i] << std::endl;
    }
    file.close();
    return sequence;
}