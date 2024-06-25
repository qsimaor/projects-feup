#ifndef VERTEX_EDGE
#define VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex **************************/

class Vertex {
public:
    /**
     * Constructor of the Vertex class.
     *
     * @param name The name of the vertex (train station).
     */
    Vertex(int name);

    /**
     * Constructor of the Vertex class with longitude and latitude information.
     *
     * @param name The name of the vertex (train station).
     * @param lon The longitude of the vertex.
     * @param lat The latitude of the vertex.
     */
    Vertex(int name, double lon, double lat);

    /**
     * Gets the name of the vertex (train station).
     *
     * @return The name of the vertex.
     */
    int getName() const;

    /**
     * Gets all the outgoing edges from this vertex.
     *
     * @return A vector of edges representing the outgoing connections from this vertex.
     */
    std::vector<Edge*> getAdj() const;

    /**
     * Gets the latitude of the vertex.
     *
     * @return The latitude of the vertex.
     */
    double getLatitude() const;

    /**
     * Gets the longitude of the vertex.
     *
     * @return The longitude of the vertex.
     */
    double getLongitude() const;

    /**
     * Gets the incoming edges to this vertex.
     *
     * @return A vector of edges representing the incoming connections to this vertex.
     */
    std::vector<Edge*> getIncoming() const;

    /**
     * Sets the name of the vertex.
     *
     * @param name The name of the vertex.
     */
    void setName(int name);

    /**
     * Adds an outgoing edge from this vertex to the specified destination vertex with the given weight.
     *
     * @param dest The destination vertex.
     * @param w The weight/capacity of the edge.
     * @return The created edge.
     */
    Edge* addEdge(Vertex* dest, double w);

    /**
     * Removes the edge between this vertex and the vertex with the specified name.
     *
     * @param destName The name of the destination vertex.
     * @return True if the edge was successfully removed, or false if no such edge exists.
     */
    bool removeEdge(int destName);

protected:
    /**
     * The name of the vertex.
     */
    int name;

    /**
     * The longitude of the vertex.
     */
    double longitude;

    /**
     * The latitude of the vertex.
     */
    double latitude;

    /**
     * The outgoing edges from this vertex.
     */
    std::vector<Edge*> adj;

    /**
     * The incoming edges to this vertex.
     */
    std::vector<Edge*> incoming;
};

/********************** Edge ****************************/

class Edge {
public:
    /**
     * Constructor of the Edge class.
     *
     * @param orig The origin vertex of the edge.
     * @param dest The destination vertex of the edge.
     * @param w The weight/capacity of the edge.
     */
    Edge(Vertex* orig, Vertex* dest, double w);

    /**
     * Gets the destination vertex of the edge.
     *
     * @return The destination vertex.
     */
    Vertex* getDest() const;

    /**
     * Gets the weight/capacity of the edge.
     *
     * @return The weight/capacity of the edge.
     */
    double getWeight() const;

    /**
     * Gets the origin vertex of the edge.
     *
     * @return The origin vertex.
     */
    Vertex* getOrig() const;

    /**
     * Sets the reverse edge of this edge.
     *
     * @param reverse The reverse edge.
     */
    void setReverse(Edge* reverse);

protected:
    /**
     * The destination vertex of the edge.
     */
    Vertex* dest;

    /**
     * The weight/capacity of the edge.
     */
    double weight;

    /**
     * The origin vertex of the edge.
     */
    Vertex* orig;

    /**
     * The reverse edge of this edge.
     */
    Edge* reverse;
};

#endif