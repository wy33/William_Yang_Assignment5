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

- Edges is a class used to aid in the creation of Graph objects. The constructor of the Graph class requires a vector of Edges.
- Each Edges object contains a vertex value and its connected vertices (vertex value and distance) that it is connected to.
- The class was given only one mutator (AddEdge) as to not mess up the order of the vector members.
- The class has accessors to view all members.

**Vertex (Embedded inside Graph class)**

- Vertex is a class used to represent the vertices of the graph. Each Vertex object will contain a list of vertices that it is adjacent to it (note: vertices in the adjacency list aren't treated as the same as the vertices in Graph class' ordered map member). 
- Only the members: value_ and distance_ for the vertices in the adjacent_ member matters. They are not meant to change and are there to note down the distances from the connected vertex object. While each vertex object in the ordered map has their members: known_, previous_in_path_ changed (and adjacent_ during insertion of adjacent vertices). This is because the Dijkstra function only alters the vertices in the ordered map and not its list member of vertices.
- Although the member previous_in_path_ is a pointer, it is only meant to point to the address of a vertex in the ordered map (and does not allocate new memory), so when the destructor is called, there is no delete called (only set to nullptr) since the ordered map's destructor should delete the memory (if it dynamically allocates). This is to avoid 2 delete calls to be made.
- Vertex Constructors/assignment operators: the pointer member (to another vertex) is always set to nullptr because the path will be altered by the DijkstraShortestPath() function in the Graph class. The pointer's value doesn't really matter as no functions other than the PrintShortestPaths() function (a follow up call after Dijkstra) accesses it.
- Operator<(): overloaded for purposes of comparison in the binary_heap.h priority queue.

**Graph**

- Graph is the main class. It is composed of 2 members, its size (integer) and the vertices represented by an ordered map (key is vertex value, stored object is Vertex).
- An ordered map was chosen to store the vertices with flexibility in mind. If a vertex's name/value becomes a string, the Graph class should function the same provided the necessary changes are made. Perhaps the Graph class could've been templated to so that this could've been determined during runtime, but this class was designed to specifically for the HW's graph file format for the graphs.
- DijkstraShortestPath(): there is a public version that takes an integer (that represents the vertex) and a private version that takes a reference to the vertex in the ordered map member. The public version calls the private version after verifying that there is indeed a vertex of the given value. The function modifies the vertices (known_ and previous_in_path_) in the ordered map member vertices_, and only reads from each vertices' adjacency list without modifying any values in the list. During the computation, a function cost() is called, it isn't necessary, but was included to adhere to the style of the pseudocode that was presented in class. After running the algorithm, the function immediately prints the result of the run by calling the PrintShortestPaths() function.

`CreateGraphAndTest.cc`
- CreateGraph(): reads the provided graph file to create the Graph object, then returns it.
- QueryAdjacency(): reads query file and queries the supplied Graph object.
- graphTestDriver(): parses arguments into strings and calls CreateGraph() and QueryAdjacency() to query the graph.


`FindPaths.cc`
- CreateGraph(): reads the provided graph file to create the Graph object, then returns it (same function as one in CreateGraphAndTest.cc).
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
