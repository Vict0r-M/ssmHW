#include "correlation_tests.h"
#include <cmath>

double pearsonCorrelation(const std::vector<double>& sequence, int lag) {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0;
    int N = sequence.size();

    for (int i = 0; i < N - lag; ++i) {
        sumX += sequence[i];
        sumY += sequence[i + lag];
        sumXY += sequence[i] * sequence[i + lag];
        sumX2 += sequence[i] * sequence[i];
        sumY2 += sequence[i + lag] * sequence[i + lag];
    }

    double numerator = N * sumXY - sumX * sumY;
    double denominator = std::sqrt((N * sumX2 - sumX * sumX) * (N * sumY2 - sumY * sumY));
    return numerator / denominator;
}