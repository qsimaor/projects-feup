#include "Graph.h"

using namespace std;

Graph::Graph(){}

int Graph::getNumVertex() const {
    return vertexSet.size();
}
vector<Vertex *> Graph::getVertexSet() const{
    return vertexSet;
}
Vertex * Graph::findVertex(int name) const {
    for (auto v : vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

bool Graph::addVertex(const int &name) {
    if (findVertex(name) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(name));
    return true;
}
bool Graph::addVertex(const int &name, double longitude, double latitude) {
    if (findVertex(name) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(name,longitude,latitude));
    return true;
}

bool Graph::addEdge(const int &sta_A, const int &sta_B, double cap) {
    auto v1 = findVertex(sta_A);
    auto v2 = findVertex(sta_B);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, cap);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sta_A, const int &sta_B, double cap) {
    auto v1 = findVertex(sta_A);
    auto v2 = findVertex(sta_B);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, cap);
    auto e2 = v2->addEdge(v1, cap);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

bool Graph::parser_onefile(const string& file_p){
    fstream file;
    file.open(file_p,ios::in);
    if(!file.is_open()){
        return false;
    }
    string ori,dest,distance;
    getline(file,ori);
    if(count(ori.begin(), ori.end(),',')==2) {
        while (getline(file, ori, ',')) {
            getline(file, dest, ',');
            getline(file, distance);
            if (findVertex(stoi(ori)) == nullptr) {addVertex(stoi(ori));}
            if (findVertex(stoi(dest)) == nullptr) {addVertex(stoi(dest));}
            addBidirectionalEdge(stoi(ori), stoi(dest), stod(distance));
        }
    }
    else if(count(ori.begin(), ori.end(),',')==4){
        string label_o,label_d;
        while (getline(file, ori, ',')) {
            getline(file, dest, ',');
            getline(file, distance, ',');
            getline(file, label_o, ',');
            getline(file, label_d);
            if (findVertex(stoi(ori)) == nullptr) {addVertex(stoi(ori));}
            if (findVertex(stoi(dest)) == nullptr) {addVertex(stoi(dest));}
            addBidirectionalEdge(stoi(ori), stoi(dest), stod(distance));
        }
    }
    file.close();
    printf("Parsed!");
    return true;
}

bool Graph::parser_twofiles(const string& edges_p, const string& nodes_p){
    fstream edges_f,nodes_f;
    nodes_f.open(nodes_p,ios::in);
    if(!nodes_f.is_open()){
        return false;
    }
    string ori,lon,lat;
    getline(nodes_f,ori);
    if(count(ori.begin(), ori.end(),',')==2) {
        while (getline(nodes_f, ori, ',')) {
            getline(nodes_f, lon, ',');
            getline(nodes_f, lat);
            addVertex(stoi(ori),stod(lon),stod(lat));
        }
        nodes_f.close();
        edges_f.open(edges_p,ios::in);
        if(!edges_f.is_open()){
            return false;
        }
        string dest,dist;
        getline(edges_f,ori);
        while (getline(edges_f, ori, ',')) {
            getline(edges_f, dest, ',');
            getline(edges_f, dist);
            addBidirectionalEdge(stoi(ori),stoi(dest),stod(dist));
        }
        edges_f.close();
    }
    printf("Parsed!");
    return true;
}
void Graph::backtrack_tsp(){
    clock_t start = clock();

    double min_cost = std::numeric_limits<double>::max();
    std::vector<int> path = {0}; // Start from vertex 0
    std::vector<bool> visited(getNumVertex(), false);
    visited[0] = true; // Mark the starting vertex as visited

    // Call the recursive function to find the minimum cost Hamiltonian cycle
    backtrack_tsp_rec(path, visited, min_cost, 0.0);

    clock_t end = clock();

    std::cout << "Minimum Distance: " << min_cost << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

}
void Graph::backtrack_tsp_rec(std::vector<int>& path, std::vector<bool>& visited, double &min_cost, double cost_so_far) {
    if (path.size() == vertexSet.size()) {
        int start_vertex = path.front();
        int last_vertex = path.back();
        for (auto edge : vertexSet[last_vertex]->getAdj()) {
            if (edge->getDest()->getName() == start_vertex) {
                double cycle_cost = cost_so_far + edge->getWeight();
                if (cycle_cost < min_cost) {
                    min_cost = cycle_cost;
                }
                break;
            }
        }
        return;
    }

    int last_vertex = path.back();
    for (auto edge : vertexSet[last_vertex]->getAdj()) {
        if (!visited[edge->getDest()->getName()]) {
            path.push_back(edge->getDest()->getName());
            visited[edge->getDest()->getName()] = true;
            backtrack_tsp_rec(path, visited, min_cost, cost_so_far + edge->getWeight());
            path.pop_back();
            visited[edge->getDest()->getName()] = false;
        }
    }
}

void Graph::removeVertex(int s){
    auto v= findVertex(std::move(s));
    for(auto e: v->getAdj()){
        v->removeEdge(e->getDest()->getName());
    }
    for(auto e: v->getIncoming()){
        e->getOrig()->removeEdge(v->getName());
    }
    remove(vertexSet.begin(), vertexSet.end(),v);
}

std::vector<std::pair<int, int>> Graph::primMST(std::vector<int>& parent) {
    std::vector<double> key(vertexSet.size(), std::numeric_limits<double>::max());
    std::vector<bool> inMST(vertexSet.size(), false);
    int startVertex = 0;
    key[startVertex] = 0.0;

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push(std::make_pair(0.0, startVertex));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        for (auto &edge: vertexSet[u]->getAdj()) {
            int v = edge->getDest()->getName();
            double weight = edge->getWeight();

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push(std::make_pair(weight, v));
            }
        }
    }

    std::vector<std::pair<int, int>> mst;
    std::cout << "Minimum Spanning Tree:" << std::endl;
    for (int i = 1; i < vertexSet.size(); ++i) {
        mst.push_back(std::make_pair(parent[i], i));
        std::cout << parent[i] << " - " << i << std::endl;
    }

    return mst;
}

void Graph::dfs(int current, const std::vector<int> &parent, std::vector<bool> &visited, std::stack<int> &cityStack, std::vector<int> &path) {
    visited[current] = true;
    cityStack.push(current);

    while (!cityStack.empty()) {
        int city = cityStack.top();
        cityStack.pop();

        path.push_back(city);

        for (int neighbor = 0; neighbor < parent.size(); ++neighbor) {
            if (parent[neighbor] == city && !visited[neighbor]) {
                visited[neighbor] = true;
                cityStack.push(neighbor);
            }
        }
    }
}

double Graph::calculateTotalDistance(const std::vector<int> &path) {
    double totalDistance = 0.0;


    for (int i = 0; i < path.size() - 1; ++i) {
        int v1 = path[i];
        int v2 = path[i + 1];

        if(!check_if_nodes_are_connected(v1, v2)){
            totalDistance += haversine(vertexSet[v1]->getLatitude(), vertexSet[v1]->getLongitude(), vertexSet[v2]->getLatitude(), vertexSet[v2]->getLongitude());
            continue;
        }

        for (const auto& edge : vertexSet[v1]->getAdj()) {
            if (edge->getDest()->getName() == v2) {
                totalDistance += edge->getWeight();
                break;
            }
        }
    }

    int final_city = path.back();
    if(!check_if_nodes_are_connected(final_city, path[0])){
        totalDistance += haversine(vertexSet[final_city]->getLatitude(), vertexSet[final_city]->getLongitude(), vertexSet[path[0]]->getLatitude(), vertexSet[path[0]]->getLongitude());
    }
    else{
        for(const auto& edge : vertexSet[final_city]->getAdj()){
            if(edge->getDest()->getName() == path[0]){
                totalDistance += edge->getWeight();
                break;
            }
        }
    }

    return totalDistance;
}
bool Graph::check_if_nodes_are_connected(int v1, int v2){
    int index_v1;

    for(auto it : vertexSet){
        if(it->getName() == v1){
            index_v1 = it->getName();
            break;
        }
    }

    for(const auto& edge : vertexSet[index_v1]->getAdj()){
        if(edge->getDest()->getName() == v2){
            return true;
        }
    }
    return false;
}

double Graph::haversine(double lat1, double lon1, double lat2, double lon2) {
    if (lat1 == 0 && lon1 == 0 && lat2 == 0 && lon2 == 0) {
        return 0.0;
    }

    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;

    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) +
               std::cos(lat1Rad) * std::cos(lat2Rad) *
               std::sin(dLon / 2.0) * std::sin(dLon / 2.0);
    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    double distance = EARTH_RADIUS * c;

    return distance;
}

void Graph::triangularApproximation() {
    clock_t start = clock();

    std::vector<int> parent(vertexSet.size(), -1);
    primMST(parent);


    std::vector<bool> visited(vertexSet.size(), false);
    std::vector<int> path;
    std::stack<int> cityStack;
    dfs(0, parent, visited, cityStack, path);

    std::cout << "Path: ";
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i != path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << " -> 0"<< std::endl;

    double total_distance = calculateTotalDistance(path);
    clock_t end = clock();

    std::cout << "Optimal cost: " << total_distance << " meters" << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}


