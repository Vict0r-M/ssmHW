#ifndef GAUSSIAN_RNG_H
#define GAUSSIAN_RNG_H

#include <vector>
#include <string>

class GaussianRNG {
public:
    GaussianRNG(int seed);
    std::vector<double> boxMuller(int length, const std::string& filename);

private:
    int seed;
};

#endif // GAUSSIAN_RNG_H