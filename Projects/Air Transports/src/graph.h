// AED 2022/2023 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [last update: 27/11/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <unordered_map>

using namespace std;

/**
 * Classe Graph
 * @details esta classe gera o grafo
 */
class Graph {
    struct Edge {
        string dest;   // Destination node
        int distance; // An integer weight
        vector<string> airline;
    };

    struct Node {
        int dist;
        string name;
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    /**
     * Construtor por default
     */
    Graph();
    /**
     * @param n n
     */
    void setN(int n);
    /**
     * @param hasDir hasDir
     */
    void setHasDir(bool hasDir);
    /**
     * @param src src
     * @param dest dest
     * @param distance distance
     * @param airline airline
     * \complexity: O(|N|*|E|)
     */
    // Add edge from source to destination with a certain weight
    void addEdge(string src, string dest, int distance, string airline);
    /**
     * Obtém o caminho mais curto
     * @param start start
     * @param end end
     * @return path
     * \complexity: O(log(|N|)*|N|*|E|)
     */
    vector<string> get_shortest_path_code(string start, string end);
    /**
     * @param path path
     */
    void printPath(vector<string> path);
    /**
     * @param v v
     * @param value value
     * \complexity: O(log(|N|)*|N|^2*|E|)
     */
    void bfs(string v, int value);
    vector<Node> getNodes()
    {return nodes;}

};

#endif
