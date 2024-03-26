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
    void addPS(const std::string &code,const PumpingStation& ps);
    void removePS(const std::string& code);
    void addCity(const std::string &code,const City& city);
    void removeCity(const std::string& code);
    void addPipe(const std::string& servicePointA, const std::string& servicePointB, int capacity, int direction);
    void removePipe(const std::string& servicePointA, const std::string& servicePointB);
    Vertex<std::string>* findNode(const std::string &in) const;

    // Getters
   /* const std::vector<Reservoir>& getReservoirs() const { return reservoirs; }
    const std::vector<PumpingStation<std::string>>& getPumpingStations() const { return pumpingStations; }
    const std::vector<City<std::string>>& getCities() const { return cities; }
    const std::vector<Pipe<std::string>>& getPipes() const { return pipes; }
    const std::unordered_map<std::string, int>& getCityDemand() const { return cityDemand; }*/

};

#endif // WATERSUPPLY_H
