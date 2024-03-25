//
// Created by Tiago Loureiro on 19/03/2024.
//

#include <iostream>
#include "TerminalFlow.h"
#include "../classes/WaterSupply.h"
#include "../utils/FileReader.h"

void TerminalFlow::call() {
    std::cout << std::endl;
    std::cout << "=||= Welcome to your Water Pipeline Management System =||=" << std::endl;
    std::cout << std::endl;

    WaterSupply<std::string> ws;

    std::string reservoir_file_path = "../files/Project1DataSetSmall/Reservoirs_Madeira.csv";
    std::string station_file_path = "../files/Project1DataSetSmall/Stations_Madeira.csv";
    std::string city_file_path = "../files/Project1DataSetSmall/Cities_Madeira.csv";
    std::string pipe_file_path = "../files/Project1DataSetSmall/Pipes_Madeira.csv";

    //FileReader::addReservoirs(reservoir_file_path,ws);
    //FileReader::addStations(station_file_path,ws);
    //FileReader::addCities(city_file_path,ws);
    //FileReader::addPipes(pipe_file_path,ws);

    // Read and parse input data

    // Determine maximum water flow
    //ws.determineMaxWaterFlow();

    // Check network configuration
    //ws.checkNetworkConfiguration();

    // Evaluate impact of failures
    //ws.evaluateFailures();

}