
#include <stdio.h>

#define MAX 100
#define INF 999999

struct Edge {
    int u, v, w;
};

int main() {
    int V, E, i, j, source;
    struct Edge edges[MAX * MAX];
    int dist[MAX], parent[MAX];

    scanf("%d", &V);
    scanf("%d", &E);

    for (i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].u, &edges[i].v, &edges[i].w);
    }

    scanf("%d", &source);

    for (i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (i = 1; i < V; i++) {
        int updated = 0;

        for (j = 0; j < E; j++) {
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

        if (!updated)
            break;
    }

    for (i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (dist[u] != INF &&
            dist[u] + w < dist[v]) {
            printf("Negative cycle detected\n");
            return 0;
        }
    }

    for (i = 1; i <= V; i++) {
        if (i == source)
            continue;

        if (dist[i] == INF) {
            printf("%d INF None\n", i);
        } else {
            int path[MAX], count = 0;
            int node = i;

            while (node != -1) {
                path[count++] = node;
                node = parent[node];
            }

            printf("%d %d ", i, dist[i]);

            for (j = count - 1; j >= 0; j--) {
                printf("%d", path[j]);

                if (j > 0)
                    printf("->");
            }

            printf("\n");
        }
    }

    return 0;
}

