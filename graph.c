#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(
    uint32_t vertices, bool undirected) { // allocate memory for graph and set up variables
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

void graph_delete(Graph **G) { // delete the graph by dereferencing it and free that
    free(*G);
    *G = NULL; // set the pointer to null
    return;
}

static inline bool outbound(
    Graph *G, uint32_t i, uint32_t j) { // inline function to check if a vertex is ever out of bound
    return ((i < 0 || i >= G->vertices) || (j < 0 || j >= G->vertices));
}

uint32_t graph_vertices(Graph *G) { // print the number of vertices in the graph
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) { // add an edge between i and j
    if (G && !(outbound(G, i, j))) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k; // add an edge between j and i if undirected
        }
        return true;
    }
    return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (!G || (outbound(G, i, j))) { // if null or out of bound then false
        return false;
    }
    return G->matrix[i][j] > 0; // return if matrix[i][j] is > 0
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (!G || (outbound(G, i, j))) { // check if null or out of bound then false
        return 0;
    }
    return G->matrix[i][j]; // return matrix[i][j]
}

bool graph_visited(Graph *G, uint32_t v) { // check if v is > 0 in visited array
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) { // if v is in bound then set it to true in the array
    if (v >= 0 && v <= G->vertices) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) { // if v is in bound then mark v to unvisited
    if (v >= 0 && v <= G->vertices) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) { // print the graph if I needed to debug it
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%2u ", G->matrix[i][j]);
        }
        printf("\n");
    }
}
