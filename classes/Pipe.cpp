#include "Pipe.h"

using namespace std;

Pipe::Pipe(const Node& _servicePointA, const Node& _servicePointB, int _capacity, bool _direction)
    : servicePointA(_servicePointA), servicePointB(_servicePointB), capacity(_capacity), direction(_direction) {}

Node Pipe::getServicePointA() const {
    return servicePointA;
}

Node Pipe::getServicePointB() const {
    return servicePointB;
}

int Pipe::getCapacity() const {
    return capacity;
}

bool Pipe::getDirection() const {
    return direction;
}
