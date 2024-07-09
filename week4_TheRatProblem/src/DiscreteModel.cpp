#include "DiscreteModel.h"
#include <cstdlib>

DiscreteModel::DiscreteModel(int gridSize, int maxRats)
    : SIZE(gridSize), NRAT(maxRats), T_MAX(100),
      EMPTY(-1), CALM(0), AGGRESSIVE(1) {
    room = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, EMPTY));
    rats.reserve(NRAT);
    for (int i = 0; i < NRAT; i++) {
        rats.emplace_back(0, 0, CALM);
    }
}

void DiscreteModel::reset() {
    for (auto& rat : rats) {
        room[rat.y][rat.x] = EMPTY;  // Clear previous position
        rat.x = rand() % SIZE;
        rat.y = rand() % SIZE;
        room[rat.y][rat.x] = rat.state;  // Place rat in new position
    }
}

void DiscreteModel::checkNeighbors() {
    for (auto& rat : rats) {
        bool foundAggressive = false;
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nx = (rat.x + dx[i] + SIZE) % SIZE;
            int ny = (rat.y + dy[i] + SIZE) % SIZE;
            if (room[ny][nx] == AGGRESSIVE) {
                foundAggressive = true;
                break;
            }
        }

        if (!foundAggressive && rat.state == AGGRESSIVE) {
            rat.state = CALM;
            room[rat.y][rat.x] = CALM;
        } else if (foundAggressive && rat.state == CALM) {
            rat.state = AGGRESSIVE;
            room[rat.y][rat.x] = AGGRESSIVE;
        }

        if (rand() / (RAND_MAX + 1.0) < PROB_SPONTANEOUS) {
            rat.state = AGGRESSIVE;
            room[rat.y][rat.x] = AGGRESSIVE;
        }
    }
}

double DiscreteModel::meanAggressivity() {
    double sum = 0;
    for (const auto& rat : rats) {
        sum += (rat.state == AGGRESSIVE);
    }
    return sum / rats.size();
}

void DiscreteModel::simulate() {
    std::ofstream f("output/outfile_discrete.txt");
    for (int N = 2500; N <= NRAT; N += 2500) {
        rats.assign(N, Rat(0, 0, CALM));
        for (int t = 0; t < T_MAX; t++) {
            reset();
            checkNeighbors();
        }
        f << N << "\t" << meanAggressivity() << std::endl;
    }
    f.close();
}