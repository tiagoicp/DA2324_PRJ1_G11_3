#ifndef WATERSUPPLY_H
#define WATERSUPPLY_H

#include "Graph.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include <unordered_map>
#include <set>

template <class T>
class WaterSupply : public Graph<T> {

private:
    std::vector<Reservoir<T>> reservoirs;
    std::vector<PumpingStation<T>> pumpingStations;
    std::vector<City<T>> cities;
    std::vector<Pipe<T>> pipes;
    std::unordered_map<std::string, int> cityDemand;

public:
    void addNode(Vertex<T>& node);
    void removeNode(const Vertex<T>& node);
    void addPipe(Edge<T>& pipe);
    void removePipe(Edge<T>& pipe);
    // Getters
    const std::vector<Reservoir<T>>& getReservoirs() const { return reservoirs; }
    const std::vector<PumpingStation<T>>& getPumpingStations() const { return pumpingStations; }
    const std::vector<City<T>>& getCities() const { return cities; }
    const std::vector<Pipe<T>>& getPipes() const { return pipes; }
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
