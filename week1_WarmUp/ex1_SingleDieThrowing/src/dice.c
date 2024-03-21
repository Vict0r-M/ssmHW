#include "dice.h"
#include <stdlib.h> // For rand(), srand(), malloc()
#include <time.h>
#include <math.h>

double* simulateDiceThrows(size_t diceNr, size_t throwsNr) {
    srand((unsigned)time(NULL)); // Seed the random number generator

    // Dynamically allocate memory for the averages array:
    double* averages = (double*)malloc(throwsNr * sizeof(double));
    if (averages == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // Simulate throwsNr throws:
    for (size_t throwIndex = 0; throwIndex < throwsNr; ++throwIndex) {
        double sum = 0;
        for (size_t diceIndex = 0; diceIndex < diceNr; ++diceIndex) {
            sum += (rand() % 6) + 1;
        }
        averages[throwIndex] = sum / diceNr; // Calculate average of one throw
    }

    return averages; // Return the array of averages
}

double calculateVariance(const double* data, size_t length) {
    if (length == 0) return 0; // Guard against division by zero

    double sum = 0;
    double mean = 0;

    // Calculate mean:
    for (size_t i = 0; i < length; ++i) {
        mean += data[i];
    }
    mean /= length;

    // Calculate variance:
    for (size_t i = 0; i < length; ++i) {
        sum += pow(data[i] - mean, 2);
    }
    return sum / length;
}