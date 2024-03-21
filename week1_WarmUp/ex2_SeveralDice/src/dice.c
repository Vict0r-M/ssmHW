#include "dice.h"

void seed_random_number_generator() {
    srand(time(NULL));
}

int throw_dice() {
    return (rand() % 6) + 1;
}

void simulate_throws(int n_experiments, int dice_count, int* results) {
    for (int i = 0; i < n_experiments; i++) {
        int sum = 0;
        for (int k = 0; k < dice_count; k++) {
            sum += throw_dice();
        }
        results[i] = sum;
    }
}