#ifndef PUMPINGSTATION_H
#define PUMPINGSTATION_H

#include <string>

class PumpingStation {
private:
    int id;
    std::string code;

public:
    // Constructor
    PumpingStation(int _id, const std::string& _code);

    // Getters
    int getId() const;
    std::string getCode() const;
};

#endif // PUMPINGSTATION_H
