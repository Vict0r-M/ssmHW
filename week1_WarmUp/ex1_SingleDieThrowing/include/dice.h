#ifndef DICE_H
#define DICE_H

#include <stddef.h> // For size_t

double* simulateDiceThrows(size_t diceNr, size_t throwsNr);

double calculateVariance(const double* data, size_t length);

#endif // DICE_H
