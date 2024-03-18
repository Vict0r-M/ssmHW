#include "dice.h"
#include <stdio.h>
#include <stdlib.h> // For free()

int main() {
    size_t diceNr, throwsNr;

    // Prompt user for input
    printf("Enter the number of dice: ");
    scanf("%zu", &diceNr);

    printf("Enter the number of throws: ");
    scanf("%zu", &throwsNr);

    // Perform the simulation
    double* averages = simulateDiceThrows(diceNr, throwsNr);
    if (averages == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Calculate variance
    double variance = calculateVariance(averages, throwsNr);
    printf("Variance of the averages: %f\n", variance);

    // Clean up
    free(averages); // Free the dynamically allocated memory

    return 0;
}
