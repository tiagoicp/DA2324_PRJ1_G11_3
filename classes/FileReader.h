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

class FileReader {
public:
    static void addReservoirs(const std::string &filename, WaterSupply &OurGraph);
    static void addStations(const std::string &filename, WaterSupply &OurGraph);
    static void addCities(const std::string &filename, WaterSupply &OurGraph);
    static void addPipes(const std::string &filename, WaterSupply &OurGraph);
};

#endif //FILEREADER_H