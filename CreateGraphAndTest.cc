// William Yang
// CreateGraphAndTest.cc: a file to test the creation of a Graph object
// and query adjacencies for the graph.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>

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
        if(graph_file.peek() == ' ')
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
    graph_file.close();

    Graph graph { edges };
    return graph;
}

// Query adjacency in supplied graph object.
void QueryAdjacency(Graph& graph, const string& query_filename) {
    fstream query_file(query_filename);
    // If query file fails to open, throw error
    if (!query_file.is_open())
    {
        cerr << "Failed to open query file." << endl;
        exit(1);
    }

    int start_vertex;
    int end_vertex;
    // Query graph for adjacency
    while (query_file >> start_vertex >> end_vertex)
    {
        cout << start_vertex << ' ' << end_vertex << ": ";
        if (graph.AdjacencyQuery(start_vertex, end_vertex))
            cout << "connected" << ' ' << fixed << setprecision(1) 
            << graph.DistanceBetween(start_vertex, end_vertex) << endl;
        else
            cout << "not_connected" << endl;
    }
    query_file.close();
}

// Driver for creating and querying graph.
int graphTestDriver(int argc, char** argv) {
    const string graph_filename(argv[1]);
    const string query_filename(argv[2]);

    Graph graph = CreateGraph(graph_filename);
    QueryAdjacency(graph, query_filename);

    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
        return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
