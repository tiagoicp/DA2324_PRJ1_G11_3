#include "Pipe.h"

using namespace std;

template<typename T>
Pipe<T>::Pipe(const Vertex<T>& _servicePointA, const Vertex<T>& _servicePointB, int _capacity, int _direction)
    : servicePointA(_servicePointA), servicePointB(_servicePointB), capacity(_capacity), direction(_direction) {}

