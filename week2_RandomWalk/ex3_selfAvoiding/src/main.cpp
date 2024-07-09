#include "SelfAvoidingWalk.h"
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>

int main() {
    int dimensions, max_steps, num_simulations;
    printf("Enter dimensions (1 or 2): ");
    scanf("%d", &dimensions);
    printf("Enter maximum number of steps: ");
    scanf("%d", &max_steps);
    printf("Enter number of simulations: ");
    scanf("%d", &num_simulations);

    std::vector<std::vector<std::pair<int, int>>> all_results;

    for (int i = 0; i < num_simulations; ++i) {
        std::srand(std::time(nullptr) + i); // Ensure different seed for each simulation
        SelfAvoidingWalk walk(dimensions);
        walk.run(max_steps);
        int steps_before_block = walk.get_steps_before_block();
        printf("Simulation %d completed. Steps before blocking: %d\n", i + 1, steps_before_block);

        // Store the results for this simulation
        all_results.push_back(walk.get_path());
    }

    // Save all results in one file
    std::string filename = "output/all_simulations_1D.txt";
    std::ofstream out(filename);
    for (const auto &simulation : all_results) {
        for (const auto &step : simulation) {
            out << "(" << step.first << ", " << step.second << "), ";
        }
        out << "\n";
    }
    out.close();

    return 0;
}