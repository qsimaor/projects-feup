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

/************************* Vertex  **************************/

class Vertex {
public:
    /**
     * Constructor of the Vertex class storing all the information about a train station.
     * Time Complexity: O(1).
     * @param name String that represents the Vertex and stores the name of the train station.
     * @param district String that stores the name of the district of the train station.
     * @param municipality String that stores the name of the municipality of the train station.
     * @param township String that stores the name of the township of the train station.
     * @param line String that stores the name of the line that the train station is from.
     */
    Vertex(string name,string district, string municipality,string township,string line);
    /**
     * Secondary constructor of the Vertex class for testing/calculating purposes.
     * Time Complexity: O(1).
     * @param name String that represents the Vertex and stores the name of the train station.
     */
    Vertex(string name);

    /**
     * Gets the name of a Vertex (train station).
     * Time Complexity: O(1).
     * @return String that represents the Vertex and stores the name of the train station.
     */
    string getName() const;
    /**
     * Gets all the connections between this Vertex (train station) and others.
     * Time Complexity: O(1).
     * @return Vector of Edge's that connect from this Vertex to another one.
     */
    std::vector<Edge *> getAdj() const;
    /**
     * Checks if this Vertex was visited.
     * Time Complexity: O(1).
     * @return Boolean (true/false) whether if it was visited or not.
     */
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    /**
     * Gets this Vertex's path.
     * Time Complexity: O(1).
     * @return Edge that corresponds to the Vertex's path.
     */
    Edge *getPath() const;
    /**
     * Gets this Vertex's (train station) municipality.
     * Time Complexity: O(1).
     * @return String that stores the name of the municipality of the train station.
     */
    string getMunicipality() const;
    /**
     * Gets this Vertex's (train station) district.
     * Time Complexity: O(1).
     * @return String that stores the name of the district of the train station.
     */
    string getDistrict() const;
    /**
     * Gets this Vertex's (train station) incoming connections (Edge's).
     * Time Complexity: O(1).
     * @return Vector that stores all the incoming Edge's of this Vertex.
     */
    std::vector<Edge *> getIncoming() const;

    void setName(string name);
    /**
     * Set if the Vertex was visited or not.
     * Time Complexity: O(1).
     * @param visited Boolean (true/false) whether if it was visited or not.
     */
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    /**
     * Set this Vertex's path.
     * Time Complexity: O(1).
     * @param path Edge that corresponds to the Vertex's path.
     */
    void setPath(Edge *path);
    /**
     * Creates and adds a edge with given parameters.
     * Time Complexity: O(1).
     * @param dest String that represents a Vertex and stores the name of the target train station.
     * @param w Double that stores the capacity of this connection between two train stations.
     * @param service String that stores the type of service that happens between those stations (STANDARD or ALFA PENDULAR).
     * @return Edge that was created by the given parameters.
     */
    Edge * addEdge(Vertex* dest, double w, string service);
    bool removeEdge(string destName);

protected:
    /**
     * @brief String that represents the Vertex and stores the name of the train station.
     */
    string name;
    /**
     * @brief String that stores the name of the district of the train station.
     */
    string district;
    /**
     * @brief String that stores the name of the municipality of the train station.
     */
    string municipality;
    /**
     * @brief String that stores the name of the township of the train station.
     */
    string township;
    /**
     * @brief String that stores the name of the line that the train station is from.
     */
    string line;
    /**
     * @brief Vector of Edge's that connect from this Vertex to another one (outgoing edges).
     */
    std::vector<Edge *> adj;  // outgoing edges
    /**
     * @brief Boolean (true/false) whether if this Vertex was visited or not.
     */
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    /**
     * @brief Edge that corresponds to the Vertex's path.
     */
    Edge *path = nullptr;
    /**
    * @brief Vector that stores all the incoming Edge's of this Vertex.
    */
    std::vector<Edge *> incoming;

};

/********************** Edge  ****************************/

class Edge {
public:
    /**
     * Constructor of the Edge class storing all the information about a connection between two vertices (Vertex)/train stations.
     * Time Complexity: O(1).
     * @param orig String that stores the name of the source train station, that also represents a Vertex.
     * @param dest String that stores the name of the target train station, that also represents a Vertex.
     * @param w Double that stores the capacity of this connection between two train stations.
     * @param service String that stores the type of service that happens between those stations (STANDARD or ALFA PENDULAR).
     */
    Edge(Vertex *orig, Vertex *dest, double w, string service);
    /**
     * Gets the train station of the destination.
     * @return Vertex that represents the target train station.
     */
    Vertex * getDest() const;
    /**
     * Gets the weight/capacity of this connection.
     * @return Double that stores the weight/capacity of this connection between two train stations.
     */
    double getWeight() const;
    /**
     * Gets the name of the type of service of this connection.
     * @return String that stores the type of service that happens between those stations (STANDARD or ALFA PENDULAR).
     */
    string getService() const;
    bool isSelected() const;
    /**
     * Gets the train station of the origin.
     * @return Vertex that represents the origin train station.
     */
    Vertex * getOrig() const;
    /**
     * Gets current flow of this connection.
     * @return Double that stores the current flow of this connection between two train stations.
     */
    double getFlow() const;
    /**
     * Sets if a Edge was selected or not.
     * @param selected Bool (true/false) that indicates if Edge was selected or not.
     */
    void setSelected(bool selected);
    /**
     * Sets the reverse connection of this connection.
     * @param reverse Edge that has this orig and dest swapped.
     */
    void setReverse(Edge *reverse);
    /**
     * Sets the current flow of this connection.
     * @param flow Double that stores the current flow of this connection between two train stations.
     */
    void setFlow(double flow);
protected:
    /**
     * @brief Vertex that represents the target train station.
     */
    Vertex * dest;
    /**
     * @brief Double that stores the weight/capacity of this connection between two train stations.
     */
    double weight;
    /**
     * @brief String that stores the type of service that happens between those stations (STANDARD or ALFA PENDULAR).
     */
    string service;
    /**
     * @brief Bool that indicates if a Edge is selected or not.
     */
    bool selected = false;
    // used for bidirectional edges
    /**
     * @brief Vertex that represents the origin train station.
     */
    Vertex *orig;
    /**
     * @brief Edge that has this orig and dest swapped.
     */
    Edge *reverse = nullptr;
    // for flow-related problems
    /**
     * @brief Double that stores the current flow of this connection between two train stations.
     */
    double flow;
};

#endif