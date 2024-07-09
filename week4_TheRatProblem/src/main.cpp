#include "ContinuousModel.h"
#include "DiscreteModel.h"
#include <cstdio>

int main() {
    printf("Select simulation mode:\n1. Continuous Space Model\n2. Discrete Grid Model\nEnter choice (1 or 2): ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        ContinuousModel model(1000);  // Assuming 1000 rats for the continuous model
        model.simulate();
        printf("Continuous Space Model simulation completed.\n");
    } else if (choice == 2) {
        DiscreteModel model(250, 100000);  // Grid size of 250 and 100,000 rats for the discrete model
        model.simulate();
        printf("Discrete Grid Model simulation completed.\n");
    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }
    return 0;
}