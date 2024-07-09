#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include <vector>
#include <utility>
#include <tuple>
#include <random>

// Function prototypes
void random_walk_1D(int steps, std::vector<int>& walk, std::mt19937& gen);
void random_walk_2D(int steps, std::vector<std::pair<int, int>>& walk, std::mt19937& gen);
void random_walk_3D(int steps, std::vector<std::tuple<int, int, int>>& walk, std::mt19937& gen);

int steps_to_return_1D(int steps, std::mt19937& gen);
int steps_to_return_2D(int steps, std::mt19937& gen);
int steps_to_return_3D(int steps, std::mt19937& gen);

#endif // RANDOM_WALK_H