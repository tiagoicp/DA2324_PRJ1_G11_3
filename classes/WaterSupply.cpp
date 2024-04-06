#include <iostream>
#include <cmath>
#include <numeric>
#include "WaterSupply.h"

using namespace std;

/* This copy constructor is necessary and used when creating a new temporary graph, so we can remove
 * edges/change edge weights/remove vertex safely without having to re-load the entire data into the
 * original graph everytime.*/
WaterSupply::WaterSupply(const WaterSupply& other)  : Graph(other) {

    cities = other.cities;
    reservoirs = other.reservoirs;
    pumpingStations = other.pumpingStations;
    if (this != &other) {
        vertexSet.clear();
        dstVertexSet.clear();
        srcVertexSet.clear();
        psVertexSet.clear();
        for (Vertex<string>* vertex : other.vertexSet) {
            auto newVertexPtr = new Vertex<string>(vertex->getInfo());
            vertexSet.push_back(newVertexPtr);
            if (cities.find(vertex->getInfo()) != cities.end()) dstVertexSet.push_back(newVertexPtr);
            else if (reservoirs.find(vertex->getInfo()) != reservoirs.end()) srcVertexSet.push_back(newVertexPtr);
            else if (pumpingStations.find(vertex->getInfo()) != pumpingStations.end()) psVertexSet.push_back(newVertexPtr);
        }
        for (Vertex<string>* vertex : other.vertexSet){
            for (Edge<string>* e : vertex->getAdj()){
                addEdge(vertex->getInfo(),e->getDest()->getInfo(),e->getWeight());
            }
        }
    }
}

void WaterSupply::addNode(const string &code){
    addVertex(code);
}
void WaterSupply::removeNode(const string &code){
    removeVertex(code);
}

void WaterSupply::addReservoir(const string& code,const Reservoir& reservoir)
{
    reservoirs[code] = reservoir;       // add element to hash table
    addVertex(code);                // add vertex to graph
    addSrc(this->findNode(code));
}

void WaterSupply::removeReservoir(const string& code)
{
    reservoirs.erase(code);
    removeVertex(code);
}

void WaterSupply::addPipe(const string& servicePointA, const string& servicePointB, int capacity, int direction)
{
    addEdge(servicePointA, servicePointB, capacity);
    if (direction == 0)
        addEdge(servicePointB,servicePointA,capacity);
}

void WaterSupply::removePipe(const string& servicePointA, const string& servicePointB, int direction)
{
    removeEdge(servicePointA, servicePointB);
    if (direction == 0)
        removeEdge(servicePointB, servicePointA);
}

Vertex<string>* WaterSupply::findNode(const string &in) const{
    return findVertex(in);
}

void WaterSupply::addPumpingStation(const string &code, const PumpingStation &ps) {
    pumpingStations[code] = ps;
    addVertex(code);
    addPS(this->findNode(code));
}

void WaterSupply::removePumpingStation(const string &code) {
    pumpingStations.erase(code);
    removeVertex(code);
}

void WaterSupply::addCity(const string &code, const City &city) {
    cities[code] = city;
    addVertex(code);
    addDst(this->findNode(code));
}

void WaterSupply::removeCity(const string &code) {
    cities.erase(code);
    removeVertex(code);
}

void WaterSupply::addSrc(Vertex<string> *src) {
    srcVertexSet.push_back(src);
}

void WaterSupply::addDst(Vertex<string> *dst) {
    dstVertexSet.push_back(dst);
}
void WaterSupply::addPS(Vertex<string> *ps) {
    psVertexSet.push_back(ps);
}

void WaterSupply::connectedReservoirsDfsVisit(Vertex<string>* src, string& dest, bool& found){
    src->setVisited(true);
    for (auto& e : src->getAdj()){
        Vertex<string>* w = e->getDest();
        if (w->getInfo() == dest) found  = true;
        if (!w->isVisited()) connectedReservoirsDfsVisit(w,dest, found);
    }
}

/* Simple DFS algorithm that stores a reservoir into a vector if it can send water to the selected city (dest)
 * Time Complexity = O(V+E). */
void WaterSupply::connectedReservoirsDfs(Vertex<string>* src, string& dest,vector<Vertex<string>*>& res ) {
    bool found = false;
    for (Vertex<string>* v : vertexSet){
        v->setVisited(false);
    }
    connectedReservoirsDfsVisit(src, dest, found);
    if (found)
        res.push_back(src);
}

double WaterSupply::getTotalSinkFlow() {
    double totalFlow = 0;
    for (Vertex<string>* v : dstVertexSet){
        for (Edge<string>* e : v->getIncoming()){
            totalFlow+=e->getFlow();
        }
    }
    return totalFlow;
}

void WaterSupply::resetGraphFlow() {
    for (Vertex<string>* v : vertexSet){
        for (Edge<string>* e : v->getAdj()){
            e->setFlow(0);
        }
    }
}

double WaterSupply::getCityFlow(Vertex<string> *cityVertex) {
    double totalFlow = 0;
    for (auto e: cityVertex->getIncoming()) {
        totalFlow += e->getFlow();
    }
    cityVertex->setIncFlow(totalFlow);
    return totalFlow;
}

double getAverage(const vector<double>& v){
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    return sum / v.size();
}

double getStdDev(const vector<double>& v){
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    return std::sqrt(sq_sum / v.size());
}

vector<double> WaterSupply::getNetworkBalanceStats() const {
    vector<double> diffVector;
    for(auto node : getNodeSet()){
        if(node->getInfo() == "master_source" || node->getInfo() == "master_sink") continue;
        if(node->getAdj().empty()) continue;
        if(node->getAdj().size() == 1 && node->getAdj()[0]->getDest()->getInfo() == "master_sink") continue;

        for(auto pipe : node->getAdj()){
            if(pipe->getDest()->getInfo() == "master_sink") continue;

            diffVector.push_back(pipe->getWeight()-pipe->getFlow());
        }
    }
    vector<double> stats;
    stats.push_back(getAverage(diffVector));
    stats.push_back(getStdDev(diffVector));
    return stats;
}







