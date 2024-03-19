#ifndef RESERVOIR_H
#define RESERVOIR_H

#include <string>
#include "../utils/Graph.h"
template <class T>
class Reservoir : public Vertex<T>{
private:
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery; // maximum delivery capacity in m3/s

public:
    // Constructor
    Reservoir(const std::string& _name, const std::string& _municipality, int _id,
              const std::string& _code, int _maxDelivery);

    // Getters
    std::string getName() const;
    std::string getMunicipality() const;
    int getId() const;
    std::string getCode() const;
    int getMaxDelivery() const;
};

#endif // RESERVOIR_H
