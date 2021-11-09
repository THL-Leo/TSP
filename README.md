# Assignment 4 - The Perambulations of Denver Long

This lab contains the program that can solve the Traveling Salesman Problem up to 26 vertices. 

## Building

Build the program with the make file or with the following:
```
$ make all
```

## Running

Run the program with:
```
$ ./tsp
```
This will give you a menu of the commands you can choose to run. Use the commands after ./sorting

For example,
```
$ ./tsp -h
```
will return the help menu of the lab.

```
$ ./tsp -i [names].graph
```
will return the the shortest path and the route given the .graph file.

## Command line options

* -h: Prints out a help message describing the purpose of the graph and the command-line options it accepts, exiting the program afterwards. Refer to the reference program in the resources repo for an idea of what to print.
* -v : Enables verbose printing. If enabled, the program prints out all Hamiltonian paths found as well as the total number of recursive calls to dfs().
* -u: Specifies the graph to be undirected.
* -i infile: Specify the input file path containing the cities and edges of a graph. If not specified, the default input should be set as stdin.
* -o outfile: Specify the output file path to print to. If not specified, the default output should be set as stdout.

## Files

* graph.c - A source file for implementing the graph of ADT.
* path.c - A source file for implementing the path ADT.
* stack.c - A source file for implementing my stack ADT.
* tsp.c - A source file that has my main function and every other function needed for my program.
* graph.h - A header file that specifies the interface for graph.c.
* path.h - A header file that specifies the interface for path.c.
* stack.h - A header file that specifies the interface for stack.c.
* vertices.h - A header file that contains macros regarding vertices.
* Makefile - This allows us to use clang and compile our program.
* README.md - A file that shows how to build and run the program.
* DESIGN.pdf - The process of how I implemented my code

## Errors

One potential error is that when you input more than 3 numbers for the path. The program accepts the three values as i, j, k and if it askes for more than it will potentially break. If any non number values are in the file when it is supposed to be numbers then it will crash as well.
