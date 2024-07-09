#include "voronoi.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_progress(int current, int total) {
    printf("Progress: %d/%d\n", current, total);
}

int main() {
    int dimensions, num_cells, num_simulations;
    char output_filename[100];

    printf("Enter the number of dimensions (1 or 2): ");
    scanf("%d", &dimensions);
    printf("Enter the number of cells: ");
    scanf("%d", &num_cells);
    printf("Enter the number of simulations: ");
    scanf("%d", &num_simulations);
    printf("Enter the output filename: ");
    scanf("%s", output_filename);

    char full_output_filename[150];
    snprintf(full_output_filename, sizeof(full_output_filename), "output/%s", output_filename);

    for (int i = 0; i < num_simulations; ++i) {
        int seed = rand();
        Voronoi voronoi(dimensions, num_cells, seed);
        voronoi.run_simulation();
        
        voronoi.save_results(full_output_filename);

        display_progress(i + 1, num_simulations);
    }

    return 0;
}