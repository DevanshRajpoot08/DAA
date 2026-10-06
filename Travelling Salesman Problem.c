#include <stdio.h>

#define INF 1000000000

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int cost[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    int total_states = 1 << n;
    int dp[1 << 16][16];

    for (int mask = 0; mask < total_states; mask++) {
        for (int u = 0; u < n; u++) {
            dp[mask][u] = INF;
        }
    }

    // Base case: start at city 0
    dp[1][0] = 0;

    for (int mask = 1; mask < total_states; mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == INF) continue;

            for (int v = 0; v < n; v++) {
                if (!(mask & (1 << v)) && cost[u][v] != -1) {
                    int next_mask = mask | (1 << v);
                    int new_cost = dp[mask][u] + cost[u][v];
                    if (new_cost < dp[next_mask][v]) {
                        dp[next_mask][v] = new_cost;
                    }
                }
            }
        }
    }

    int all_visited = (1 << n) - 1;
    int ans = INF;
    for (int u = 1; u < n; u++) {
        if (dp[all_visited][u] != INF && cost[u][0] != -1) {
            int total_cost = dp[all_visited][u] + cost[u][0];
            if (total_cost < ans) {
                ans = total_cost;
            }
        }
    }

    if (ans == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }

    return 0;
}
