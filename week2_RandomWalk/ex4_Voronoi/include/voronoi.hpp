#ifndef VORONOI_HPP
#define VORONOI_HPP

#include <vector>
#include <random>
#include <stdio.h>

class Voronoi {
public:
    Voronoi(int dimensions, int num_cells, int seed);
    void run_simulation();
    void save_results(const char* filename);

private:
    int dimensions;
    int num_cells;
    int seed;
    std::vector<double> cell_sizes;
    
    void generate_voronoi();
    double generate_random_value();
};

#endif // VORONOI_HPP