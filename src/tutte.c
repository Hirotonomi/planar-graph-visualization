#include "graph.h"
#include "node.h"
#include <math.h>
#include <string.h>
#define MAXN 1000 // FIX: set max to something different
#define EPS 1e-9

int visited[MAXN];
int par[MAXN];
int cycle[MAXN];

int found_cycle;
int cycle_size;

int is_boundary[MAXN];
double x[MAXN], y[MAXN];

void store_cycle(int u, int v) {
    int cur = u;
    int i = 0;
    while (cur != v && cur != -1) {
        cycle[i++] = cur;
        cur = par[cur];
    }
    cycle[i++] = v;
    if (i < 3) return;
    found_cycle = 1;
    cycle_size = i;
    return;
}

void dfs_cycle(Graph *g, int v, int p) {
    visited[v] = 1;
    par[v] = p;
    for (int i = 0; i < g->adj[v].size; i++) {
        int u = g->adj[v].data[i].to;
        int found_cycle = 0;
        if (!visited[u]) {
            dfs_cycle(g, u, v);
            if (found_cycle) return;
        } else {
            store_cycle(v, u);
            if (found_cycle) return;
        }
    }
}

void fix_cycle(Graph *g) {
    memset(is_boundary, 0, sizeof(is_boundary));
    for (int i = 0; i < cycle_size; i++) {
        int v = cycle[i];
        is_boundary[v] = 1;

        double ang = 2.0 * M_PI * i / cycle_size;
        x[v] = cos(ang);
        y[v] = sin(ang);
    }
}
