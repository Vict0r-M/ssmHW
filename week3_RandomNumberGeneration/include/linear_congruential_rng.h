#ifndef LINEAR_CONGRUENTIAL_RNG_H
#define LINEAR_CONGRUENTIAL_RNG_H

#include <vector>
#include <string>

class LinearCongruentialRNG {
public:
    LinearCongruentialRNG(long int a, long int c, long int m, int seed);
    int generate();
    std::vector<double> generateSequence(int length, const std::string& filename);
    int checkPeriod(int periodMax);

private:
    long int a;
    long int c;
    long int m;
    int seed;
    long int current;
};

#endif // LINEAR_CONGRUENTIAL_RNG_H