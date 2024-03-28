//
// Created by Tiago Loureiro on 19/03/2024.
//

#ifndef DA2324_PRJ1_G11_3_TERMINALFLOW_H
#define DA2324_PRJ1_G11_3_TERMINALFLOW_H

#include <iostream>
#include "../classes/WaterSupply.h"
#include "../utils/FileReader.h"
#include "../classes/Functionality.h"

class TerminalFlow {
public:
    static void call(WaterSupply& ws);
    static void getReadDataMenu(WaterSupply& ws);
};


#endif //DA2324_PRJ1_G11_3_TERMINALFLOW_H
