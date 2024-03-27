//
// Created by jonas on 26/03/2024.
//

#ifndef DA2324_PRJ1_G11_3_FUNCTIONALITY_H
#define DA2324_PRJ1_G11_3_FUNCTIONALITY_H


#include "City.h"
#include "WaterSupply.h"
#include <iostream>

class Functionality {
public:
    static void maxFlowCity(WaterSupply* graph, string& cityCode);
    static void maxFlowGraph(WaterSupply* graph);
};


#endif //DA2324_PRJ1_G11_3_FUNCTIONALITY_H
