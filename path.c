#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) { // initialize path
    Path *path = (Path *) malloc(sizeof(Path));
    path->vertices = stack_create(VERTICES + 1);
    path->length = 0;
    return path;
}

void path_delete(Path **p) { // delete the path
    stack_delete(&(*p)->vertices); // delete the stack first
    free(*p); // free the memory then null the pointer
    *p = NULL;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) { // push into path
    if (!stack_empty(p->vertices)) {
        uint32_t temp;
        stack_peek(p->vertices, &temp); // store the peek to temp
        p->length
            += graph_edge_weight(G, temp, v); // add the edge weight between temp and v to path
    }
    return stack_push(p->vertices, v);
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) { // pop from the path
    bool result = stack_pop(p->vertices, v); // pop it
    if (!stack_empty(p->vertices)) {
        uint32_t last;
        stack_peek(p->vertices, &last); // store it to last
        p->length -= graph_edge_weight(G, last, *v); // then subtract the length
    }
    return result;
}

uint32_t path_vertices(Path *p) { // return number of vertices
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) { // return length
    return p->length;
}

void path_copy(Path *dst, Path *src) { // using stack copy to copy the vertices stack
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length; // set length equal to each other
}

void path_print(
    Path *p, FILE *outfile, char *cities[]) { // print using fprintf and in the right format
    fprintf(outfile, "Path length: %d\nPath: ", path_length(p));
    stack_print(p->vertices, outfile, cities); // print the stack of vertices
}
