#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>
#include "linear_congruential_rng.h"
#include "gaussian_rng.h"
#include "correlation_tests.h"
#include "distribution_generators.h"

#define printf(...) (fprintf(stdout, __VA_ARGS__))

const int N = 100000;
const int CORR_MAX = 100;
const int GRIDSIZE = 10000;
const int EXPERIMENTS = 1000;
const int TRIES = 100000;
const int DIST_SIZE = 1000000;

int main() {
    auto seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937 mt(seed);
    std::uniform_real_distribution<> uDis(0.0, 1.0);
    std::uniform_int_distribution<> uiDis(0, GRIDSIZE - 1);
    std::vector<double> uniform(N, 0);

    // Return-map test
    printf("2. Output of the built-in RNG written to return-map.txt; return-map given in plotting.ipynb\n");
    std::ofstream f2("output/return-map.txt");
    for (int i = 0; i < N; ++i) {
        uniform[i] = uDis(mt);
        f2 << uniform[i] << std::endl;
    }
    f2.close();

    // Pearson correlation test
    printf("\n3. Pearson correlation of a built-in RNG (Mersenne Twister)\n");
    std::ofstream f3("output/pearson.txt");
    for (int c = 1; c <= CORR_MAX; ++c) {
        double p = pearsonCorrelation(uniform, c);
        printf("Pearson correlation of order %d: %f\n", c, p);
        f3 << c << "\t" << p << std::endl;
    }
    f3.close();
    printf("Output written to pearson.txt\n");

    // Linear Congruential RNG
    LinearCongruentialRNG lcg1(16598013, 12820163, pow(2, 24), 1);
    printf("\n4. Output of the LCG written to lcg_values.txt\n");
    lcg1.generateSequence(100000, "output/lcg_values.txt");

    // LCG parameters effect on period
    printf("\n5. a) Effect of the LCG parameters on the period\n");
    LinearCongruentialRNG lcgGlibc(1103515245, 12345, pow(2, 31), 17);
    int period1 = lcgGlibc.checkPeriod(100000);
    printf("Period (glibc): %d\n", period1);

    LinearCongruentialRNG lcgRandu(8121, 0, pow(2, 31), 17);
    int period2 = lcgRandu.checkPeriod(100000);
    printf("Period (RANDU): %d\n", period2);

    LinearCongruentialRNG lcgRandom0(65539, 28411, pow(2, 3) * pow(7, 5), 17);
    int period3 = lcgRandom0.checkPeriod(100000);
    printf("Period (random0): %d\n", period3);

    LinearCongruentialRNG lcgZx81(75, 74, pow(2, 16) + 1, 17);
    int period4 = lcgZx81.checkPeriod(100000);
    printf("Period (ZX81): %d\n", period4);

    // LCG return-map and correlation
    printf("\n5. b) Effect of the LCG parameters on the return-map: output written to glibc.txt, randu.txt, random0.txt, zx81.txt; return-map given in plotting.ipynb\n");
    lcgGlibc.generateSequence(N, "output/glibc.txt");
    lcgRandu.generateSequence(N, "output/randu.txt");
    lcgRandom0.generateSequence(N, "output/random0.txt");
    lcgZx81.generateSequence(N, "output/zx81.txt");

    printf("\n5. c) Effect of the LCG parameters on the correlation: output written to lcg_pearson.txt, analyzed in plotting.ipynb\n");
    std::ofstream f5("output/lcg_pearson.txt");
    for (int c = 1; c <= CORR_MAX; ++c) {
        f5 << c << "\t" << pearsonCorrelation(lcgGlibc.generateSequence(N, ""), c) << "\t"
           << pearsonCorrelation(lcgRandu.generateSequence(N, ""), c) << "\t"
           << pearsonCorrelation(lcgRandom0.generateSequence(N, ""), c) << "\t"
           << pearsonCorrelation(lcgZx81.generateSequence(N, ""), c) << std::endl;
    }
    f5.close();

    // Exponential decay test
    printf("\n6. Output written to exponential.txt, plotted in plotting.ipynb\n");
    std::ofstream f6("output/exponential.txt");
    std::vector<bool> grid(GRIDSIZE, false);
    std::vector<int> available(int(TRIES / 100), 0);
    for (int e = 0; e < EXPERIMENTS; ++e) {
        int a = GRIDSIZE;
        for (int i = 0; i < TRIES; ++i) {
            int t = uiDis(mt);
            if (!grid[t]) {
                grid[t] = true;
                --a;
            }
            if (i % 100 == 0) {
                available[i / 100] += a;
            }
        }
        std::fill(grid.begin(), grid.end(), false);
    }
    for (int i = 0; i < int(TRIES / 100); ++i) {
        f6 << i * 100 << "\t" << double(available[i]) / EXPERIMENTS << std::endl;
    }
    f6.close();

    // Distribution generators
    printf("\n7. Output written to distrib_x2_01.txt, distrib_x2_12.txt, distrib_1-x2.txt, distrib_semicirc.txt; histograms available in plotting.ipynb\n");
    DistributionGenerators distGen(1);
    distGen.generateX2_01(DIST_SIZE, "output/distrib_x2_01.txt");
    distGen.generateX2_12(DIST_SIZE, "output/distrib_x2_12.txt");
    distGen.generate1MinusX2(DIST_SIZE, "output/distrib_1-x2.txt");
    distGen.generateSemiCircular(DIST_SIZE, "output/distrib_semicirc.txt");

    // Gaussian RNG (Box-Muller)
    printf("\n8. Gaussian RNG results written to box_muller.txt\n");
    GaussianRNG gaussianRNG(1);
    gaussianRNG.boxMuller(N, "output/box_muller.txt");

    // Gaussian Pearson correlation
    printf("\n9. Pearson output written to bm_pearson.txt, test results available in plotting.ipynb\n");
    std::vector<double> normal = gaussianRNG.boxMuller(N, "");
    std::ofstream f9("output/bm_pearson.txt");
    for (int c = 1; c <= CORR_MAX; ++c) {
        f9 << c << "\t" << pearsonCorrelation(normal, c) << std::endl;
    }
    f9.close();

    return 0;
}