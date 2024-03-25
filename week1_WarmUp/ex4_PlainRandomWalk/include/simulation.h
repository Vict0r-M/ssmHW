#ifndef SIMULATION_H
#define SIMULATION_H

// Function prototypes for simulation:
void simulate_1d_walks(int steps, int num_simulations, const char* output_path);
void simulate_2d_walks(int steps, int num_simulations, int (*directions)[2], 
                        int num_directions, const char* output_path);

#endif