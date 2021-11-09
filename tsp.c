#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "hvui:o:"
#define BLOCK  4096

char **cities; //array for the list of cities
uint32_t city_count = 0; //number of cities
uint32_t recursive_count = 0; //number of recursion called
FILE *infile = NULL; //infile destination
FILE *outfile = NULL; //outfile destintion
bool verbose = false; //bool for verbose mode

void DFS(Graph *G, uint32_t v, Path *current, Path **shortest) {
    uint32_t pop = 0;
    recursive_count++; //incrementing count
    graph_mark_visited(G, v); //marked visited
    path_push_vertex(current, v, G); //pushed into the path
    if (*shortest == NULL
        || path_length(current) < path_length(
               *shortest)) { //if shortest doesnt exist (1st time) or current is still less than shortest, keep running
        for (uint32_t i = 0; i < city_count; i++) {
            if (graph_has_edge(G, v, i)) { //check for edges
                if (!graph_visited(G, i)) { //has not visited, go into that path
                    DFS(G, i, current, shortest);
                } else if (
                    i == START_VERTEX
                    && path_vertices(current)
                           == city_count) { //came around in full circle and the amount of paths = city count
                    path_push_vertex(current, i, G); //push one more cuz no more recursion
                    if (verbose) { //verbose mode
                        path_print(current, outfile, cities); //print the paths
                    }
                    if (*shortest == NULL
                        || path_length(current) < path_length(
                               *shortest)) { //initialize shortest path once u came in full circle the first time
                        if (*shortest == NULL) {
                            *shortest = path_create();
                        }
                        path_copy(*shortest, current); //copy current into shortest
                    }
                    path_pop_vertex(current, &pop, G); //pop the vertex
                }
            }
        }
    }
    graph_mark_unvisited(G, v); //unmark visited
    path_pop_vertex(current, &v, G); //pop the vertex
}

int main(int argc, char **argv) {
    int opt;
    bool help = false; //help message
    bool undirected = false; //undirected boolean

    while ((opt = getopt(argc, argv, PROMPT))
           != -1) { //parse input and do the what user wants basically
        switch (opt) {
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }
    if (infile == NULL) { //initialize infile
        infile = stdin;
    }
    if (outfile == NULL) { //initialize outfile
        outfile = stdout;
    }
    if (help) { //help message
        printf("SYNOPSIS\n  Traveling Salesman Problem using DFS.\n\nUSAGE\n  "
               "/home/leo/resources/asgn4/tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\nOPTIONS\n "
               " -u             Use undirected graph.\n  -v             Enable verbose printing.\n "
               " -h             Program usage and help.\n  -i infile      Input containing graph "
               "(default: stdin)\n  -o outfile     Output of computed path (default: stdout)\n");
        return 0;
    }
    char str[BLOCK]; //initialize char array
    fgets(str, BLOCK, infile); //reads in the first value: n
    city_count = atoi(str); //next n lines
    cities = calloc(city_count, sizeof(char *)); //allocate memory for the cities array

    for (uint32_t i = 0; i < city_count; i++) { //loop for number of cities
        fgets(str, BLOCK, infile); //get city names
        str[strlen(str) - 1] = '\0'; //moves \0 to \n and replaces it
        cities[i] = strdup(str); //duplicate the str because it gets overwritten
    }

    Graph *G = graph_create(city_count, undirected); //initialize the graph

    while (fgets(str, BLOCK, infile)) { //reads in the paths
        int k = 0;
        str[strlen(str) - 1] = '\0';
        char *temp = strtok(str, " "); //parse the (int space int space int)
        uint32_t array[3];
        for (int i = 0; i < 3; i++) {
            array[i] = atoi(temp);
            temp = strtok(NULL, " ");
            k++;
        }
        if (k != 3) { //error if not enough numbers. Idk what to do for too many
            fprintf(stderr, "Error: malformed number of vertices\n");
            return 1;
        }

        graph_add_edge(G, array[0], array[1], array[2]); //add the edge to the graph
    }

    uint32_t v = START_VERTEX; //initialize value for v with START_VERTEX
    Path *current = path_create(); //initialize current path
    Path *shortest = NULL; //initialize shortest path

    DFS(G, v, current, &shortest); //run DFS

    if (city_count < 2) { //more edges cases and outputs
        printf("There's nowhere to go.\n");
    } else if (!shortest) {
        printf("No hamiltonian path found.\n");
        printf("Total recursive calls: %d\n", recursive_count);
    } else {
        path_print(shortest, outfile, cities);
        printf("Total recursive calls: %d\n", recursive_count);
    }
    for (uint32_t i = 0; i < city_count; i++) { //free the memory from strdup()
        free(cities[i]);
    }
    path_delete(&current); //free memory
    path_delete(&shortest);
    graph_delete(&G);
}
