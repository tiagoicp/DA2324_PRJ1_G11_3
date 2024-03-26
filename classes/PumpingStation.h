#ifndef PUMPINGSTATION_H
#define PUMPINGSTATION_H

#include <string>
#include "Graph.h"

class PumpingStation {
private:
    int id;
    std::string code;

public:
    // Constructor
    PumpingStation();
    PumpingStation(int _id, const std::string& _code);

    // Getters
    int getId() const;
    std::string getCode() const;
};

#endif // PUMPINGSTATION_H
