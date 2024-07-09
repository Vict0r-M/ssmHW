#include "voronoi.hpp"
#include <fstream>
#include <cmath>
#include <sstream>

Voronoi::Voronoi(int dimensions, int num_cells, int seed)
    : dimensions(dimensions), num_cells(num_cells), seed(seed) {}

void Voronoi::run_simulation() {
    cell_sizes.clear();
    generate_voronoi();
}

void Voronoi::generate_voronoi() {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < num_cells; ++i) {
        double cell_size = generate_random_value();
        cell_sizes.push_back(cell_size);
    }
}

double Voronoi::generate_random_value() {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dimensions == 1) {
        double x = dis(gen);
        return x * exp(-x);
    } else if (dimensions == 2) {
        double x = dis(gen);
        return pow(x, 2.5) * exp(-x);
    } else {
        return 0.0;
    }
}

void Voronoi::save_results(const char* filename) {
    std::ofstream file;
    file.open(filename, std::ios_base::app); // Append to file

    for (size_t i = 0; i < cell_sizes.size(); ++i) {
        file << cell_sizes[i];
        if (i != cell_sizes.size() - 1) {
            file << " ";
        }
    }
    file << "\n";
}