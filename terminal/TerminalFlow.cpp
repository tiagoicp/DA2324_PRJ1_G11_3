//
// Created by Tiago Loureiro on 19/03/2024.
//

#include <iostream>
#include "TerminalFlow.h"
#include "../classes/WaterSupply.h"
#include "../utils/FileReader.h"
#include "../classes/Functionality.h"

using namespace std;

void TerminalFlow::call() {
    cout << endl;
    cout << "=||= Welcome to your Water Pipeline Management System =||=" << endl;
    cout << endl;

    WaterSupply ws;

    /*string reservoir_file_path = "../files/Project1DataSetSmall/Reservoirs_Madeira.csv";
    string station_file_path = "../files/Project1DataSetSmall/Stations_Madeira.csv";
    string city_file_path = "../files/Project1DataSetSmall/Cities_Madeira.csv";
    string pipe_file_path = "../files/Project1DataSetSmall/Pipes_Madeira.csv";*/

    string reservoir_file_path = "../files/Project1LargeDataSet/Reservoir.csv";
    string station_file_path = "../files/Project1LargeDataSet/Stations.csv";
    string city_file_path = "../files/Project1LargeDataSet/Cities.csv";
    string pipe_file_path = "../files/Project1LargeDataSet/Pipes.csv";

    FileReader::addReservoirs(reservoir_file_path,ws);
    FileReader::addPumpingStations(station_file_path,ws);
    FileReader::addCities(city_file_path,ws);
    FileReader::addPipes(pipe_file_path,ws);

    // to select a single city just call the function once with the desired city code.
    for (auto v : ws.getDstSet()){
        string code = v->getInfo();
        Functionality::maxFlowCity(&ws,code);
    }
    cout << endl;
    Functionality::maxFlowGraph(&ws);

}