#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "env.h"
//#include "App/sky_scannix.h"

/**
 * Run all tests OR start Project Terminal
 *
 * @param argc
 * @param argv
 * @return exit code
 */
int main(int argc, char* argv[]) {
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
}