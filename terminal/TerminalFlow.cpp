//
// Created by Tiago Loureiro on 19/03/2024.
//

#include <iostream>
#include <cmath>
#include <numeric>
#include "TerminalFlow.h"

using namespace std;

void TerminalFlow::call(WaterSupply &ws) {
    cout << endl;
    cout << "Welcome to our Water Supply Management System" << endl;
    cout << "---------------------------------------------" << endl;
    getReadDataMenu(ws);
    mainMenu(ws);
}

void TerminalFlow::mainMenu(WaterSupply &ws) {
    cout << endl;
    cout << "Please choose a functionality of the following:" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "1. Determine maximum amount of water that can reach each city" << endl;
    cout << "2. Determine maximum amount of water that can reach a specific city" << endl;
    cout << "3. Check if the network configuration meets the water needs" << endl;
    cout << "4. Balance the load across the network" << endl;
    cout << "5. Determine which cities are affected by a reservoir failure" << endl;
    cout << "6. Identify pumping stations that can be out of service without impacting overall city delivery capacity"
         << endl;
    cout << "7. Identify pipeline failures that would impede delivering required water to each city" << endl;
    cout << "8. Exit" << endl;

    int selected;
    cin >> selected;
    cin.ignore(9999999, '\n'); // always clean cin (to avoid issue with getline
    cout << endl;

    string cityCode;
    switch (selected) {
        case 1 :
            for (auto v: ws.getDstSet()) {
                string code = v->getInfo();
                cout << Functionality::maxFlowCity(&ws, code) << endl;
            }
            mainMenu(ws);
            break;
        case 2 :
            cityCode = getValidCityCode(ws);
            cout << Functionality::maxFlowCity(&ws, cityCode) << endl;
            mainMenu(ws);
            break;
        case 3 :
            printVector(Functionality::maxFlowGraph(&ws));
            mainMenu(ws);
            break;
        case 4 :
            Functionality::maxFlowGraph(&ws);
            printPipeLoad(ws); // print current load of edges/pipes
            // run pipe balancer algorithm
            // print final load of edges/pipes
            mainMenu(ws);
            break;
        case 5 :
            Functionality::maxFlowGraphBalanced(&ws);
            printPipeLoad(ws);
        case 6 :
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

void TerminalFlow::printPipeLoad(WaterSupply& ws) {
    vector<double> diffVector;
    double totalFlow = ws.getSinkFlow();
    cout << "Current Network / Pipe Load:" << endl;
    for(auto node : ws.getNodeSet()){
        if(node->getInfo() == "master_source" || node->getInfo() == "master_sink")
            continue;

        if(node->getAdj().empty())
            continue;

        if(node->getAdj().size() == 1 && node->getAdj()[0]->getDest()->getInfo() == "master_sink")
            continue;

        cout << "From node " << node->getInfo() << ":" << endl;
        for(auto pipe : node->getAdj()){
            if(pipe->getDest()->getInfo() == "master_sink")
                continue;

            diffVector.push_back(pipe->getWeight()-pipe->getFlow());
            cout << "- to " << pipe->getDest()->getInfo() << " (" << to_string(int(pipe->getFlow())) << "/" << to_string(int(pipe->getWeight())) <<")" << endl;
        }
    }
    cout << endl;
    cout << "Average diff: " << getAverage(diffVector) << endl;
    cout << "Std Dev of diff: " << getStdDev(diffVector) << endl;
    cout << "Sink flow: " << totalFlow << endl;
    cout << endl;
}

double TerminalFlow::getAverage(const vector<double>& v){
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    return sum / v.size();
}

double TerminalFlow::getStdDev(const vector<double>& v){
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    return std::sqrt(sq_sum / v.size());
}

string TerminalFlow::getValidCityCode(WaterSupply &ws) {
    string cityCode;
    while (true) {
        cout << "Insert a city code: (eg: C_1)" << endl;
        getline(cin, cityCode);
        if (ws.findNode(cityCode) != nullptr)
            break;

        cout << "You wrote an invalid input or city not found." << endl;
        cout << "Example of a valid input: C_2" << endl;
        cout << endl;
    }

    return cityCode;
}

void TerminalFlow::printVector(const vector<string> &resultVector) {
    for (const string &s: resultVector) {
        cout << s << endl;
    }
}

void TerminalFlow::getReadDataMenu(WaterSupply &ws) {
    cout << "Please choose a dataset of the following:" << endl;
    cout << "1. Madeira Dataset" << endl;
    cout << "2. Portugal Dataset" << endl;
    int selected;
    cin >> selected;
    string reservoir_file_path = "";
    string station_file_path = "";
    string city_file_path = "";
    string pipe_file_path = "";
    switch (selected) {
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
    FileReader::addReservoirs(reservoir_file_path, ws);
    FileReader::addPumpingStations(station_file_path, ws);
    FileReader::addCities(city_file_path, ws);
    FileReader::addPipes(pipe_file_path, ws);
    cout << "Files have been read correctly" << endl;
}