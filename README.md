# Assignment 5

## Information about the repository

This repository contains the following:
- `graph.h`
- `CreateGraphAndTest.cc`
- `FindPaths.cc`

## Parts of the program completed

All parts completed.

`graph.h`
- The graph.h file contains 3 core classes (2 visible, 1 embedded inside another).
Classes: Edges, Vertex, and Graph.

**Edges**

Edges is a class used to aid in the creation of Graph objects. The constructor of the Graph class requires a vector of Edges.
Each Edges object contains a vertex value and its connected vertices (vertex value and distance) that it is connected to.

**Vertex (Embedded inside Graph class)**

Vertex is a class used to represent the vertices of the graph. Each Vertex object will contain a list of vertices that it is adjacent to it (note: vertices in the adjacency list aren't treated as the same as the vertices in Graph class' ordered map member).

**Graph**

Graph is the main class. It is composed of 2 members, its size (integer) and the vertices represented by an ordered map (key is vertex value, stored object is Vertex). An ordered map was chosen to store the vertices with flexibility in mind. If a vertex's name/value becomes a string, the Graph class should function the same provided the necessary changes are made. Perhaps the Graph class could've been templated to so that this could've been determined during runtime, but this class was designed to specifically for HW's format for the graphs.

`CreateGraphAndTest.cc`
- CreateGraph(): reads the provided graph file to create the Graph object, then returns it.
- QueryAdjacency(): reads query file and queries the supplied Graph object.
- graphTestDriver(): parses arguments into strings and calls CreateGraph() and QueryAdjacency() to query the graph.


`FindPaths.cc`
- CreateGraph(): reads the provided graph file to create the Graph object, then returns it.
- pathfindDriver(): parses arguments into strings and calls CreateGraph() and FindShortestPath() to run Dijkstra's Algorithm.

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
