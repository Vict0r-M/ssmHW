#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function to generate a random step:
static int random_step() {
    return (rand() % 2) * 2 - 1;
}

// Function to simulate multiple one-dimensional random walks:
void simulate_1d_walks(int steps, int num_simulations, const char* output_path) {
    FILE* file = fopen(output_path, "w");
    if(file == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        exit(1);
    }

    for(int sim = 0; sim < num_simulations; ++sim) {
        int position = 0;
        for(int i = 0; i < steps; ++i) {
            position += random_step();
        }
        fprintf(file, "%d\n", position);
    }

    fclose(file);
}

// Generic function to simulate 2D random walks:
void simulate_2d_walks(int max_steps, int num_simulations, int (*directions)[2], int num_directions, const char* output_path) {
    FILE* file = fopen(output_path, "w");
    if(file == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        exit(1);
    }
    
    for(int step = 1; step <= max_steps; ++step) {
        long long total_squared_distance = 0; // Use long long to avoid overflow

        for(int sim = 0; sim < num_simulations; ++sim) {
            int x = 0, y = 0;

            for(int i = 0; i < step; ++i) { // Simulate up to 'step' steps
                int dir_idx = rand() % num_directions;
                x += directions[dir_idx][0];
                y += directions[dir_idx][1];
            }

            total_squared_distance += (long long)x*x + (long long)y*y;
        }

        // Calculate average squared distance for this step:
        double avg_squared_distance = (double)total_squared_distance / num_simulations;
        fprintf(file, "%d, %f\n", step, avg_squared_distance); // Print step and average squared distance

        // Progress indicator
        if(step % (max_steps / 10) == 0) {
            printf("%s simulation %d%% complete\n", output_path, (step * 100) / max_steps);
        }
    }

    fclose(file);
}