#ifndef DISTRIBUTION_GENERATORS_H
#define DISTRIBUTION_GENERATORS_H

#include <vector>
#include <string>

class DistributionGenerators {
public:
    DistributionGenerators(int seed);
    std::vector<double> generateX2_01(int length, const std::string& filename);
    std::vector<double> generateX2_12(int length, const std::string& filename);
    std::vector<double> generate1MinusX2(int length, const std::string& filename);
    std::vector<double> generateSemiCircular(int length, const std::string& filename);

private:
    int seed;
    double newtonMethod(double x, double p, double (*func)(double, double), double (*derivFunc)(double, double));
};

#endif // DISTRIBUTION_GENERATORS_H