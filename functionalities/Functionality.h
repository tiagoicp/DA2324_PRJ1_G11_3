//
// Created by jonas on 26/03/2024.
//

#ifndef DA2324_PRJ1_G11_3_FUNCTIONALITY_H
#define DA2324_PRJ1_G11_3_FUNCTIONALITY_H


#include "../classes/City.h"
#include "../classes/WaterSupply.h"
#include <iostream>

class Functionality {
public:
    static string maxFlowCity(WaterSupply& graph, string& cityCode);
    static vector<string> maxFlowGraph(WaterSupply& graph);
    static void maxFlowGraphBalanced(WaterSupply& graph);
    static void removeReservoirAndListAffectedCities(WaterSupply& graph, const string& reservoirCode);
    static void checkUselessPumpingStations(WaterSupply& graph);
    static void checkCriticalPipes(WaterSupply& graph);
};


#endif //DA2324_PRJ1_G11_3_FUNCTIONALITY_H
