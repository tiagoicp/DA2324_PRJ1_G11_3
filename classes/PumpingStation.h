#ifndef PUMPINGSTATION_H
#define PUMPINGSTATION_H

#include <string>
#include "Graph.h"

template <class T>
class PumpingStation : public Vertex<T> {
private:
    int id;
    std::string code;

public:
    // Constructor
    PumpingStation(int _id, const std::string& _code);

    // Getters
    int getId() const;
    std::string getCode() const; // Vertex getInfo()
};

#endif // PUMPINGSTATION_H
