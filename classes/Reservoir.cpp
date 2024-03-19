#include "Reservoir.h"

using namespace std;

template<typename T>
Reservoir<T>::Reservoir(const string& _name, const string& _municipality, int _id,
                     const string& _code, int _maxDelivery)
    : name(_name), municipality(_municipality), id(_id), code(_code), maxDelivery(_maxDelivery) {}

template<typename T>
string Reservoir<T>::getName() const {
    return name;
}

template<typename T>
string Reservoir<T>::getMunicipality() const {
    return municipality;
}

template<typename T>
int Reservoir<T>::getId() const {
    return id;
}

template<typename T>
string Reservoir<T>::getCode() const {
    return code;
}

template<typename T>
int Reservoir<T>::getMaxDelivery() const {
    return maxDelivery;
}
