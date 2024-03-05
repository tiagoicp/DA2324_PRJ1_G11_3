#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../App/Lib/db_loader.h"

using testing::Eq;

TEST(DbLoader, LoadsAirlines) {
    unordered_map<string, Airline> airlines = DbLoader::loadAirlines();

    EXPECT_EQ(airlines.size(), 444);
}

TEST(DbLoader, LoadsAirports) {
    unordered_map<string, Airport> airports = DbLoader::loadAirports();

    EXPECT_EQ(airports.size(), 3019);
}

TEST(DbLoader, LoadsFlights) {
    unordered_map<string, Airport> airports = DbLoader::loadAirports();
    unordered_map<string, Route> routes = DbLoader::loadRoutes(airports);

    EXPECT_EQ(routes.size(), 35480);
}