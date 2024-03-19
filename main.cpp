//#include "gtest/gtest.h"
//#include "gmock/gmock.h"
//#include "env.h"
//#include "App/sky_scannix.h"
#include "WaterSupply.h"

using namespace std;

int main() {
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

    return 0;
}


/**
 * Run all tests OR start Project Terminal
 *
 * @param argc
 * @param argv
 * @return exit code
 */
/*int main(int argc, char* argv[]) {
    // SkyScannix s = SkyScannix();
    int success = 0;
    switch(constants::CHOSEN_FLOW) {
        case 0: // test
            testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
            break;
        case 1: // terminal
            // success = s.runTerminalFlow();
            break;
        default:
            break;
    }

    return success;
}*/