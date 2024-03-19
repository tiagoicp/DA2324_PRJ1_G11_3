#ifndef WATERSUPPLY_H
#define WATERSUPPLY_H

#include "Graph.h"
#include "Nodes.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include <unordered_map>
#include <set>

class WaterSupply : public Graph<Nodes> {

private:
    std::vector<Reservoir> reservoirs;
    std::vector<PumpingStation> pumpingStations;
    std::vector<City> cities;
    std::vector<Pipe> pipes;
    std::unordered_map<std::string, int> cityDemand;

public:
    void addReservoir(Reservoir& reservoir);
    void removeReservoir(Reservoir& reservoir);
    void addPumpingStation(PumpingStation& station);
    void removePumpingStation(PumpingStation& station);
    void addCity(City& city);
    void removeCity(City& city);
    void addPipe(Pipe& pipe);
    void removePipe(Pipe& pipe);
    // Getters
    const std::vector<Reservoir>& getReservoirs() const { return reservoirs; }
    const std::vector<PumpingStation>& getPumpingStations() const { return pumpingStations; }
    const std::vector<City>& getCities() const { return cities; }
    const std::vector<Pipe>& getPipes() const { return pipes; }
    const std::unordered_map<std::string, int>& getCityDemand() const { return cityDemand; }

    /*Airport findAirport(std::string code);
    Airline getAirline(std::string code);
    void airportFlightCount();      //i.
    void flightsPerAirport(std::string code);       //ii.
    vector<Vertex<Airport> * > getAirports() const;
    Airport getAirport(std::string code);
    void flightsPerCity(std::string city);          //iii.
    void flighsPerAirline(std::string airline);     //iii.
    void airportDestinations(std::string code);     //v.
    void reachableDestinationsInXStops(std::string code,int n); //vi.
    void numOfDestinationsCity(std::string city);       //iv.
    void numOfDestinationsAirport(std::string code);    //iv.
    void maxTrip();         //vii.
    void topAirports(int numOfAirports);        //viii.
    void articulationDfs(Vertex<Airport>* v, set<Airport> & articulationAirports, stack<Airport> &s, int index);
    void essentialAirports();
    int connectedComponents();
    void connectedComponentsDfsVisit(Vertex<Airport>* v, set<std::string> & airportCount);
    int lowestNumberOfStops(Vertex<Airport>* source, Vertex<Airport>* destination);
    set<vector<Vertex<Airport>*>> findAllShortestPathsBetweenAirports(Vertex<Airport>* source, Vertex<Airport>* destination);
    vector<vector<Flight>> allPossibleFlightsPerTravel(vector<Vertex<Airport>*> path);
    int filterPerMinNumberOfAirlines(vector<vector<Flight>>& allPossibleFlights);
    void bestFlightOptions(Vertex<Airport>* source , Vertex<Airport>* destination);
    void bestFlightOptionsWithFilter(Vertex<Airport> *source, Vertex<Airport> *destination);
    vector<Airport> cityAirports(std::string city);
    Vertex<Airport>* cityOption();
    Vertex<Airport>* airportOption();
    Vertex<Airport>* coordinatesOption();
    void addAirlinesToFilter(vector<Airline>& airlines);
    void removeAirlinesFromFilter(vector<Airline>& airlines);
    FMSGraph applyAirlineFilter(vector<Airline> selectedAirlines);*/
};

#endif // WATERSUPPLY_H
