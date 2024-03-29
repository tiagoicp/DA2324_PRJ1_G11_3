#ifndef DA2324_PRJ1_G11_3_CITY_H
#define DA2324_PRJ1_G11_3_CITY_H

#include <string>
#include "Graph.h"


class City {
private:
    std::string city;
    int id;
    std::string code;
    double demand;
    int population;

public:
    // Constructor
    City();
    City(const std::string& _city, int _id, const std::string& _code, double _demand, int _population);

    // Getters
    std::string getCity() const;
    int getId() const;
    std::string getCode() const; // Vertex getInfo()
    double getDemand() const;
    int getPopulation() const;
};

#endif // DA2324_PRJ1_G11_3_CITY_H
