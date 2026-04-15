#include "graph.h"
#include "node.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#define MAXN 1000 // FIX: set max to something different
#define EPS 1e-9
#define R 100 // circle radius
#define MAXCYCLES 100

int visited[MAXN];
int par[MAXN];
int cycles[MAXCYCLES][MAXN];

// int found_cycle;
int cycle_count;
int cycle_sizes[MAXCYCLES];

int is_boundary[MAXN];
double x[MAXN], y[MAXN];

double A[MAXN][MAXN];
double bx[MAXN], by[MAXN];

void store_cycle(int start, int end) {
    if (cycle_count >= MAXCYCLES) return;
    int path[MAXN], len = 0;
    int cur = start;
    while (cur != end && cur != -1) {
        path[len++] = cur;
        cur = par[cur];
    }

    if (cur == -1) return;

    path[len++] = end;

    if (len < 3) return;

    for (int i = 0; i < len; i++) {
        cycles[cycle_count][i] = path[i];
    }
    cycle_sizes[cycle_count] = len;
    cycle_count++;
}

void dfs_cycles(Graph *g, int v, int p) {
    visited[v] = 1;
    par[v] = p;
    for (int i = 0; i < g->adj[v].size; i++) {
        int u = g->adj[v].data[i].to;
        if (!visited[u]) {
            dfs_cycles(g, u, v);
        } else {
            store_cycle(v, u);
        }
    }
}

int has_chord(Graph *g, int cycle[], int k) {
    for (int i = 0; i < k; i++) {
        int u = cycle[i];

        for (int j = 0; j < g->adj[u].size; j++) {
            int v = g->adj[u].data[j].to;

            for (int t = 0; t < k; t++) {
                if (cycle[t] == v) {
                    int next = (i + 1) % k;
                    int prev = (i - 1 + k) % k;

                    if (t != next && t != prev) return 1;
                }
            }
        }
    }
    return 0;
}

int cycle_score(Graph *g, int id) {
    int len = cycle_sizes[id];

    int penalty = has_chord(g, cycles[id], len) ? 1000 : 0;

    return len - penalty;
}

void sort_cycles(Graph *g) {
    for (int i = 0; i < cycle_count; i++) {
        for (int j = i + 1; j < cycle_count; j++) {
            if (cycle_score(g, j) > cycle_score(g, i)) {

                // swap cycles
                int tmp[MAXN], tmp_size;

                memcpy(tmp, cycles[i], sizeof(tmp));
                memcpy(cycles[i], cycles[j], sizeof(tmp));
                memcpy(cycles[j], tmp, sizeof(tmp));

                tmp_size = cycle_sizes[i];
                cycle_sizes[i] = cycle_sizes[j];
                cycle_sizes[j] = tmp_size;
            }
        }
    }
}
void fix_cycle(int cycle[], int size) {
    for (int i = 0; i < size; i++) {
        is_boundary[cycle[i]] = 0;
    }
    for (int i = 0; i < size; i++) {
        int v = cycle[i];
        is_boundary[v] = 1;
        double angle = 2.0 * M_PI * ((double)i / size);

        x[v] = R * cos(angle);
        y[v] = R * sin(angle);
    }
}

void build_linear_equations(Graph *g) {
    int n = g->vertices_num;
    for (int i = 0; i < n; i++) {
        bx[i] = by[i] = 0;
        for (int j = 0; j < n; j++) {
            A[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        if (is_boundary[i]) {
            A[i][i] = 1.0;
            bx[i] = x[i];
            by[i] = y[i];
        } else {
            int deg = g->adj[i].size;
            A[i][i] = (double)deg;
            for (int k = 0; k < deg; k++) {
                int j = g->adj[i].data[k].to;
                A[i][j] = -1.0;
            }
            bx[i] = 0.0;
            by[i] = 0.0;
        }
    }
}

// Gauss przez ai bo mi się nie chciało pisać
// FIX: usunąć komentarz XD (oraz może sprawdzić gaussa?)
void solve(int n, double A[MAXN][MAXN], double b[MAXN], double x[MAXN]) {
    int i, j, k;

    for (i = 0; i < n; i++) {

        // pivot
        double pivot = A[i][i];
        if (fabs(pivot) < 1e-12) {
            printf("Numerical issue: zero pivot\n");
            return;
        }

        // normalize row
        for (j = i; j < n; j++) A[i][j] /= pivot;

        b[i] /= pivot;

        // eliminate other rows
        for (k = 0; k < n; k++) {
            if (k == i) continue;

            double factor = A[k][i];

            for (j = i; j < n; j++) A[k][j] -= factor * A[i][j];

            b[k] -= factor * b[i];
        }
    }

    // extract solution
    for (i = 0; i < n; i++) x[i] = b[i];
}

// FIX: More AI stuff to test
int segments_intersect(double ax, double ay, double bx, double by, double cx,
                       double cy, double dx, double dy) {

    double o1 = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    double o2 = (bx - ax) * (dy - ay) - (by - ay) * (dx - ax);
    double o3 = (dx - cx) * (ay - cy) - (dy - cy) * (ax - cx);
    double o4 = (dx - cx) * (by - cy) - (dy - cy) * (bx - cx);

    return (o1 * o2 < 0 && o3 * o4 < 0);
}
int has_crossing(Graph *g, double px[], double py[]) {
    int n = g->vertices_num;

    for (int u = 0; u < n; u++) {
        for (int i = 0; i < g->adj[u].size; i++) {

            int v = g->adj[u].data[i].to;

            // avoid double-checking edges
            if (u >= v) continue;

            for (int a = 0; a < n; a++) {
                for (int j = 0; j < g->adj[a].size; j++) {

                    int b = g->adj[a].data[j].to;

                    if (a >= b) continue;

                    // skip same or shared-vertex edges
                    if (u == a || u == b || v == a || v == b) continue;
                    if (segments_intersect(px[u], py[u], px[v], py[v], px[a],
                                           py[a], px[b], py[b])) {
                        return 1; // crossing found
                    }
                }
            }
        }
    }

    return 0;
}

void find_embedding(Graph *g) {
    int n = g->vertices_num;
    memset(visited, 0, sizeof(visited));
    memset(par, -1, sizeof(par));
    cycle_count = 0;
    dfs_cycles(g, 0, -1);
    if (cycle_count == 0) {
        printf("No cycle found");
        return;
    }
    sort_cycles(g);
    int max_try = (cycle_count < 20) ? cycle_count : 20;
    for (int i = 0; i < max_try; i++) {
        fix_cycle(cycles[i], cycle_sizes[i]);
        build_linear_equations(g);
        double rx[MAXN], ry[MAXN];
        solve(n, A, bx, rx);
        build_linear_equations(g);
        solve(n, A, by, ry);

        if (!has_crossing(g, rx, ry)) {
            printf("Planar embedding found:\n");
            for (int i = 0; i < n; i++)
                printf("%d: (%f, %f)\n", i, rx[i], ry[i]);
            return;
        }
    }
}
