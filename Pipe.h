#ifndef PIPE_H
#define PIPE_H

#include <string>

class Pipe {
private:
    std::string servicePointA;
    std::string servicePointB;
    int capacity;
    bool direction;

public:
    // Constructor
    Pipe(const std::string& _servicePointA, const std::string& _servicePointB, int _capacity, bool _direction);

    // Getters
    std::string getServicePointA() const;
    std::string getServicePointB() const;
    int getCapacity() const;
    bool getDirection() const;
};

#endif // PIPE_H
