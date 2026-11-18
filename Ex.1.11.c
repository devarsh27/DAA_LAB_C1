#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem
int knapsack(int n, int values[], int weights[], int W) {
    // Create a 2D array for dynamic programming
    // dp[i][w] will store the maximum value obtained with i items and capacity w
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    // Build the table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case: 0 items or 0 capacity yields 0 value
            } else if (weights[i - 1] <= w) {
                // Maximum of including the item or excluding it
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // Weight of the item is more than the current capacity
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][W];

    // Free the allocated memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int n, W;

    // Read the number of items
    if (scanf("%d", &n) != 1) return 0;

    int *values = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));

    // Read the values of the items
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1) return 0;
    }

    // Read the weights of the items
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &weights[i]) != 1) return 0;
    }

    // Read the knapsack capacity
    if (scanf("%d", &W) != 1) return 0;

    // Calculate and print the maximum value
    printf("%d\n", knapsack(n, values, weights, W));

    // Free the item arrays
    free(values);
    free(weights);

    return 0;
}
