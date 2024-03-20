#ifndef PIPE_H
#define PIPE_H

#include <string>
#include "Graph.h"

template <class T>
class Pipe : public Edge<T> {
private:
    Vertex<T>* servicePointA;
    Vertex<T>* servicePointB;
    int capacity;
    int direction;

public:
    // Constructor
    Pipe(const Vertex<T>& _servicePointA, const Vertex<T>& _servicePointB, int _capacity, int _direction);

    // Getters
 /* Vertex<T>* getServicePointA() const; // Edge getOrigin()
    Vertex<T>* getServicePointB() const; // Edge getDest();
    int getCapacity() const;             // Edge getWeight();
    int getDirection() const;            // Direction == 0 -> add 2 edges (A to B, B to A)
                                         // Direction == 1 -> add 1 edge from A to B */
};

#endif // PIPE_H
