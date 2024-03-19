#include "City.h"

using namespace std;

template<typename T>
City<T>::City(const string& _city, int _id, const string& _code, int _demand, int _population)
    : city(_city), id(_id), code(_code), demand(_demand), population(_population) {}

template<typename T>
string City<T>::getCity() const {
    return city;
}

template<typename T>
int City<T>::getId() const {
    return id;
}

template<typename T>
string City<T>::getCode() const {
    return code;
}

template<typename T>
int City<T>::getDemand() const {
    return demand;
}

template<typename T>
int City<T>::getPopulation() const {
    return population;
}
