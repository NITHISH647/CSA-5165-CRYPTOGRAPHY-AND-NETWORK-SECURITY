#include <stdio.h>
#include <math.h>
#define FACTORIAL_NUM 25
double factorial(int n) {
    double result = 1.0;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    double total_permutations = factorial(FACTORIAL_NUM);
    double power_of_2_total = log2(total_permutations);
    double estimated_unique_keys = total_permutations / 100000;
    double power_of_2_unique = log2(estimated_unique_keys);
    printf("Approximate power of 2 for the number of possible keys: %.0f\n", power_of_2_total);
    printf("Approximate power of 2 for the number of effectively unique keys: %.0f\n", power_of_2_unique);

    return 0;
}
