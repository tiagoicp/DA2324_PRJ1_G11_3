#ifndef FILEREADER_H
#define FILEREADER_H

#include "../classes/Reservoir.h"
#include "../classes/PumpingStation.h"
#include "../classes/City.h"
#include "../classes/WaterSupply.h"
#include "../classes/Pipe.h"
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