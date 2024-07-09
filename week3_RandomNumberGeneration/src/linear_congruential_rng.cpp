#include "linear_congruential_rng.h"
#include <fstream>
#include <algorithm>
#include <iostream>

LinearCongruentialRNG::LinearCongruentialRNG(long int a, long int c, long int m, int seed)
    : a(a), c(c), m(m), seed(seed), current(seed) {}

int LinearCongruentialRNG::generate() {
    current = (a * current + c) % m;
    return current;
}

std::vector<double> LinearCongruentialRNG::generateSequence(int length, const std::string& filename) {
    std::ofstream file(filename);
    std::vector<double> sequence(length, 0);
    for (int i = 0; i < length; ++i) {
        current = generate();
        sequence[i] = static_cast<double>(current) / (m - 1.0);
        file << sequence[i] << std::endl;
    }
    file.close();
    return sequence;
}

int LinearCongruentialRNG::checkPeriod(int periodMax) {
    std::vector<long int> values(periodMax, -1);
    for (int i = 0; i < periodMax; ++i) {
        current = generate();
        auto it = std::find(values.begin(), values.begin() + i, current);
        if (it != values.begin() + i) {
            return i - std::distance(values.begin(), it);
        }
        values[i] = current;
    }
    return -1;
}