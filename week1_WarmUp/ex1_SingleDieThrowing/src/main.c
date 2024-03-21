#include "dice.h"
#include <stdio.h>
#include <stdlib.h> // For free()

int main() {
    size_t diceNrLow, throwsNr;

    printf("Enter the starting number of dice: ");
    scanf("%zu", &diceNrLow); // "%zu" specifies 'size_t'

    printf("Enter the number of throws: ");
    scanf("%zu", &throwsNr); // "%zu" specifies 'size_t'

    // Perform the simulation 10 times in a 1000 range:
    for(size_t diceNr=diceNrLow; diceNr <= diceNrLow + 900; diceNr += 100) {
        double* averages = simulateDiceThrows(diceNr, throwsNr);
        if (averages == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }

        // Calculate variance:
        double variance = calculateVariance(averages, throwsNr);
        printf("%zu dice variance of averages: %f\n", diceNr, variance);

        // Free the dynamically allocated memory:
        free(averages);
    }

    return 0;
}