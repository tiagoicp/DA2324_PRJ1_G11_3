#ifndef DA2324_PRJ1_G11_3_RESERVOIR_H
#define DA2324_PRJ1_G11_3_RESERVOIR_H

#include <string>
#include "Graph.h"

class Reservoir {
private:
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery; // maximum delivery capacity in m3/s

public:
    // Constructor
    Reservoir();
    Reservoir(const std::string& _name, const std::string& _municipality, int _id,
              const std::string& _code, int _maxDelivery);

    // Getters
    std::string getName() const;
    std::string getMunicipality() const;
    int getId() const;
    std::string getCode() const; // Vertex getInfo()
    int getMaxDelivery() const;
};

#endif // DA2324_PRJ1_G11_3_RESERVOIR_H
