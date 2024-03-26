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

