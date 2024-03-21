#ifndef DICE_H
#define DICE_H

#include <stdlib.h>
#include <time.h>

// Function prototypes
void seed_random_number_generator();
int throw_dice();
void simulate_throws(int n_experiments, int dice_count, int* results);

#endif