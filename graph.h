// William Yang
// graph.h: An adjacency list-based graph and all its required components.

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <list>
#include <limits>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <stack>



// Class Edges:
// Class to represent a vertex and all its edges
// Vertex is directed (connected one way to its adjacent vertices).
class Edges {
public:
	Edges() = delete;	// Delete default constructor

	// One parameter constructor.
	// Initialize starting vertex.
	explicit Edges(const int& start) : start_vertex_(start)
	{}

	// Add edge/adjacent vertex
	void AddEdge(const int& end, const float& dis)
	{
		end_vertex_.push_back(end);
		distance_.push_back(dis);
		size_++;
	}

	// Return starting vertex
	int StartVertex() const
	{
		return start_vertex_;
	}

	// Return number of adjacent vertices (size)
	int Size() const
	{
		return size_;
	}
	
	// Return end vertices vector
	const std::vector<int>& EndVertices() const
	{
		return end_vertex_;
	}

	// Return end vertices' distances vector
	const std::vector<float>& Distances() const
	{
		return distance_;
	}

private:
	int start_vertex_ = 0;			// Starting vertex
	int size_ = 0;					// Number of edges
	std::vector<int> end_vertex_;	// All the vertices connected to start vertex
	std::vector<float> distance_;	// All the distances associated with each end vertex
};	// Edges class



// Class Graph:
// An adjacency list-based directed graph capable of finding the shortest path to each vertex
// and can be queried for adjacent vertices (directed).
class Graph {
public:
	// Default constructor
	explicit Graph() : size_(0)
	{}

	// Copy constructor
	Graph(const Graph& rhs) : vertices_(rhs.vertices_), size_(rhs.size_)
	{}

	// Move constructor
	Graph(Graph&& rhs) : vertices_(std::move(rhs.vertices_)), size_(std::move(rhs.size_))
	{}

	// Destructor
	~Graph()
	{
		MakeEmpty();
	}

	// Copy assignment
	Graph& operator=(const Graph& rhs)
	{
		Graph copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	// Move assignment
	Graph& operator=(Graph&& rhs)
	{
		vertices_ = std::move(rhs.vertices_);
		size_ = std::move(rhs.size_);
		return *this;
	}

	// One parameter constructor.
	// Immediately generates graph.
	explicit Graph(const std::vector<Edges>& edges): size_(edges.size())
	{
		CreateGraph(edges);
	}

	// Create the adjacency list graph (clears the old graph, empty or otherwise).
	// edges: a collection of all vertices and their respective edges
	//		needed to create the graph.
	void CreateGraph(const vector<Edges>& edges)
	{
		MakeEmpty();
		size_ = edges.size();

		// Loop through each edges object and add the edges to its respective vertex.
		for (size_t i = 0; i < edges.size(); i++)
		{
			AddVertex(edges[i].StartVertex());
			AddAdjacentVertices(edges[i], edges[i].StartVertex());
		}
	}

	// Clear the graph
	void MakeEmpty()
	{
		vertices_.clear();
		size_ = 0;
	}
	
	// Return the size of graph (number of vertices)
	int Size() const
	{
		return size_;
	}

	// Query adjaceny between a 2 vertices (directed).
	// If distance between start vertex is connected to end vertex,
	// return true; else false.
	bool AdjacencyQuery(const int& start, const int& end) const
	{
		// If distance is float min, one/both of the vertices don't exist
		// or are not connected; thus return false.
		if (DistanceBetween(start, end) == std::numeric_limits<float>::min())
			return false;
		return true;	// Start vertex is connected to end vertex.
	}

	// If start vertex is connected to end vertex (directed),
	// return distance; else return std::numeric_limits<float>::min() to signal
	// start vertex isn't connected to end vertex or
	// one/both of them doesn't exist.
	float DistanceBetween(const int& start, const int& end) const
	{
		// Start vertex doesn't exist or end vertex doesn't exist,
		// thus not connected to each other.
		if (vertices_.find(start) == vertices_.end() || vertices_.find(end) == vertices_.end())
			return std::numeric_limits<float>::min();

		// Match end vertex with one in adjacency list and return its distance.
		for (const Vertex& v : vertices_.at(start).adjacent_)
			if (v.value_ == end)
				return v.distance_;
		return std::numeric_limits<float>::min();
	}

	// Dijkstra's algorithm for shortest path.
	void DijkstraShortestPath(const int& start)
	{
		// Vertex does not exist, throw error.
		if (!FindVertex(start))
		{
			std::cerr << "Starting vertex " << start << " does not exist." << std::endl;
			exit(1);
		}
		else // Vertex exists, run Dijkstra's algorithm.
			DijkstraShortestPath(vertices_.at(start));
	}

	// Prints the adjacency lists of all vertices in graph.
	// Format:		1: 2 3 4
	//				2: 
	//				3: 5 6
	//				...
	void PrintAdjacencyLists() const
	{
		// Return if graph is empty
		if (size_ == 0)
		{
			std::cout << "Graph is empty, nothing to print." << std::endl;
			return;
		}

		// Loop through the pairs in map (pair<int, Vertex>)
		for (auto& v : vertices_)
		{
			std::cout << v.second.value_ << ':';
			for (const Vertex& w : v.second.adjacent_)
			{
				std::cout << ' ' << w.value_;
			}
			std::cout << std::endl;
		}
	}



private:
	// Vertex class
	struct Vertex {
		int value_;						// Vertex value
		std::list<Vertex> adjacent_;	// Adjacency list (not modified by Dijkstra algorithm being run)
		float distance_;				// Distance from starting vertex
		bool known_ = false;			// Flag for visited or not (Only gets modified by Dijkstra algorithm)
		Vertex* previous_in_path_;		// Previous vertex on shortest path (Only gets modified by Dijkstra algorithm)

		// Default constructor
		Vertex(const int& val = 0, const float& dis = 0.0f)
			: value_(val), distance_(dis), known_(false), previous_in_path_(nullptr)
		{}

		// Copy constructor
		Vertex(const Vertex& rhs) : value_(rhs.value_), adjacent_(rhs.adjacent_),
			distance_(rhs.distance_), known_(rhs.known_), previous_in_path_(nullptr)
		{}

		// Move constructor
		Vertex(Vertex&& rhs) : value_(std::move(rhs.value_)), adjacent_(std::move(rhs.adjacent_)),
			distance_(std::move(rhs.distance_)), known_(std::move(rhs.known_)),
			previous_in_path_(std::move(rhs.previous_in_path_))
		{
			previous_in_path_ = nullptr;
			rhs.previous_in_path_ = nullptr;
		}

		// Destructor
		~Vertex()
		{
			adjacent_.clear();
			value_ = 0;
			distance_ = 0.0f;
			known_ = false;
			previous_in_path_ = nullptr;
		}

		// Copy assignment
		Vertex& operator=(const Vertex& rhs)
		{
			Vertex copy = rhs;
			std::swap(*this, copy);
			previous_in_path_ = nullptr;
			return *this;
		}

		// Move assignment
		Vertex& operator=(Vertex&& rhs)
		{
			value_ = std::move(rhs.value_);
			distance_ = std::move(rhs.distance_);
			adjacent_ = std::move(rhs.adjacent_);
			known_ = std::move(rhs.known_);
			previous_in_path_ = std::move(rhs.previous_in_path_);
			previous_in_path_ = nullptr;
			rhs.previous_in_path_ = nullptr;
			return *this;
		}

		// Add an adjacent vertex to list of adjacencies.
		void AddAdjacentVertex(const Vertex& adjacent_vertex)
		{
			adjacent_.push_back(adjacent_vertex);
		}

		// Overload < operator for Vertex class.
		// Comparison is based on vertex's distance.
		bool operator<(const Vertex& rhs) const
		{
			return distance_ < rhs.distance_;
		}
	};	// Vertex class



	// Graph Class Members
	std::map<int, Vertex> vertices_;	// Adjacency list graph
	int size_;							// Number of vertices in graph



	// Add new vertex to graph.
	void AddVertex(const int& val)
	{
		vertices_[val] = Vertex{ val };
	}

	// Add adjacent vertices to an existing vertex's adjacency list
	// given the edges of the respective vertex.
	void AddAdjacentVertices(const Edges& edges, const int& val)
	{
		for (int i = 0; i < edges.Size(); i++)
		{
			vertices_.at(val).AddAdjacentVertex(Vertex { edges.EndVertices()[i], edges.Distances()[i] } );
		}
	}

	// Find vertex given its value
	bool FindVertex(const int& val) const
	{
		if (vertices_.find(val) != vertices_.end())
			return true;	// Found
		return false;	// Not Found
	}

/*	This function is viable if Vertex class is a public class of its own.

	// Find vertex given a vertex object (
	bool FindVertex(const Vertex& v) const
	{
		if (vertices_.find(v.value_) != vertices_.end())
			return true;	// Found
		return false;	// Not Found
	}
*/

	// Find the cost from vertex v to vertex w.
	// Vertex v is the referenced vertex from the member vertices_
	// Vertex w is directly referenced from v's adjacency list.
	float cost(const Vertex& v, const Vertex& w) const
	{
		return w.distance_;
	}

	// Print shortest paths of starting vertex to all vertices
	// in graph after running Dijkstra algorithm.
	// Starting vertex is determined when running Dijkstra,
	// thus this function is meant to be a followup call after running Dijkstra.
	void PrintShortestPaths() const
	{
		std::stack<int> path;
		// Loop through vertices in map (pair<int, Vertex>)
		for (auto& v : vertices_)
		{
			std::cout << v.first << ':';
			Vertex* prev = v.second.previous_in_path_;

			// No valid path exists to vertex
			if (prev == nullptr && v.second.distance_ != 0.0f)
			{
				std::cout << " not_possible" << std::endl;
				continue;
			}


			// Valid path exists
			path.push(v.first);
			while (prev)
			{
				path.push(prev->value_);
				prev = prev->previous_in_path_;
			}

			// Print path and reset stack
			while (!path.empty())
			{
				std::cout << ' ' << path.top();
				path.pop();
			}

			// Print distance of path to vertex
			std::cout << " cost: " << fixed << setprecision(1) << v.second.distance_ << std::endl;
		}
	}

	// Dijkstra's Shortest Path Algorithm.
	// Given a starting vertex, run algorithm and find the shortest path to every
	// vertex in the graph from starting vertex.
	// Then print the results of the run.
	void DijkstraShortestPath(Vertex& start)
	{
		// Set all vertices':
		// distance_ = INFINITY
		// known_ = false
		// previous_in_path_ = nullptr
		for (std::map<int, Vertex>::iterator i = vertices_.begin(); i != vertices_.end(); i++)
		{
			i->second.distance_ = std::numeric_limits<float>::max();	// INFINITY
			i->second.known_ = false;
			i->second.previous_in_path_ = nullptr;
		}

		start.distance_ = 0.0f;	// Starting vertex's distance to itself is 0
		BinaryHeap<Vertex> priority_queue;
		priority_queue.insert(start);
		Vertex v;	// Copy of vertex to enqueue and dequeue

		while (true)
		{
			bool success = false;

			while (!priority_queue.isEmpty() && !success)
			{
				priority_queue.deleteMin(v);	// Dequeue vertex into v
				if (!v.known_)	// Prevents re-reading an already read vertex
					success = true;
			}
			if (!success)	// All vertices read, end Dijkstra
				break;
			v.known_ = true;	// Vertex visited

			// Compare distances and choose shortest route
			for (const Vertex& w : v.adjacent_)
			{
				if (!vertices_.at(w.value_).known_)
				{
					const auto new_distance_through_v = v.distance_ + cost(v, w);
					if (new_distance_through_v < vertices_.at(w.value_).distance_)
					{
						vertices_.at(w.value_).distance_ = new_distance_through_v; // Decrease w.distance_
						priority_queue.insert(vertices_.at(w.value_));
						vertices_.at(w.value_).previous_in_path_ = &vertices_.at(v.value_);
					}
				}
			} // end of for each Vertex w
		} // end of while (true)
		PrintShortestPaths();	// Print the result (shortest paths to each vertex)
	}
};

#endif	// STUDENT_GRAPH
