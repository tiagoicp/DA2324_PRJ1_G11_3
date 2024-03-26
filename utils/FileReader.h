#ifndef FILEREADER_H
#define FILEREADER_H

#include "../classes/Reservoir.h"
#include "../classes/PumpingStation.h"
#include "../classes/City.h"
#include "../classes/WaterSupply.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class FileReader {
public:
    static void addReservoirs(const std::string &filename, WaterSupply &network);
    static void addPumpingStations(const std::string &filename, WaterSupply &network);
    static void addCities(const std::string &filename, WaterSupply &network);
    static void addPipes(const std::string &filename, WaterSupply &network);
};

#endif //FILEREADER_H