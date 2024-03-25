#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include "simulation.h"

int main() {
    int steps, max_steps, num_1Dsimulations, num_2Dsimulations;

    // Initialize the random seed:
    initialize_seed();

    // Prompting user for simulation parameters:

    printf("Enter the number of steps for the 1D simulations: ");
    scanf("%d", &steps);
    printf("Enter the number of 1D simulations: ");
    scanf("%d", &num_1Dsimulations);


    printf("Enter the max number of steps for the 2D simulations: ");
    scanf("%d", &max_steps);
    printf("Enter the number of 2D simulations: ");
    scanf("%d", &num_2Dsimulations);

    // Perform the one-dimensional walk simulations:
    simulate_1d_walks(steps, num_1Dsimulations, "output/1d_final_positions.txt");

    printf("Simulation for 1d_final_positions.txt completed.\n");

    // Direction sets defined:
    int directions_4_main_halt[5][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 0}};
    int directions_4_diag[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    int directions_8[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    int directions_8_halt[9][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}, {0, 0}};

    // Array of direction sets for iteration:
    int (*direction_sets[])[2] = {
        directions_4_main_halt, 
        directions_4_diag, 
        directions_8, 
        directions_8_halt
    };
    int num_directions[] = {5, 4, 8, 9};
    char* filenames[] = {"2d_4_main_halt.txt", "2d_4_diag.txt", "2d_8_directions.txt", "2d_8_directions_halt.txt"};

    // Simulate for each direction set:
    for (int i = 0; i < 4; i++) {
        char output_path[100];
        sprintf(output_path, "output/%s", filenames[i]);
        simulate_2d_walks(max_steps, num_2Dsimulations, direction_sets[i], num_directions[i], output_path);
        printf("Simulation for %s completed.\n", filenames[i]);
    }

    return 0;
}