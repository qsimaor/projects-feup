#include <fstream>
#include <unordered_map>
#include <set>
#include "Graph.h"

using namespace std;

Graph::Graph(){}

int Graph::getNumVertex() const {
    return vertexSet.size();
}
vector<Vertex *> Graph::getVertexSet() const{
    return vertexSet;
}
Vertex * Graph::findVertex(string name) const {
    for (auto v : vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

bool Graph::addVertex(const string &name,const string &district,const string &municipality,const string &township,const string &line) {
    if (findVertex(name) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(name,district,municipality,township,line));
    return true;
}

bool Graph::addEdge(const string &sta_A, const string &sta_B, double cap, const string &service) {
    auto v1 = findVertex(sta_A);
    auto v2 = findVertex(sta_B);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, cap,service);
    return true;
}

bool Graph::addBidirectionalEdge(const string &sta_A, const string &sta_B, double cap, const string &service) {
    auto v1 = findVertex(sta_A);
    auto v2 = findVertex(sta_B);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, cap,service);
    auto e2 = v2->addEdge(v1, cap,service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

bool Graph::parser(string stations_p, string network_p){
    Graph g = Graph();
    fstream stations_f,network_f;
    stations_f.open(stations_p,ios::in);

    if(!stations_f.is_open()){
        return false;
    }
    string name,district,municipality,township,line;
    getline(stations_f,name);
    while(getline(stations_f,name,',')){
        getline(stations_f,district,',');
        getline(stations_f,municipality,',');
        getline(stations_f,township,',');
        getline(stations_f,line);

        addVertex(name,district,municipality,township,line);
    }
    stations_f.close();
    network_f.open(network_p,ios::in);

    if(!network_f.is_open()){
        return false;
    }
    string sta_A,sta_B,cap,ser;
    getline(network_f,sta_A);
    while(getline(network_f,sta_A,',')){
        getline(network_f,sta_B,',');
        getline(network_f,cap,',');
        getline(network_f,ser);

        addBidirectionalEdge(sta_A, sta_B,stod(cap),ser);
    }
    network_f.close();
    return true;
}

void Graph::testAndVisit(queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double Graph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

double Graph::edmondsKarp(string source, string target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    // Reset the flows
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    double maxFlow = 0;
    // Loop to find augmentation paths
    while( findAugmentingPath(s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
        maxFlow += f;
    }
    return maxFlow;
}

double Graph::maxTrainsAtStation(string station){
    Vertex super_v = Vertex("super_v");
    vertexSet.push_back(&super_v);
    double flow = 0;
    for(auto e: vertexSet){
        if(e->getAdj().size()==1 and e->getName()!=station){
            super_v.addEdge(e,INT_MAX,"");
        }
    }
    flow = edmondsKarp(super_v.getName(),station);
    removeVertex("super_v");
    return flow;
}

vector<pair<string,double>> Graph::budgetMunicipalities(int k){
    unordered_map<string,vector<Vertex*>> municipalities;
    vector<pair<string,double>> maxflowMunicipalities;
    for(auto v: vertexSet){
        municipalities[v->getMunicipality()].push_back(v);
    }
    for(auto m:municipalities){
        double d = 0;
        auto v = m.second;
        if(m.second.size()==1){
            maxflowMunicipalities.push_back(make_pair(m.first,d));
            continue;
        }
        for (int i=0;i!=v.size();i++){
            for(int j=i+1;j!=v.size();j++) {
                d += edmondsKarp(v[i]->getName(), v[j]->getName());
            }
        }
        maxflowMunicipalities.push_back(make_pair(m.first,d));
    }
    sort(maxflowMunicipalities.begin(), maxflowMunicipalities.end(),[](auto& lhs, auto& rhs) {
        return lhs.second > rhs.second;
    });
    if (k < maxflowMunicipalities.size()) {
        maxflowMunicipalities.erase(maxflowMunicipalities.begin() + k, maxflowMunicipalities.end());
    }
    else{
        cout << "ERROR: Please input a k value smaller than " << maxflowMunicipalities.size() << "." << endl;
    }
    return maxflowMunicipalities;
}
vector<pair<string,double>> Graph::budgetDistricts(int k){
    unordered_map<string,vector<Vertex*>> districts;
    vector<pair<string,double>> maxflowDistricts;
    for(auto v: vertexSet){
        districts[v->getDistrict()].push_back(v);
    }
    for(auto m: districts){
        double d = 0;
        auto v = m.second;
        if(m.second.size()==1){
            maxflowDistricts.push_back(make_pair(m.first,d));
            continue;
        }
        for (int i=0;i!=v.size();i++){
            for(int j=i+1;j!=v.size();j++) {
                d += edmondsKarp(v[i]->getName(), v[j]->getName());
            }
        }
        maxflowDistricts.push_back(make_pair(m.first,d));
    }
    sort(maxflowDistricts.begin(), maxflowDistricts.end(),[](auto& lhs, auto& rhs) {
        return lhs.second > rhs.second;
    });
    if (k < maxflowDistricts.size()) {
        maxflowDistricts.erase(maxflowDistricts.begin() + k, maxflowDistricts.end());
    }
    else{
        cout << "ERROR: Please input a k value smaller than " << maxflowDistricts.size() << "." << endl;
    }
    return maxflowDistricts;
}
vector<pair<pair<string,string>,double>> Graph::getPairs_MostAmountOfTrains(){
    vector<pair<string,string>> pairs;
    vector<int> capacities;
    vector<pair<pair<string,string>,double>> pairs_f;
    double trains_max = vertexSet[0]->getAdj()[0]->getWeight();
    int num_stations = getNumVertex();
    cout << "\nLoading..." << endl;
    for(int i = 0; i < num_stations;i++){
        for(int j = i+1;j < num_stations;j++){
            double cap = edmondsKarp(vertexSet[i]->getName(),vertexSet[j]->getName());
            if(cap >= trains_max) {
                trains_max = cap;
                pairs.push_back(make_pair(vertexSet[i]->getName(), vertexSet[j]->getName()));
                capacities.push_back(cap);
            }
        }
    }
    cout << "\nFinishing..." << endl;
    for(int i = 0; i < pairs.size(); i++){
        if(capacities[i] == trains_max){
            pairs_f.push_back(make_pair(pairs[i],trains_max));
        }
    }
    return pairs_f;
}

bool Graph::bfs_for_max_flow(Vertex *s, Vertex *t) {
    for(auto v : vertexSet){
        v->setVisited(false);
    }
    s->setVisited(true);
    queue<Vertex *> q;
    q.push(s);

    while(!q.empty() && !t->isVisited()){
        auto u = q.front();
        q.pop();
        for(auto e : u->getAdj()){
            if((!e->getDest()->isVisited() && e->getWeight() - e->getFlow() > 0)){
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                q.push(e->getDest());
            }
        }
    }
    return t->isVisited();
}
int Graph::maxFlow_minCost(string source, string target) {
    Vertex *s = findVertex(std::move(source));
    Vertex *t = findVertex(std::move(target));
    if(s == nullptr || t == nullptr){
        cout << "\nInvalid station inserted" << endl;
        return 0;
    }
    for(auto v : vertexSet){
        auto e = v->getPath();
        if(e==NULL){
            continue;
        }
        e->setSelected(false);
    }

    for (int i = 0; i < getNumVertex(); i++) {
        for (int j = 0; j < vertexSet[i]->getAdj().size(); j++) {
            vertexSet[i]->getAdj()[j]->setFlow(0);
        }
    }
    std::vector<double> aux;
    int i = 0;
    vector<pair<string,int>> services ={{"ALFA PENDULAR",0},{"STANDARD",0}};
    while (bfs_for_max_flow(s, t)) {
        double path_flow = INF;
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if(i==0){
            if(e->getService()=="ALFA PENDULAR" && !e->isSelected()){
                services[0].second++;
                e->setSelected(true);
            }
            else if (e->getService()=="STANDARD" && !e->isSelected()){
                services[1].second++;
                e->setSelected(true);
            }}
            if (e->getDest() == v) {
                path_flow = std::min(path_flow, e->getWeight() - e->getFlow());
                v = e->getOrig();
            } else {
                path_flow = std::min(path_flow, e->getFlow());
                v = e->getDest();
            }
        }
        i++;
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            double flow = e->getFlow();
            if (e->getDest() == v) {
                e->setFlow(flow + path_flow);
                v = e->getOrig();
            } else {
                e->setFlow(flow - path_flow);
                v = e->getDest();
            }
        }
        aux.push_back(path_flow);
    }

    if (aux.empty()) {
        return 0;
    }

    double max_flow = 0;
    int index = 0;
    for(int j = 0; j < aux.size(); j++){
        if(max_flow < aux[j]){
            index = j;
            max_flow = aux[j];
        }
    }
    double minCost = ((4*services[0].second)+(2*services[1].second))*max_flow;
    cout << endl;
    cout << "The minimum cost is: " << minCost << endl;
    return (int) aux[index];
}
void Graph::max_trains_min_cost(string station1, string station2) {

    int max_trains = maxFlow_minCost(std::move(station1),std::move(station2));

    if(max_trains == 0){
        cout << "Found no connection between this stations\n";
    }
    else{
        cout << "Max num of trains with min cost: " << max_trains << endl;
        cout << endl;
    }
}

void Graph::removeVertex(string s){
    auto v= findVertex(std::move(s));
    for(auto e: v->getAdj()){
        v->removeEdge(e->getDest()->getName());
    }
    for(auto e: v->getIncoming()){
        e->getOrig()->removeEdge(v->getName());
    }
    remove(vertexSet.begin(), vertexSet.end(),v);
}

vector<pair<string,double>> Graph::differenceMaxFlowFailures(Graph f,int k){
    vector<pair<string,double>> pairs;
    int num_stations = f.getNumVertex();
    cout << "\nLoading..." << endl;
    for(int i = 0; i < num_stations;i++){
        double diffCap = maxTrainsAtStation(f.getVertexSet()[i]->getName()) - f.maxTrainsAtStation(f.getVertexSet()[i]->getName());
        pairs.push_back(make_pair(f.getVertexSet()[i]->getName(),diffCap));
    }
    cout << "\nFinishing..." << endl;
    sort(pairs.begin(), pairs.end(),[](auto& lhs, auto& rhs) {
        return lhs.second > rhs.second;
    });
    if (k < pairs.size()) {
        pairs.erase(pairs.begin() + k, pairs.end());
    }
    else{
        cout << "ERROR: Please input a k value smaller than " << pairs.size() << "." << endl;
    }
    return pairs;

}
