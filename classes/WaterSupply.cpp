#include <iostream>
#include "WaterSupply.h"

using namespace std;


void WaterSupply::addReservoir(const std::string& code,const Reservoir& reservoir)
{
    reservoirs[code] = reservoir;       // add element to hash table
    addVertex(code);                // add vertex to graph
}

void WaterSupply::removeReservoir(const std::string& code)
{
    reservoirs.erase(code);
    removeVertex(code);
}

void WaterSupply::addPipe(const std::string& servicePointA, const std::string& servicePointB, int capacity, int direction)
{
    addEdge(servicePointA, servicePointB, capacity);
    if (direction == 0)
        addEdge(servicePointB,servicePointA,capacity);
}

void WaterSupply::removePipe(const std::string& servicePointA, const std::string& servicePointB)
{
    removeEdge(servicePointA, servicePointB);
    removeEdge(servicePointB, servicePointA);
}

Vertex<std::string>* WaterSupply::findNode(const std::string &in) const{
    return findVertex(in);
}

void WaterSupply::addPS(const string &code, const PumpingStation &ps) {
    pumpingStations[code] = ps;
    addVertex(code);
}

void WaterSupply::removePS(const string &code) {
    pumpingStations.erase(code);
}

void WaterSupply::addCity(const string &code, const City &city) {
    cities[code] = city;
    addVertex(code);
}

void WaterSupply::removeCity(const string &code) {
    cities.erase(code);
}
