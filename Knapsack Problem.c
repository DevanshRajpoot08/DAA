#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int n, w;
    if (scanf("%d", &n) != 1) return 0;

    int values[1005];
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    int weights[1005];
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    scanf("%d", &w);

    int dp[1005] = {0};

    for (int i = 0; i < n; i++) {
        for (int cap = w; cap >= weights[i]; cap--) {
            dp[cap] = MAX(dp[cap], dp[cap - weights[i]] + values[i]);
        }
    }

    printf("%d\n", dp[w]);
    return 0;
}
