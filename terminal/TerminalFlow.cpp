//
// Created by Tiago Loureiro on 19/03/2024.
//

#include <iostream>
#include "TerminalFlow.h"

using namespace std;

void TerminalFlow::call(WaterSupply& ws) {
    cout << endl;
    cout << "Welcome to our Water Supply Management System" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Please choose a functionality of the following:" << endl;
    cout << "1. Read and parse the input data" << endl;
    cout << "2. Determine maximum amount of water that can reach each city" << endl;
    cout << "3. Determine maximum amount of water that can reach a specific city" << endl;
    cout << "4. Check if the network configuration meets the water needs" << endl;
    cout << "5. Balance the load across the network"<< endl;
    cout << "6. Determine which cities are affected by a reservoir failure" << endl;
    cout << "7. Identify pumping stations that can be out of service without impacting overall city delivery capacity" << endl;
    cout << "8. Identify pipeline failures that would impede delivering required water to each city" << endl;
    cout << "9. Exit"<< endl;
    int selected;
    cin >> selected;
    cout << endl;
    string city;
    switch (selected){
        case 1 :
            getReadDataMenu(ws);
            call(ws);
            break;
        case 2 : 
            for (auto v : ws.getDstSet()){
                string code = v->getInfo();
                Functionality::maxFlowCity(&ws,code);
            }
            call(ws);
            break;
        case 3 :
            cout << "Insert the city code (C_i):"<< endl;
            cin >> city;
            Functionality::maxFlowCity(&ws,city);
            call(ws);
            break;
        case 4 :
            Functionality::maxFlowGraph(&ws);
            call(ws);
            break;
        case 5 :

            call(ws);
            break;
        case 6 :

            call(ws);
            break;
        case 7 :

            call(ws);
            break;
        case 8 :

            call(ws);
            break;
        case 9 :
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }

}

void TerminalFlow::getReadDataMenu(WaterSupply& ws){
    cout << "Please choose a dataset of the following:" << endl;
    cout << "1. Madeira Dataset" << endl;
    cout << "2. Portugal Dataset" << endl;
    int selected;
    cin >> selected;
    string reservoir_file_path = "";
    string station_file_path = "";
    string city_file_path = "";
    string pipe_file_path = "";
    switch (selected){
        case 1 :
            reservoir_file_path = "../files/Project1DataSetSmall/Reservoirs_Madeira.csv";
            station_file_path = "../files/Project1DataSetSmall/Stations_Madeira.csv";
            city_file_path = "../files/Project1DataSetSmall/Cities_Madeira.csv";
            pipe_file_path = "../files/Project1DataSetSmall/Pipes_Madeira.csv";
            break;
        case 2 : 
            reservoir_file_path = "../files/Project1LargeDataSet/Reservoir.csv";
            station_file_path = "../files/Project1LargeDataSet/Stations.csv";
            city_file_path = "../files/Project1LargeDataSet/Cities.csv";
            pipe_file_path = "../files/Project1LargeDataSet/Pipes.csv";
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
    FileReader::addReservoirs(reservoir_file_path,ws);
    FileReader::addPumpingStations(station_file_path,ws);
    FileReader::addCities(city_file_path,ws);
    FileReader::addPipes(pipe_file_path,ws);
    cout << "Files have been read correctly" << endl;
}