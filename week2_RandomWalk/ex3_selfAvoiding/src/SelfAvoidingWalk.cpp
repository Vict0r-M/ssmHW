#include "SelfAvoidingWalk.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

SelfAvoidingWalk::SelfAvoidingWalk(int dimensions)
    : dimensions(dimensions), steps(0), blocked_steps(0), current_step(0) {
    reset();
}

void SelfAvoidingWalk::reset() {
    steps = 0;
    blocked_steps = 0;
    current_step = 0;
    path.clear();
    visited.clear();
    path.push_back({0, 0});
    visited.insert({0, 0});
}

bool SelfAvoidingWalk::move() {
    auto next_move = get_next_move();
    if (visited.find(next_move) != visited.end()) {
        blocked_steps++;
        return false;
    }
    path.push_back(next_move);
    visited.insert(next_move);
    steps++;
    return true;
}

std::pair<int, int> SelfAvoidingWalk::get_next_move() const {
    static const std::vector<std::pair<int, int>> directions_1D = {
        {1, 0}, {-1, 0}};
    static const std::vector<std::pair<int, int>> directions_2D = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    const auto& directions = (dimensions == 1) ? directions_1D : directions_2D;

    auto current_position = path.back();
    auto direction = directions[std::rand() % directions.size()];
    return {current_position.first + direction.first, current_position.second + direction.second};
}

bool SelfAvoidingWalk::is_blocked() const {
    static const std::vector<std::pair<int, int>> directions_1D = {
        {1, 0}, {-1, 0}};
    static const std::vector<std::pair<int, int>> directions_2D = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    const auto& directions = (dimensions == 1) ? directions_1D : directions_2D;

    for (const auto &direction : directions) {
        auto next = std::make_pair(path.back().first + direction.first,
                                   path.back().second + direction.second);
        if (visited.find(next) == visited.end()) {
            return false;
        }
    }
    return true;
}

void SelfAvoidingWalk::run(int max_steps) {
    while (steps < max_steps && !is_blocked()) {
        if (!move()) {
            break;
        }
    }
}

int SelfAvoidingWalk::get_steps_before_block() const {
    return steps;
}

void SelfAvoidingWalk::save_results(const std::string &filename, const std::vector<int> &results) const {
    std::ofstream out(filename, std::ios::app);
    for (const auto &result : results) {
        out << result << " ";
    }
    out << "\n";
    out.close();
}

const std::vector<std::pair<int, int>>& SelfAvoidingWalk::get_path() const {
    return path;
}