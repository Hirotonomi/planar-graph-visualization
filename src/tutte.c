#include "graph.h"
#include "node.h"
#include <math.h>
#define MAXN 1000 // FIX: set max to something different

int visited[MAXN];
int par[MAXN];
int cycle[MAXN];

void store_cycle(int u, int v) {
    int cur = u;
    int i = 0;
    while (cur != v && cur != -1) {
        cycle[i++] = cur;
        cur = par[cur];
    }
    cycle[i++] = v;
    return;
}

int dfs_cycle(Graph *g, int v, int p) {
    visited[v] = 1;
    par[v] = p;
    for (int i = 0; i < g->adj[v].size; i++) {
        int u = g->adj[v].data[i].to;
        int found_cycle = 0;
        if (!visited[u]) {
            found_cycle = dfs_cycle(g, u, v);
        } else {
            found_cycle = 1;
            store_cycle(v, u);
        }
        // if already found cycle no point in doing rest of dfs
        if (found_cycle == 1) {
            return 1;
        } else {
            return -1; // -1 if no cycle found, use later for error
        }
    }
    return 0;
}
