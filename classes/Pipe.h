#ifndef PIPE_H
#define PIPE_H

#include <string>
#include "Node.h"

class Pipe {
private:
    Node servicePointA;
    Node servicePointB;
    int capacity;
    bool direction;

public:
    // Constructor
    Pipe(const Node& _servicePointA, const Node& _servicePointB, int _capacity, bool _direction);

    // Getters
    Node getServicePointA() const;
    Node getServicePointB() const;
    int getCapacity() const;
    bool getDirection() const;
};

#endif // PIPE_H
