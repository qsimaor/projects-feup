#include <valarray>
#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int name): name(name){}
Vertex::Vertex(int name,double lon, double lat): name(name), longitude(lon), latitude(lat){}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdge(int destName) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getName() == destName) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getName() == name) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}



int Vertex::getName() const {
    return this->name;
}

double Vertex::getLatitude() const {
    return this->latitude;
}

double Vertex::getLongitude() const {
    return this->longitude;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}


std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setName(int name) {
    this->name = name;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}
