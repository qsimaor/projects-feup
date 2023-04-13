// AED 2022/2023 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [last update: 27/11/2022]

#include "graph.h"


Graph::Graph() {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(string src, string dest, int distance, string airline) {

    for (auto & no : nodes) {
        if (no.name == src) {
            for (auto it = no.adj.begin(); it != no.adj.end(); it++) {
                if (it->dest == dest) {
                    it->airline.push_back(airline);
                    return;
                }
            }
            Edge e;
            e.dest = dest;
            e.distance = distance;
            e.airline = {};
            e.airline.push_back(airline);
            no.adj.push_back({e.dest, e.distance, e.airline});
            return;
        }
    }
    Edge edge;
    edge.dest = dest;
    edge.distance = distance;
    edge.airline = {};
    edge.airline.push_back(airline);

    Node node;
    node.name = src;
    node.adj = list<Edge> {};
    node.adj.push_back(edge);
    node.visited = false;

    nodes.push_back(node);
}

vector<string> Graph::get_shortest_path_code(string start, string end)  {
    queue<Node> q;
    unordered_map<string, string> previous;
    unordered_map<string, int> distance;

    for (auto & node : nodes) {
        if (node.name == start) {
            q.push(node);
        }
    }

    distance[start] = 0;

    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        if (node.name == end) {
            break;
        }
        for (auto & e : node.adj) {
            if (distance.count(e.dest) == 0) {
                distance[e.dest] = distance[node.name] + 1;
                previous[e.dest] = node.name;
                for (auto & n : nodes) {
                    if (n.name == e.dest) {
                        q.push(n);
                    }
                }
            }
        }
    }

    vector<string> path;
    string current = end;
    while (current != start) {
        if (current.empty()) {
            return path;
        }
        path.insert(path.begin(), current);
        current = previous[current];
    }
    path.insert(path.begin(), start);
    return path;
}






void Graph::printPath(vector<string> path) {

    cout << "--------------------------------------------------------" << endl;
    for (int i = 0; i < path.size(); ++i) {
        if (i != path.size()-1) {
            cout << path[i] << " --> ";
        }
        else
            cout << path[i];
    }
    cout << endl << "--------------------------------------------------------" << endl;
}

void Graph::setN(int n) {
    Graph::n = n;
}

void Graph::setHasDir(bool hasDir) {
    Graph::hasDir = hasDir;
}



void Graph::bfs(string v, int value) {
    for (auto & node : nodes) {
        node.visited = false;
        node.dist = -1;
    }

    queue<string> q; // queue of unvisited nodes
    q.push(v);

    for (auto & node : nodes) {
        if (node.name == v) {
            node.dist = 0;
            node.visited = true;
        }
    }

    while (!q.empty()) { // while there are still unvisited nodes
        string u = q.front();
        q.pop();
        //cout << u << " "; // show node order
        for (auto node : nodes) {
            if (node.name == u) {
                if (node.dist > value)
                    break;
                for (auto e: node.adj) {
                    string w = e.dest;
                    for (auto & j : nodes) {
                        if (j.name == w) {
                            if (!j.visited) {
                                q.push(w);
                                j.visited = true;
                                j.dist = node.dist + 1;
                            }
                        }
                    }
                }
            }
        }
    }
}