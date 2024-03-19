#include "Pipe.h"

using namespace std;

Pipe::Pipe(const Node& _servicePointA, const Node& _servicePointB, int _capacity, bool _direction)
    : servicePointA(_servicePointA), servicePointB(_servicePointB), capacity(_capacity), direction(_direction) {}

