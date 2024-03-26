#ifndef WATERSUPPLY_H
#define WATERSUPPLY_H

#include "Graph.h"
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include <unordered_map>

class WaterSupply : Graph<std::string> {

private:
    std::unordered_map<std::string,Reservoir> reservoirs;
    std::unordered_map<std::string,PumpingStation> pumpingStations;
    std::unordered_map<std::string,City> cities;

public:
    void addReservoir(const std::string &code,const Reservoir& reservoir);
    void removeReservoir(const std::string& code);
    void addPumpingStation(const std::string &code,const PumpingStation& ps);
    void removePumpingStation(const std::string& code);
    void addCity(const std::string &code,const City& city);
    void removeCity(const std::string& code);
    void addPipe(const std::string& servicePointA, const std::string& servicePointB, int capacity, int direction);
    void removePipe(const std::string& servicePointA, const std::string& servicePointB);
    Vertex<std::string>* findNode(const std::string &in) const;

    // Getters
    const std::unordered_map<std::string,Reservoir>& getReservoirs() const { return reservoirs; }
    const std::unordered_map<std::string,PumpingStation>& getPumpingStations() const { return pumpingStations; }
    const std::unordered_map<std::string,City>& getCities() const { return cities; }
    std::vector<Vertex<std::string> *> getNodes() const { return getVertexSet(); }
};

#endif // WATERSUPPLY_H
