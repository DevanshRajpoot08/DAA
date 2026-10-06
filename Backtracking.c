#include <stdio.h>

int set[100];
int subset[100];
int results[100][100];
int resultSizes[100];
int count = 0;
int n, target;

void backtrack(int index, int currentSum, int depth) {
    if (currentSum == target) {
        // Store the found subset
        for (int i = 0; i < depth; i++)
            results[count][i] = subset[i];
        resultSizes[count] = depth;
        count++;
        return;
    }

    for (int i = index; i < n; i++) {
        if (currentSum + set[i] <= target) {
            subset[depth] = set[i];
            backtrack(i + 1, currentSum + set[i], depth + 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &set[i]);
    scanf("%d", &target);

    backtrack(0, 0, 0);

    if (count == 0) {
        printf("-1\n");
    } else {
        // Print in reverse order of discovery
        for (int i = count - 1; i >= 0; i--) {
            for (int j = 0; j < resultSizes[i]; j++)
                printf("%d ", results[i][j]);
            printf("\n");
        }
    }

    return 0;
}
