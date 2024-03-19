#ifndef FILEREADER_H
#define FILEREADER_H

#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include "WaterSupply.h"
#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

template <class T>
class FileReader {
public:
    static void addReservoirs(const std::string &filename, WaterSupply<T> &OurGraph);
    static void addStations(const std::string &filename, WaterSupply<T> &OurGraph);
    static void addCities(const std::string &filename, WaterSupply<T> &OurGraph);
    static void addPipes(const std::string &filename, WaterSupply<T> &OurGraph);
};

#endif //FILEREADER_H