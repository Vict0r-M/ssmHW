#include <stdio.h>
#include <stdlib.h> // For dynamic memory allocation
#include "dice.h"

#define N_EXPERIMENTS 10000

int main() {
    int dice_count = 100000;
    int* results = malloc(N_EXPERIMENTS * sizeof(int));
    if (results == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    seed_random_number_generator();
    simulate_throws(N_EXPERIMENTS, dice_count, results);

    // Saving results to a file
    FILE *fp = fopen("output/results.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        free(results);
        return 1;
    }

    for (int i = 0; i < N_EXPERIMENTS; i++) {
        fprintf(fp, "%d\n", results[i]);
    }

    fclose(fp);
    free(results); // Freeing dynamically allocated memory

    printf("Results saved to output/results.txt\n");

    return 0;
}