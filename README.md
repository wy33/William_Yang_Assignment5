# Assignment 5

## Information about the repository

This repository contains the following:
- `graph.h`
- `CreateGraphAndTest.cc`
- `FindPaths.cc`

## Parts of the program completed

All parts completed.

`graph.h`
The graph.h file contains 3 core classes (2 visible, 1 embedded inside another).
Classes: Edges, Vertex, and Graph.
**Edges**
Edges is a class used to aid in the creation of Graph objects. The constructor of the Graph class requires a vector of Edges.
Each Edges object contains a vertex value and its connected vertices (vertex value and distance) that it is connected to.

**Vertex (Embedded inside Graph class)**
Vertex is a class used to represent the vertices of the graph. The 

**Graph**


`CreateGraphAndTest.cc`

`FindPaths.cc`


## Bugs encountered

No noticeable bugs encountered.

## Input File

`graph1.txt`
`graph2.txt`
`AdjacencyQueries1.txt`
`AdjacencyQueries2.txt`

## Running the assignment

Use provided `Makefile` for Homework 5.

To compile on terminal, type:

```bash
make
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make CreateGraphAndTest
```

```bash
make FindPaths
```

To delete executables and object files, type:

```bash
make clean
```

To run CreateGraphAndTest, type:

```bash
./CreateGraphAndTest <graph file> <adjacency query file>
```

```bash
./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt
```

```bash
./CreateGraphAndTest Graph2.txt AdjacencyQueries2.txt
```

To run FindPaths, type:

```bash
./FindPaths <graph file> <starting vertex integer>
```

```bash
./FindPaths Graph2.txt 1
```
