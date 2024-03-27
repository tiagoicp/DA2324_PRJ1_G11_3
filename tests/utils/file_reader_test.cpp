#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../utils/FileReader.h"

using testing::Eq;

TEST(FileReader, addReservoirsSmallDataSet) {
    WaterSupply network;
    std::string file_path = "../files/Project1DataSetSmall/Reservoirs_Madeira.csv";
    FileReader::addReservoirs(file_path,network);
    EXPECT_EQ(network.getReservoirs().size(), 4);

    auto found = network.getReservoirs().at("R_1");
    EXPECT_EQ(found.getName(), "Ribeira do Seixal");
    EXPECT_EQ(found.getMunicipality(), "Porto Moniz");
    EXPECT_EQ(found.getId(), 1);
    EXPECT_EQ(found.getCode(), "R_1");
    EXPECT_EQ(found.getMaxDelivery(), 525);
}

TEST(FileReader, addReservoirsLargeDataSet) {
    WaterSupply network;
    std::string file_path = "../files/Project1LargeDataSet/Reservoir.csv";
    FileReader::addReservoirs(file_path,network);
    EXPECT_EQ(network.getReservoirs().size(), 24);

    auto found = network.getReservoirs().at("R_10");
    EXPECT_EQ(found.getName(), "Pretarouca");
    EXPECT_EQ(found.getMunicipality(), "Viseu");
    EXPECT_EQ(found.getId(), 10);
    EXPECT_EQ(found.getCode(), "R_10");
    EXPECT_EQ(found.getMaxDelivery(), 280);
}

TEST(FileReader, addStationsLargeDataSet) {
    WaterSupply network;
    std::string file_path = "../files/Project1LargeDataSet/Stations.csv";
    FileReader::addPumpingStations(file_path,network);
    EXPECT_EQ(network.getPumpingStations().size(), 81);

    auto found = network.getPumpingStations().at("PS_61");
    EXPECT_EQ(found.getId(), 61);
    EXPECT_EQ(found.getCode(), "PS_61");
}

TEST(FileReader, addCitiesLargeDataSet) {
    WaterSupply network;
    std::string file_path = "../files/Project1LargeDataSet/Cities.csv";
    FileReader::addCities(file_path,network);
    EXPECT_EQ(network.getCities().size(), 22);

    auto found = network.getCities().at("C_17");
    EXPECT_EQ(found.getCity(), "Porto");
    EXPECT_EQ(found.getId(), 17);
    EXPECT_EQ(found.getCode(), "C_17");
    EXPECT_EQ(found.getDemand(), 6324.00);
    EXPECT_EQ(found.getPopulation(), 948613);
}

TEST(FileReader, addPipesLargeDataSet) {
    WaterSupply network;

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

    EXPECT_EQ(network.getNodeSet().size(), 127);

    auto node_found = network.findNode("R_5");
    EXPECT_EQ(node_found->getAdj().size(), 2);

    auto pipe_found = node_found->getAdj()[0];
    EXPECT_EQ(pipe_found->getWeight(), 2000);
    EXPECT_EQ(pipe_found->getOrig()->getInfo(), "R_5");
    EXPECT_EQ(pipe_found->getDest()->getInfo(), "PS_1");

    // also test bi-direction
    node_found = network.findNode("PS_62");
    EXPECT_EQ(node_found->getAdj().size(), 4);

    pipe_found = node_found->getAdj()[1];
    EXPECT_EQ(pipe_found->getWeight(), 3000);
    EXPECT_EQ(pipe_found->getOrig()->getInfo(), "PS_62");
    EXPECT_EQ(pipe_found->getDest()->getInfo(), "PS_58");
}

