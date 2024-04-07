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

void setupMadeiraGraph(WaterSupply& network) {
    // setup all vertexes before adding edges
    std::string reservoir_file_path = "../files/Project1DataSetSmall/Reservoirs_Madeira.csv";
    std::string station_file_path = "../files/Project1DataSetSmall/Stations_Madeira.csv";
    std::string city_file_path = "../files/Project1DataSetSmall/Cities_Madeira.csv";
    FileReader::addReservoirs(reservoir_file_path,network);
    FileReader::addPumpingStations(station_file_path,network);
    FileReader::addCities(city_file_path,network);

    // add edges / pipes
    std::string pipe_file_path = "../files/Project1DataSetSmall/Pipes_Madeira.csv";
    FileReader::addPipes(pipe_file_path,network);
}

TEST(Functionality, maxFlowCity) {
    WaterSupply network;
    setupGraph(network);

    string city = "C_2";
    string result = Functionality::maxFlowCity(network, city);
    EXPECT_EQ(result, "The maximum amount of water that can reach the city C_2 is 560 m^3/sec. Maximum incoming capacity = 560.\nDemand = 515.");

    city = "C_10";
    result = Functionality::maxFlowCity(network, city);
    EXPECT_EQ(result, "The maximum amount of water that can reach the city C_10 is 220 m^3/sec. Maximum incoming capacity = 300.\nDemand = 313. There is no possible configuration that can meet this city's needs.");
}

TEST(Functionality, maxFlowGraph) {
    WaterSupply network;
    setupGraph(network);

    vector<string> result = Functionality::maxFlowGraph(network);
    EXPECT_EQ(result[3], "The city C_3 is supplied with only 110 m^3/sec, resulting in a water flow deficit of 50 m^3/sec.");
    EXPECT_EQ(result[4], "The city C_4 is supplied with the desired water rate level of 1208 m^3/sec.");
    EXPECT_EQ(result[8], "The city C_8 is supplied with only 100 m^3/sec, resulting in a water flow deficit of 22 m^3/sec.");
}

TEST(Functionality, maxFlowGraphCleansFirst) {
    WaterSupply network;
    setupGraph(network);

    Functionality::maxFlowGraph(network);
    vector<string> result = Functionality::maxFlowGraph(network);
    EXPECT_EQ(result[3], "The city C_3 is supplied with only 110 m^3/sec, resulting in a water flow deficit of 50 m^3/sec.");
    EXPECT_EQ(result[4], "The city C_4 is supplied with the desired water rate level of 1208 m^3/sec.");
    EXPECT_EQ(result[8], "The city C_8 is supplied with only 100 m^3/sec, resulting in a water flow deficit of 22 m^3/sec.");
}

TEST(Functionality, balanceMaxFlowGraph) {
    WaterSupply network;
    setupGraph(network);

    Functionality::maxFlowGraph(network);
    vector<double> initStats = network.getNetworkBalanceStats();

    Functionality::balanceMaxFlowGraph(network);
    vector<double> stats = network.getNetworkBalanceStats();

    EXPECT_EQ(stats[0], initStats[0]);
    EXPECT_LT(stats[1], initStats[1]);
    EXPECT_EQ(stats[2], initStats[2]);
}

TEST(Functionality, balanceMaxFlowGraphWithMadeiraSample) {
    WaterSupply network;
    setupMadeiraGraph(network);

    Functionality::maxFlowGraph(network);
    vector<double> initStats = network.getNetworkBalanceStats();

    Functionality::balanceMaxFlowGraph(network);
    vector<double> stats = network.getNetworkBalanceStats();

    EXPECT_EQ(stats[0], initStats[0]);
    EXPECT_LT(stats[1], initStats[1]);
    EXPECT_EQ(stats[2], initStats[2]);
}