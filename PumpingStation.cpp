#include "PumpingStation.h"

using namespace std;

PumpingStation::PumpingStation(int _id, const string& _code) : id(_id), code(_code) {}

int PumpingStation::getId() const {
    return id;
}

string PumpingStation::getCode() const {
    return code;
}
