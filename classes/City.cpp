#include "City.h"

using namespace std;

City::City(const string& _city, int _id, const string& _code, int _demand, int _population)
    : city(_city), id(_id), code(_code), demand(_demand), population(_population) {}

string City::getCity() const {
    return city;
}

int City::getId() const {
    return id;
}

string City::getCode() const {
    return code;
}

int City::getDemand() const {
    return demand;
}

int City::getPopulation() const {
    return population;
}
