#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "terminal/TerminalFlow.h"
#include "classes/WaterSupply.h"

using namespace std;

/**
 * Run all tests OR start Project Terminal
 *
 * @param argc
 * @param argv
 * @return exit code
 */
int main(int argc, char* argv[]) {
    bool isTesting = false;
    if(isTesting) {
        // tests
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    else {
        // terminal
        WaterSupply ws;
        TerminalFlow::call(ws);
    }

    return 0;
}