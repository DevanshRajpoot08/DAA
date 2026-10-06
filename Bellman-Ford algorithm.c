#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

struct Edge {
    int u, v, w;
};

void printPath(int parent[], int src, int vertex) {
    int path[1001];
    int count = 0;
    int current = vertex;

    while (current != -1) {
        path[count++] = current;
        if (current == src)
            break;
        current = parent[current];
    }

    // Safety check: source was not reached
    if (path[count - 1] != src) {
        printf("None");
        return;
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i != 0)
            printf("->");
    }
}

int main() {
    int V, E;

    scanf("%d", &V);
    scanf("%d", &E);

    struct Edge edges[E];

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].w);
    }

    int src;
    scanf("%d", &src);

    int dist[V + 1];
    int parent[V + 1];

    // Initialization
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[src] = 0;

    // Bellman-Ford: relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        int updated = 0;

        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF &&
                dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;
                parent[v] = u;
                updated = 1;
            }
        }

        // Optimization: stop if no distance was updated
        if (!updated)
            break;
    }

    // Check for negative weight cycle
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (dist[u] != INF &&
            dist[u] + w < dist[v]) {

            printf("Negative cycle detected\n");
            return 0;
        }
    }

    // Print shortest distance and path
    for (int i = 1; i <= V; i++) {

        // Source is excluded
        if (i == src)
            continue;

        if (dist[i] == INF) {
            printf("%d INF None\n", i);
        } else {
            printf("%d %d ", i, dist[i]);
            printPath(parent, src, i);
            printf("\n");
        }
    }

    return 0;
}
