#include "secretary.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Helper function defining the simulation:
double simulate_candidates(int N, int k) {
    int *candidates = (int *)malloc(N * sizeof(int));
    int i, selected_rank;

    // Assign ranks to candidates:
    for (i = 0; i < N; i++) {
        candidates[i] = i + 1; // Assuming ranks are 1 to N
    }

    // Shuffle the candidates to randomize their order:
    for (i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = candidates[i];
        candidates[i] = candidates[j];
        candidates[j] = temp;
    }

    int best_seen = N + 1; // Initially, no candidate has been seen
    for (i = 0; i < k && i < N; i++) {
        if (candidates[i] < best_seen) {
            best_seen = candidates[i];
        }
    }

    // Select the first candidate better than all seen in the initial k:
    int hasSelected = 0; // Flag to check if a selection has been made
    for (; i < N; i++) {
        if (candidates[i] < best_seen) {
            selected_rank = candidates[i];
            hasSelected = 1;
            break;
        }
    }

    // If no candidate was selected better than the first k, select the last one:
    if (!hasSelected) {
        selected_rank = candidates[N - 1];
    }

    free(candidates);
    return selected_rank;
}

// Function to find the optimal k/N ratios:
void find_ratios(int N, int simulations, double *returned_optimal_ratio_best, 
                double *returned_optimal_ratio_average) {
    srand(time(NULL)); // Seed the random number generator
    double max_success = 0.0;
    double best_total_rank = (N + 1) * simulations; // Worst possible rank
    double optimal_ratio_best = 0.0; // For the best candidate
    double optimal_ratio_average = 0.0; // For the best average rank

    FILE *fp_success = fopen("output/success.txt", "w");
    FILE *fp_total_rank = fopen("output/total_rank.txt", "w");

    for (int k = 1; k <= N; k++) {
        double success = 0; // For the best candidate
        double total_rank = 0; // For the best average rank
        for (int i = 0; i < simulations; i++) {
            int temp = simulate_candidates(N, k);
            success += (temp == 1); // For the best candidate
            total_rank += temp; // For the best average rank
        }

        fprintf(fp_success, "%d %lf\n", k, success);
        fprintf(fp_total_rank, "%d %lf\n", k, total_rank);
        
        if (success > max_success) { // For the best candidate
            max_success = success; // No need to divide by the nr of simulations
            optimal_ratio_best = (double)k / N;
        }
        
        if (total_rank < best_total_rank) { // For the best average rank
            best_total_rank = total_rank;
            optimal_ratio_average = (double)k / N;
        } // No need to divide by the nr of simulations
    }

    fclose(fp_success);
    fclose(fp_total_rank);

    *returned_optimal_ratio_best = optimal_ratio_best;
    *returned_optimal_ratio_average = optimal_ratio_average;
}