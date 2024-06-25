#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "VertexEdge.h"
using namespace std;

class Graph {
public:
    /**
     * Constructor of the graph class.
     * Time Complexity: O(1).
     */
    Graph();
    /**
     * Auxiliary function to find a vertex with a given ID.
     * Time Complexity: O(V) [V = Number of Vertices].
     * @param name String that represents the Vertex and the name of the train station.
     * @return Vertex of a graph represented by the string name.
     */
    Vertex *findVertex(string name) const;
    /**
     * Adds a vertex to a graph, with given info about a specific train station.
     * Time Complexity: O(V) [V = Number of Vertices].
     * @param name String that represents the Vertex and stores the name of the train station.
     * @param district String that stores the name of the district of the train station.
     * @param municipality String that stores the name of the municipality of the train station.
     * @param township String that stores the name of the township of the train station.
     * @param line String that stores the name of the line that the train station is from.
     * @return Returns true if successful, and false if a vertex with that name already exists.
     */
    bool addVertex(const string &name,const string &district,const string &municipality,const string &township,const string &line);
    /**
     * Adds an edge to a graph, with given info about a unidirectional connection between two train stations.
     * Time Complexity: O(V) [V = Number of Vertices].
     * @param sta_A String that stores the name of the source train station, that also represents a Vertex.
     * @param sta_B String that stores the name of the target train station, that also represents a Vertex.
     * @param cap Double that stores the capacity of this connection between two train stations.
     * @param service String that stores the type of service that happens between those stations (STANDARD or ALFA PENDULAR).
     * @return Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const string &sta_A, const string &sta_B, double cap, const string &service);
    /**
     * Adds an edge to a graph, with given info about a bidirectional connection between two train stations.
     * Time Complexity: O(V) [V = Number of Vertices].
     * @param sta_A String that stores the name of the first train station, that also represents a Vertex.
     * @param sta_B String that stores the name of the second train station, that also represents a Vertex.
     * @param cap Double that stores the capacity of this connection between two train stations.
     * @param service String that stores the type of service that happens between those stations (STANDARD or ALFA PENDULAR).
     * @return Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addBidirectionalEdge(const string &sta_A, const string &sta_B, double cap, const string &service);
    /**
     * Gets the number of vertices (stations) in the graph (train network).
     * Time Complexity: O(1).
     * @return Integer that stores the number of vertices (Vertex) in the graph.
     */
    int getNumVertex() const;
    /**
     *
     * @return
     */
    vector<Vertex *> getVertexSet() const;
    /**
     * Populates the graph with vertices (Vertex) and edges (Edge) given by reading the chosen files that contain that data.
     * Time Complexity: O(V + E) [V = Number of Vertices | E = Number of Edges].
     * @param stations_p String that stores the path to the file correspondent to the stations data.
     * @param network_p String that stores the path to the file correspondent to the network (connections) data.
     * @return Returns true if successful, and false if one of the paths doesn't work.
     */
    bool parser(string stations_p, string network_p);
    /**
     * Finds the maximum flow from a source vertex to a target vertex in a graph.
     * Time Complexity: O(V * E^2) [V = Number of Vertices | E = Number of Edges].
     * @param source String that stores the name of the source train station, that also represents a Vertex.
     * @param target String that stores the name of the target train station, that also represents a Vertex.
     * @return Double that stores the maximum flow between the two vertices (stations).
     */
    double edmondsKarp(string source, string target);
    /**
     * Finds the pairs that require the most amount of trains when taking full advantage of the network's capacity.
     * Time Complexity: O(V^3 * E^2) [V = Number of Vertices | E = Number of Edges].
     * @return Vector that stores pairs of pairs of two strings (representing two stations) and a double (representing the max. flow between those two stations).
     */
    vector<pair<pair<string,string>,double>> getPairs_MostAmountOfTrains();
    /**
     * Finds the top-k municipalities that need more budget to sustain its services.
     * Time Complexity: O(V^2 * E^2) [V = Number of Vertices | E = Number of Edges].
     * @param k Integer that stores the desired size of the top list.
     * @return Sorted vector that stores pairs of a string (representing a municipality) and a double (representing the sum of the max. flow between all the pairs of the stations of the municipality).
     */
    vector<pair<string,double>> budgetMunicipalities(int k);
    /**
     * Finds the top-k districts that need more budget to sustain its services.
     * Time Complexity: O(V^2 * E^2) [V = Number of Vertices | E = Number of Edges].
     * @param k Integer that stores the desired size of the top list.
     * @return Sorted vector that stores pairs of a string (representing a district) and a double (representing the sum of the max. flow between all the pairs of the stations of the district).
     */
    vector<pair<string,double>> budgetDistricts(int k);
    /**
     * Calculates the maximum number of trains that can simultaneously arrive at a given station.
     * Time Complexity: O(V * E^2) [V = Number of Vertices | E = Number of Edges].
     * @param station String that stores the name of the chosen train station, that also represents a Vertex.
     * @return Double that stores the maximum number of trains that can simultaneously arrive at the given station.
     */
    double maxTrainsAtStation(string station);
    /**Calculates the maximum number of trains that can simultaneously travel between stations with minimum cost for the company.
     * Time Complexity: O(f * (V+E)) [V = Number of Vertices | E = Number of Edges| f = maximum flow].
     * @param station1 String that stores the name of the source train station, that also represents a Vertex.
     * @param station2 String that stores the name of the target train station, that also represents a Vertex.
     */
    void max_trains_min_cost(string station1, string station2);
    /**
     * Removes a Vertex from the vertexSet and removes the edges that are associated with it.
     * Time Complexity: O(V + E) [V = Number of Vertices | E = Number of Edges].
     * @param s String that stores the name of the chosen train station, that also represents a Vertex.
     */
    void removeVertex(string s);
    /**
     * Calculates which stations will be more impacted after a failure in the Graph.
     * Time Complexity: O(V) [V = Number of Vertices].
     * @param f Graph that stores the desired failures that will be tested.
     * @param k Integer that stores the desired size of the top list.
     * @return Vector of pairs of a string that represents a Vertex and a double that represent the difference of max flow at station after the the failure.
     */
    vector<pair<string,double>> differenceMaxFlowFailures(Graph f,int k);

protected:
    /**
     * @brief Vector that stores the vertices (Vertex) of a graph.
     */
    std::vector<Vertex *> vertexSet;    // vertex set

    void testAndVisit(queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    bool findAugmentingPath(Vertex *s, Vertex *t);
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
    int maxFlow_minCost(string source, string target);
    bool bfs_for_max_flow(Vertex *s, Vertex *t);
};
#endif