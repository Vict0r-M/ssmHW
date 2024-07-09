#ifndef SELFAVOIDINGWALK_H
#define SELFAVOIDINGWALK_H

#include <vector>
#include <set>
#include <utility>
#include <string>

class SelfAvoidingWalk {
public:
    SelfAvoidingWalk(int dimensions);
    void reset();
    bool move();
    bool is_blocked() const;
    void run(int max_steps);
    int get_steps_before_block() const;
    void save_results(const std::string &filename, const std::vector<int> &results) const;
    const std::vector<std::pair<int, int>>& get_path() const; // Getter for path

private:
    int dimensions;
    int steps;
    int blocked_steps;
    int current_step;
    std::vector<std::pair<int, int>> path;
    std::set<std::pair<int, int>> visited;
    std::pair<int, int> get_next_move() const;
};

#endif