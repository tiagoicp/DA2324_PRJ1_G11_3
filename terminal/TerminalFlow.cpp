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
    getReadDataMenu(ws);
    mainMenu(ws);
}

void TerminalFlow::mainMenu(WaterSupply& ws){
    cout << endl;
    cout << "Please choose a functionality of the following:" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "1. Determine maximum amount of water that can reach each city" << endl;
    cout << "2. Determine maximum amount of water that can reach a specific city" << endl;
    cout << "3. Check if the network configuration meets the water needs" << endl;
    cout << "4. Balance the load across the network"<< endl;
    cout << "5. Determine which cities are affected by a reservoir failure" << endl;
    cout << "6. Identify pumping stations that can be out of service without impacting overall city delivery capacity" << endl;
    cout << "7. Identify pipeline failures that would impede delivering required water to each city" << endl;
    cout << "8. Exit"<< endl;

    int selected;
    cin >> selected;
    cout << endl;

    string city;
    switch (selected){
        case 1 :
            for (auto v : ws.getDstSet()){
                string code = v->getInfo();
                cout << Functionality::maxFlowCity(&ws,code) << endl;
            }
            mainMenu(ws);
            break;
        case 2 :
            cout << "Insert the city code (C_i):"<< endl;
            cin >> city;
            cout << Functionality::maxFlowCity(&ws,city) << endl;
            mainMenu(ws);
            break;
        case 3 :
            Functionality::maxFlowGraph(&ws);
            mainMenu(ws);
            break;
        case 4 :
            mainMenu(ws);
            break;
        case 5 :
            mainMenu(ws);
            break;
        case 6 :
            mainMenu(ws);
            break;
        case 7 :
            mainMenu(ws);
            break;
        case 8 :
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
            mainMenu(ws);
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