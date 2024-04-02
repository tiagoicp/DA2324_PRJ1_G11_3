#include <iostream>
#include "WaterSupply.h"

using namespace std;


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
}

void WaterSupply::removePumpingStation(const string &code) {
    pumpingStations.erase(code);
    removeVertex(code);
}

void WaterSupply::addCity(const string &code, const City &city) {
    cities[code] = city;
    addVertex(code);
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

void WaterSupply::connectedReservoirsDfsVisit(Vertex<string>* src, string& dest, bool& found){
    src->setVisited(true);
    for (auto& e : src->getAdj()){
        Vertex<string>* w = e->getDest();
        if (w->getInfo() == dest) found  = true;
        if (!w->isVisited()) connectedReservoirsDfsVisit(w,dest, found);
    }
}

void WaterSupply::connectedReservoirsDfs(Vertex<string>* src, string& dest,vector<Vertex<string>*>& res ) {
    bool found = false;
    for (Vertex<string>* v : vertexSet){
        v->setVisited(false);
    }
    connectedReservoirsDfsVisit(src, dest, found);
    if (found)
        res.push_back(src);
}

double WaterSupply::getSinkFlow() {
    double totalFlow = 0;
    for (Vertex<string>* v : dstVertexSet){
        for (Edge<string>* e : v->getIncoming()){
            totalFlow+=e->getFlow();
        }
    }
    return totalFlow;
}




