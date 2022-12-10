#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "graph.h"

using namespace std;



// Create the graph object.
// Extract the vertices and their adjacencies from the graph file
// and return the created Graph.
Graph CreateGraph(const string& graph_filename) {
    fstream graph_file(graph_filename);
    // If file fails to open, throw error
    if (!graph_file.is_open())
    {
        cerr << "Failed to open graph file." << endl;
        exit(1);
    }

    int number_of_vertices;
    graph_file >> number_of_vertices;   // Get number of vertices in file

    int vertex_value;
    vector<Edges> edges;    // All vertices and their edges
    // Extract adjacency lists in file
    while (graph_file >> vertex_value)
    {
        float distance = 0.0f;
        Edges new_vertex { vertex_value };
        if (graph_file.peek() == ' ')
            graph_file.ignore(1, ' ');

        // Read line by line (the adjacent vertices)
        while (graph_file.peek() != '\n' && graph_file.peek() != '\r' &&
            graph_file.peek() != graph_file.eof())  // If not newline character or end of file, more adjacent vertices
        {
            // Confirm that an adjacent vertex and its distance is read
            if (!(graph_file >> vertex_value >> distance))
                break;
            new_vertex.AddEdge(vertex_value, distance);
        }
        edges.push_back(new_vertex);
    }

    Graph graph { edges };
    return graph;
}

// Run Dijkstra's Shortest Path Algorithm for the given graph
// using the given starting vertex.
void FindShortestPath(Graph& graph, const int& start) {
    graph.DijkstraShortestPath(start);
}

// Driver for creating graph and running Dijkstra's Algorithm.
int pathfindDriver(int argc, char** argv) {
    const string graph_filename(argv[1]);
    const int starting_vertex(stoi(argv[2]));

    Graph graph = CreateGraph(graph_filename);
    FindShortestPath(graph, starting_vertex);

    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
        return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
