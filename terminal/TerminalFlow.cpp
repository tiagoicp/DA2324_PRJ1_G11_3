//
// Created by Tiago Loureiro on 19/03/2024.
//

#include <iostream>
#include "TerminalFlow.h"
#include "../classes/WaterSupply.h"

using namespace std;

void TerminalFlow::call() {
    cout << endl;
    cout << "=||= Welcome to your Water Pipeline Management System =||=" << endl;
    cout << endl;

    WaterSupply ws;

    string reservoir_file_path = "../Project1DataSetSmall/Reservoirs_Madeira.csv";
    string station_file_path = "../Project1DataSetSmall/Stations_Madeira.csv";
    string city_file_path = "../Project1DataSetSmall/Cities_Madeira.csv";
    string pipe_file_path = "../Project1DataSetSmall/Pipes_Madeira.csv";

    // Read and parse input data

    // Determine maximum water flow
    //ws.determineMaxWaterFlow();

    // Check network configuration
    //ws.checkNetworkConfiguration();

    // Evaluate impact of failures
    //ws.evaluateFailures();

}