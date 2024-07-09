#include <vector>
#include <random>
#include "random_walk.h"

void random_walk_1D(int steps, std::vector<int>& walk, std::mt19937& gen) {
    walk.clear();
    walk.push_back(0);
    int position = 0;
    std::uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < steps; ++i) {
        position += (dis(gen) == 0) ? -1 : 1;
        walk.push_back(position);
    }
}

void random_walk_2D(int steps, std::vector<std::pair<int, int>>& walk, std::mt19937& gen) {
    walk.clear();
    walk.emplace_back(0, 0);
    int x = 0, y = 0;
    std::uniform_int_distribution<> dis(0, 3);
    for (int i = 0; i < steps; ++i) {
        int direction = dis(gen);
        switch (direction) {
            case 0: x += 1; break;
            case 1: x -= 1; break;
            case 2: y += 1; break;
            case 3: y -= 1; break;
        }
        walk.emplace_back(x, y);
    }
}

void random_walk_3D(int steps, std::vector<std::tuple<int, int, int>>& walk, std::mt19937& gen) {
    walk.clear();
    walk.emplace_back(0, 0, 0);
    int x = 0, y = 0, z = 0;
    std::uniform_int_distribution<> dis(0, 5);
    for (int i = 0; i < steps; ++i) {
        int direction = dis(gen);
        switch (direction) {
            case 0: x += 1; break;
            case 1: x -= 1; break;
            case 2: y += 1; break;
            case 3: y -= 1; break;
            case 4: z += 1; break;
            case 5: z -= 1; break;
        }
        walk.emplace_back(x, y, z);
    }
}

int steps_to_return_1D(int steps, std::mt19937& gen) {
    int position = 0;
    std::uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < steps; ++i) {
        position += (dis(gen) == 0) ? -1 : 1;
        if (position == 0 && i != 0) {
            return i + 1; // +1 because step index starts at 0
        }
    }
    return steps;
}

int steps_to_return_2D(int steps, std::mt19937& gen) {
    int x = 0, y = 0;
    std::uniform_int_distribution<> dis(0, 3);
    for (int i = 0; i < steps; ++i) {
        int direction = dis(gen);
        switch (direction) {
            case 0: x += 1; break;
            case 1: x -= 1; break;
            case 2: y += 1; break;
            case 3: y -= 1; break;
        }
        if (x == 0 && y == 0 && i != 0) {
            return i + 1;
        }
    }
    return steps;
}

int steps_to_return_3D(int steps, std::mt19937& gen) {
    int x = 0, y = 0, z = 0;
    std::uniform_int_distribution<> dis(0, 5);
    for (int i = 0; i < steps; ++i) {
        int direction = dis(gen);
        switch (direction) {
            case 0: x += 1; break;
            case 1: x -= 1; break;
            case 2: y += 1; break;
            case 3: y -= 1; break;
            case 4: z += 1; break;
            case 5: z -= 1; break;
        }
        if (x == 0 && y == 0 && z == 0 && i != 0) {
            return i + 1;
        }
    }
    return steps;
}