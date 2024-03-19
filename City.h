#ifndef CITY_H
#define CITY_H

#include <string>

class City {
private:
    std::string city;
    int id;
    std::string code;
    int demand;
    int population;

public:
    // Constructor
    City(const std::string& _city, int _id, const std::string& _code, int _demand, int _population);

    // Getters
    std::string getCity() const;
    int getId() const;
    std::string getCode() const;
    int getDemand() const;
    int getPopulation() const;
};

#endif // CITY_H