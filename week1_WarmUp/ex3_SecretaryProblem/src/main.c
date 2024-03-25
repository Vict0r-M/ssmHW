#include <stdio.h>
#include <stdlib.h>
#include "secretary.h"

int main() {
    int N, simulations;
    printf("Enter the number of candidates (N): ");
    scanf("%d", &N);
    printf("Enter the number of simulations: ");
    scanf("%d", &simulations);

    double returned_optimal_ratio_best, returned_optimal_ratio_average;
    find_ratios(N, simulations, &returned_optimal_ratio_best, &returned_optimal_ratio_average);
    
    printf("Optimal k/N ratio to employ the best applicant: %lf\n", returned_optimal_ratio_best);
    printf("Optimal k/N ratio to maximize the average quality of the accepted applicant: %lf\n", returned_optimal_ratio_average);
    
    return 0;
}
