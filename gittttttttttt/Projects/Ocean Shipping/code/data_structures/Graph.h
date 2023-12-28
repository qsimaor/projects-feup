#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stack>
#include <fstream>
#include <unordered_map>
#include <set>
#include "VertexEdge.h"
#define EARTH_RADIUS (double)6371000.0

/**
 * @class Graph
 * @brief Represents a graph (train network) with vertices and edges.
 *
 * The Graph class represents a graph (train network) using a collection of vertices and edges.
 * It provides various methods for adding vertices and edges, parsing graph data from files,
 * solving the traveling salesman problem, and finding the minimum spanning tree.
 */
class Graph {
public:
    /**
     * @brief Default constructor for the Graph class.
     *
     * This constructor initializes an empty graph.
     * Time Complexity: O(1).
     */
    Graph();

    /**
     * @brief Finds a vertex with the specified name.
     *
     * This function searches for a vertex with the given name in the graph.
     *
     * @param name The name of the vertex to find.
     * @return A pointer to the vertex if found, or nullptr if not found.
     * Time Complexity: O(V) [V = Number of Vertices].
     */
    Vertex* findVertex(int name) const;

    /**
     * @brief Adds a vertex with the specified name to the graph.
     *
     * This function adds a vertex with the given name to the graph.
     *
     * @param name The name of the vertex to add.
     * @return True if the vertex was added successfully, or false if a vertex with the same name already exists.
     * Time Complexity: O(V) [V = Number of Vertices].
     */
    bool addVertex(const int& name);

    /**
     * @brief Adds a vertex with the specified name, longitude, and latitude to the graph.
     *
     * This function adds a vertex with the given name, longitude, and latitude to the graph.
     *
     * @param name The name of the vertex to add.
     * @param longitude The longitude of the vertex's location.
     * @param latitude The latitude of the vertex's location.
     * @return True if the vertex was added successfully, or false if a vertex with the same name already exists.
     * Time Complexity: O(V) [V = Number of Vertices].
     */
    bool addVertex(const int& name, double longitude, double latitude);

    /**
     * @brief Adds a unidirectional edge between two vertices with the specified names and capacity to the graph.
     *
     * This function adds a unidirectional edge between the source vertex and the target vertex with the given names and capacity to the graph.
     *
     * @param ori The name of the source vertex.
     * @param dest The name of the target vertex.
     * @param cap The capacity of the edge.
     * @return True if the edge was added successfully, or false if the source or destination vertex does not exist.
     * Time Complexity: O(V) [V = Number of Vertices].
     */
    bool addEdge(const int& ori, const int& dest, double cap);

    /**
     * @brief Adds a bidirectional edge between two vertices with the specified names and capacity to the graph.
     *
     * This function adds a bidirectional edge between the first vertex and the second vertex with the given names and capacity to the graph.
     *
     * @param ori The name of the first vertex.
     * @param dest The name of the second vertex.
     * @param cap The capacity of the edge.
     * @return True if the edge was added successfully, or false if the source or destination vertex does not exist.
     * Time Complexity: O(V) [V = Number of Vertices].
     */
    bool addBidirectionalEdge(const int& ori, const int& dest, double cap);

    /**
     * @brief Gets the number of vertices in the graph.
     *
     * This function returns the number of vertices (stations) in the graph (train network).
     *
     * @return The number of vertices in the graph.
     * Time Complexity: O(1).
     */
    int getNumVertex() const;

    /**
     * @brief Gets the vector of all vertices in the graph.
     *
     * This function returns the vector of all vertices in the graph (train network).
     *
     * @return The vector of all vertices in the graph.
     * Time Complexity: O(1).
     */
    std::vector<Vertex*> getVertexSet() const;

    /**
     * @brief Parses graph data from a file in one-file format.
     *
     * This function parses the graph data from a file in one-file format, where each line represents an edge with the format:
     * "source_vertex, target_vertex, capacity".
     *
     * @param file_p The path of the file to parse.
     * @return True if the parsing was successful, or false if the file could not be opened or the format is incorrect.
     * Time Complexity: O(V + E) [V = Number of Vertices, E = Number of Edges].
     */
    bool parser_onefile(const std::string& file_p);

    /**
     * @brief Parses graph data from files in two-file format.
     *
     * This function parses the graph data from files in two-file format, where one file contains the edges and the other file contains the vertices.
     * The edges file should have each line representing an edge with the format: "source_vertex, target_vertex, capacity".
     * The vertices file should have each line representing a vertex with the format: "vertex_name, longitude, latitude".
     *
     * @param edges_p The path of the file containing the edges.
     * @param nodes_p The path of the file containing the vertices.
     * @return True if the parsing was successful, or false if the files could not be opened or the formats are incorrect.
     * Time Complexity: O(V + E) [V = Number of Vertices, E = Number of Edges].
     */
    bool parser_twofiles(const std::string& edges_p, const std::string& nodes_p);

    /**
     * @brief Removes a vertex from the graph.
     *
     * This function removes the vertex with the specified name from the graph along with its associated edges.
     *
     * @param s The name of the vertex to remove.
     * Time Complexity: O(V + E) [V = Number of Vertices, E = Number of Edges].
     */
    void removeVertex(int s);

    /**
     * @brief Solves the traveling salesman problem (TSP) using a backtracking algorithm.
     *
     * This function finds the minimum cost Hamiltonian cycle (closed path) in the graph using a backtracking algorithm.
     * It prints the minimum distance and the execution time.
     * Time Complexity: O(2^V * V^2) [V = Number of Vertices].
     */
    void backtrack_tsp();

    /**
     * @brief Recursive function for the traveling salesman problem (TSP) backtracking algorithm.
     *
     * This function is a helper function for the `backtrack_tsp` function.
     * It recursively explores all possible paths to find the minimum cost Hamiltonian cycle (closed path) in the graph.
     *
     * @param path The current path being explored.
     * @param visited A boolean vector indicating which vertices have been visited.
     * @param min_cost The minimum cost found so far.
     * @param cost_so_far The current cost of the path.
     */
    void backtrack_tsp_rec(std::vector<int>& path, std::vector<bool>& visited, double& min_cost, double cost_so_far);

    /**
     * @brief Finds the minimum spanning tree (MST) of the graph using Prim's algorithm.
     *
     * This function finds the minimum spanning tree of the graph using Prim's algorithm and returns a vector of edges in the MST.
     *
     * @param parent A vector to store the parent vertices of each vertex in the MST.
     * @return A vector of pairs representing the edges in the minimum spanning tree.
     * Time Complexity: O(V^2 + E) [V = Number of Vertices, E = Number of Edges].
     */
    std::vector<std::pair<int, int>> primMST(std::vector<int>& parent);

    /**
     * @brief Performs the triangular approximation algorithm for the traveling salesman problem (TSP).
     *
     * This function approximates the minimum cost Hamiltonian cycle in the graph using the triangular approximation algorithm.
     * It prints the optimal cost and the execution time.
     * Time Complexity: O(V^3) [V = Number of Vertices].
     */
    void triangularApproximation();

protected:
    /**
     * @brief Vector that stores the vertices (Vertex) of the graph.
     */
    std::vector<Vertex*> vertexSet; // vertex set

    /**
     * @brief Calculates the total distance of a given path in the graph.
     *
     * This function calculates the total distance of a given path in the graph by summing the weights of the edges in the path.
     *
     * @param path The path represented as a vector of vertex names.
     * @return The total distance of the path.
     */
    double calculateTotalDistance(const std::vector<int>& path);

    /**
     * @brief Checks if two nodes in the graph are connected by an edge.
     *
     * This function checks if two nodes in the graph are connected by an edge.
     *
     * @param v1 The name of the first node.
     * @param v2 The name of the second node.
     * @return True if the nodes are connected, or false otherwise.
     */
    bool check_if_nodes_are_connected(int v1, int v2);

    /**
     * @brief Calculates the haversine distance between two coordinates.
     *
     * This function calculates the haversine distance between two coordinates using their latitude and longitude.
     *
     * @param lat1 The latitude of the first coordinate.
     * @param lon1 The longitude of the first coordinate.
     * @param lat2 The latitude of the second coordinate.
     * @param lon2 The longitude of the second coordinate.
     * @return The haversine distance between the coordinates.
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Performs a depth-first search (DFS) starting from a given vertex.
     *
     * This function performs a depth-first search (DFS) starting from a given vertex and updates the visited nodes and the path.
     *
     * @param current The current vertex being visited.
     * @param parent The vector storing the parent vertices in the DFS.
     * @param visited The vector indicating which vertices have been visited.
     * @param cityStack The stack for DFS traversal.
     * @param path The resulting path from the DFS traversal.
     * Time Complexity: O(V + E) [V = Number of Vertices, E = Number of Edges]
     */
    void dfs(int current, const std::vector<int>& parent, std::vector<bool>& visited, std::stack<int>& cityStack, std::vector<int>& path);
};

#endif