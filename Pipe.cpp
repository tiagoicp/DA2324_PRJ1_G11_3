#include "Pipe.h"

using namespace std;

Pipe::Pipe(const string& _servicePointA, const string& _servicePointB, int _capacity, bool _direction)
    : servicePointA(_servicePointA), servicePointB(_servicePointB), capacity(_capacity), direction(_direction) {}

string Pipe::getServicePointA() const {
    return servicePointA;
}

string Pipe::getServicePointB() const {
    return servicePointB;
}

int Pipe::getCapacity() const {
    return capacity;
}

bool Pipe::getDirection() const {
    return direction;
}
