//
// Created by Tiago Loureiro on 19/03/2024.
//

#ifndef DA2324_PRJ1_G11_3_TERMINALFLOW_H
#define DA2324_PRJ1_G11_3_TERMINALFLOW_H

#include <iostream>
#include "../classes/WaterSupply.h"
#include "../utils/FileReader.h"
#include "../functionalities/Functionality.h"

class TerminalFlow {
public:
    static void call(WaterSupply& ws);
    static void getReadDataMenu(WaterSupply& ws);
    static void mainMenu(WaterSupply& ws);
private:
    static void printVector(const vector<string>& resultVector);
    static string getValidCityCode(WaterSupply& ws);
    static string getValidReservoirCode(WaterSupply& ws);
    static void printPipeLoad(WaterSupply& ws);
    static double getAverage(const vector<double>& v);
    static double getStdDev(const vector<double>& v);
};


#endif //DA2324_PRJ1_G11_3_TERMINALFLOW_H
