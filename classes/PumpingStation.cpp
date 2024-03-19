#include "PumpingStation.h"

using namespace std;

template<typename T>
PumpingStation<T>::PumpingStation(int _id, const string& _code) : id(_id), code(_code) {}

template<typename T>
int PumpingStation<T>::getId() const {
    return id;
}

template<typename T>
string PumpingStation<T>::getCode() const {
    return code;
}
