#include <cstdio>
#include <fstream>
#include <vector>
#include <random>
#include "random_walk.h"

void save_data_to_file(const std::string& filename, const std::vector<std::vector<int>>& data, const std::vector<int>& step_counts) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < data.size(); ++i) {
            file << step_counts[i];
            for (const int& value : data[i]) {
                file << " " << value;
            }
            file << "\n";
        }
        file.close();
    } else {
        printf("Unable to open file: %s\n", filename.c_str());
    }
}

void initialize_simulation_parameters(int& max_step_count, int& step_increment_count, int& num_walks_sim) {
    max_step_count = 1000;
    step_increment_count = 1000;
    num_walks_sim = 100;
}

void run_simulations(int max_step_count, int step_increment_count, int num_walks_sim, 
                     std::vector<std::vector<int>>& return_steps_1D,
                     std::vector<std::vector<int>>& return_steps_2D,
                     std::vector<std::vector<int>>& return_steps_3D,
                     std::vector<int>& step_counts) {
    int step_increment = max_step_count / step_increment_count;

    for (int i = 0; i < step_increment_count; ++i) {
        int steps = step_increment * (i + 1);
        step_counts[i] = steps;

        std::random_device rd;
        for (int j = 0; j < num_walks_sim; ++j) {
            std::mt19937 gen(rd());
            return_steps_1D[i].push_back(steps_to_return_1D(steps, gen));
            return_steps_2D[i].push_back(steps_to_return_2D(steps, gen));
            return_steps_3D[i].push_back(steps_to_return_3D(steps, gen));
        }
    }
}

int main() {
    int max_step_count, step_increment_count, num_walks_sim;
    initialize_simulation_parameters(max_step_count, step_increment_count, num_walks_sim);

    std::vector<std::vector<int>> return_steps_1D(step_increment_count);
    std::vector<std::vector<int>> return_steps_2D(step_increment_count);
    std::vector<std::vector<int>> return_steps_3D(step_increment_count);
    std::vector<int> step_counts(step_increment_count);

    printf("Starting simulation with max_step_count=%d, step_increment_count=%d, num_walks_sim=%d\n", max_step_count, step_increment_count, num_walks_sim);

    run_simulations(max_step_count, step_increment_count, num_walks_sim, return_steps_1D, return_steps_2D, return_steps_3D, step_counts);

    save_data_to_file("output/return_steps_1D.txt", return_steps_1D, step_counts);
    save_data_to_file("output/return_steps_2D.txt", return_steps_2D, step_counts);
    save_data_to_file("output/return_steps_3D.txt", return_steps_3D, step_counts);

    printf("Data saved to files\n");

    return 0;
}