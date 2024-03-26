#include "Reservoir.h"

using namespace std;

Reservoir::Reservoir() {
    this->name  = "";
    this->municipality = "";
    this->id = 0;
    this->code = "";
    this->maxDelivery = 0;
}

Reservoir::Reservoir(const string& _name, const string& _municipality, int _id,
                     const string& _code, int _maxDelivery)
    : name(_name), municipality(_municipality), id(_id), code(_code), maxDelivery(_maxDelivery) {}

string Reservoir::getName() const {
    return name;
}

string Reservoir::getMunicipality() const {
    return municipality;
}

int Reservoir::getId() const {
    return id;
}

string Reservoir::getCode() const {
    return code;
}

int Reservoir::getMaxDelivery() const {
    return maxDelivery;
}
