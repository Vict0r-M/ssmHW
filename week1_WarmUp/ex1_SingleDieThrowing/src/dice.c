#include "dice.h"
#include <stdlib.h> // For rand(), srand()
#include <time.h>   // For time()
#include <math.h> // For pow()

double* simulateDiceThrows(size_t diceNr, size_t throwsNr) {
    srand((unsigned)time(NULL)); // Seed the random number generator

    double* averages = (double*)malloc(throwsNr * sizeof(double)); // Allocate memory for averages
    if (averages == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    for (size_t throwIndex = 0; throwIndex < throwsNr; ++throwIndex) {
        double sum = 0;
        for (size_t diceIndex = 0; diceIndex < diceNr; ++diceIndex) {
            sum += (rand() % 6) + 1; // Simulate a dice throw, rand() % 6 gives a range 0-5, +1 to adjust range to 1-6
        }
        averages[throwIndex] = sum / diceNr; // Calculate average of this throw
    }

    return averages; // Return the array of averages
}

double calculateVariance(const double* data, size_t length) {
    if (length == 0) return 0; // Guard against division by zero

    double sum = 0;
    double mean = 0;

    // Calculate mean
    for (size_t i = 0; i < length; ++i) {
        mean += data[i];
    }
    mean /= length;

    // Calculate variance
    for (size_t i = 0; i < length; ++i) {
        sum += pow(data[i] - mean, 2);
    }
    return sum / length;
}
