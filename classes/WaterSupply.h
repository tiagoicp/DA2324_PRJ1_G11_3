#ifndef DA2324_PRJ1_G11_3_WATERSUPPLY_H
#define DA2324_PRJ1_G11_3_WATERSUPPLY_H

#include "Graph.h"
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include <unordered_map>

using namespace std;

class WaterSupply : Graph<string> {

private:
    unordered_map<string,Reservoir> reservoirs;
    unordered_map<string,PumpingStation> pumpingStations;
    unordered_map<string,City> cities;
    vector<Vertex<string>*> srcVertexSet;
    vector<Vertex<string>*> dstVertexSet;

public:
    void addNode(const string &code);
    void removeNode(const string &code);
    void addReservoir(const string &code,const Reservoir& reservoir);
    void removeReservoir(const string& code);
    void addPumpingStation(const string &code,const PumpingStation& ps);
    void removePumpingStation(const string& code);
    void addCity(const string &code,const City& city);
    void removeCity(const string& code);
    void addPipe(const string& servicePointA, const string& servicePointB, int capacity, int direction);
    void removePipe(const string& servicePointA, const string& servicePointB, int direction);
    Vertex<string>* findNode(const string &in) const;
    void addSrc(Vertex<string>* src);
    void addDst(Vertex<string>* dst);

    // Getters
    const unordered_map<string,Reservoir>& getReservoirs() const { return reservoirs; }
    const unordered_map<string,PumpingStation>& getPumpingStations() const { return pumpingStations; }
    const unordered_map<string,City>& getCities() const { return cities; }
    vector<Vertex<string> *> getNodeSet() const { return getVertexSet(); }
    vector<Vertex<string> *> getSrcSet() const { return srcVertexSet; }
    vector<Vertex<string> *> getDstSet() const { return dstVertexSet; }
    void connectedReservoirsDfsVisit(Vertex<string>* src, string& dest, bool& found);
    void connectedReservoirsDfs(Vertex<string>* src, string& dest, vector<Vertex<string>*>& res);
    double getSinkFlow();
};

#endif // DA2324_PRJ1_G11_3_WATERSUPPLY_H
