#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../utils/FileReader.h"
#include "../../functionalities/Functionality.h"

using testing::Eq;

void setupGraph(WaterSupply& network) {
    // setup all vertexes before adding edges
    std::string reservoir_file_path = "../files/Project1LargeDataSet/Reservoir.csv";
    std::string station_file_path = "../files/Project1LargeDataSet/Stations.csv";
    std::string city_file_path = "../files/Project1LargeDataSet/Cities.csv";
    FileReader::addReservoirs(reservoir_file_path,network);
    FileReader::addPumpingStations(station_file_path,network);
    FileReader::addCities(city_file_path,network);

    // add edges / pipes
    std::string pipe_file_path = "../files/Project1LargeDataSet/Pipes.csv";
    FileReader::addPipes(pipe_file_path,network);
}

TEST(Functionality, maxFlowCity) {
    WaterSupply network;
    setupGraph(network);

    string city = "C_2";
    string result = Functionality::maxFlowCity(&network, city);
    EXPECT_EQ(result, "The maximum amount of water that can reach the city C_2 is 560 m^3/sec. City maximum capacity = 560.");

    city = "C_10";
    result = Functionality::maxFlowCity(&network, city);
    EXPECT_EQ(result, "The maximum amount of water that can reach the city C_10 is 220 m^3/sec. City maximum capacity = 300.");
}

TEST(Functionality, maxFlowGraph) {
    WaterSupply network;
    setupGraph(network);

    vector<string> result = Functionality::maxFlowGraph(&network);
    EXPECT_EQ(result[3], "The maximum amount of water that can reach the city C_3 is 110 m^3/sec. (water flow in deficit = 50)");
    EXPECT_EQ(result[4], "The maximum amount of water that can reach the city C_4 is 1208 m^3/sec. (water flow in deficit = 0)");
    EXPECT_EQ(result[8], "The maximum amount of water that can reach the city C_8 is 100 m^3/sec. (water flow in deficit = 22)");
}

TEST(Functionality, maxFlowGraphCleansFirst) {
    WaterSupply network;
    setupGraph(network);

    Functionality::maxFlowGraph(&network);
    vector<string> result = Functionality::maxFlowGraph(&network);
    EXPECT_EQ(result[3], "The maximum amount of water that can reach the city C_3 is 110 m^3/sec. (water flow in deficit = 50)");
    EXPECT_EQ(result[4], "The maximum amount of water that can reach the city C_4 is 1208 m^3/sec. (water flow in deficit = 0)");
    EXPECT_EQ(result[8], "The maximum amount of water that can reach the city C_8 is 100 m^3/sec. (water flow in deficit = 22)");
}