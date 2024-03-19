#ifndef PIPE_H
#define PIPE_H

#include <string>
#include "Node.h"

template <class T>
class Pipe : public Edge<T> {
private:
   /* Node servicePointA;
    Node servicePointB;
    int capacity;
    int direction;*/

public:
    // Constructor
    Pipe(const Node& _servicePointA, const Node& _servicePointB, int _capacity, int _direction);

    // Getters
   /* Node getServicePointA() const; getOrigin()
    Node getServicePointB() const;  getDest();
    int getCapacity() const;    getWeight();
    int getDirection() const;      Direction == 0 -> add 2 edges / Direction == 1 -> add 1 edge from A to B*/
};

#endif // PIPE_H
