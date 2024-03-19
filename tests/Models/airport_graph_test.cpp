#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../App/Models/airport_graph.h"
#include "../../App/Models/airport.h"
#include "../../App/Models/route.h"
#include "../../App/Lib/db_loader.h"

using testing::Eq;

AirportGraph setupGraph() {
    AirportGraph g;

    unordered_map<string, Airport> airports = DbLoader::loadAirports();
    unordered_map<string, Route> routes = DbLoader::loadRoutes(airports);

    for (auto &airport: airports) {
        g.addNode(airport.second.getCode());
    }

    for (auto &routePair: routes) {
        g.addEdge(routePair.second);
    }

    return g;
}

TEST(AirportGraph, addsNode) {
    AirportGraph g;
    g.addNode("OPO");
    EXPECT_EQ(g.nodeSize(), 1);
}

TEST(AirportGraph, addsEdge) {
    AirportGraph g;
    g.addNode("OPO");
    g.addNode("LIS");
    Route r = {"OPO", "LIS", 0};
    r.addAirlineCode("TAP");
    g.addEdge(r);
    EXPECT_EQ(g.edgeSize("OPO"), 1);
}

TEST(AirportGraph, whenWholeGraphBuilt) {
    AirportGraph g = setupGraph();

    EXPECT_EQ(g.nodeSize(), 3019);
    EXPECT_EQ(g.edgeSize("OPO"), 61);
}

TEST(AirportGraph, calcShortestRoutes) {
    AirportGraph g = setupGraph();
    vector<list<Route>> routes;
    list<Route> l;
    vector<string> airlineCodes;

    // short, 1 route case
    Route r = {"OPO", "LIS", 0};
    r.addAirlineCode("RYR");
    r.addAirlineCode("RZO");
    r.addAirlineCode("TAP");
    r.addAirlineCode("TSC");
    r.addAirlineCode("USA");
    l.push_back(r);
    routes.push_back(l);

    EXPECT_EQ(g.shortestRoutes("OPO", "LIS", airlineCodes), routes);

    // long, 3 routes case
    EXPECT_EQ(g.shortestRoutes("OPO", "DPS", airlineCodes).size(), 77);
}

TEST(AirportGraph, calcShortestRoutesWithFilter) {
    AirportGraph g = setupGraph();
    vector<list<Route>> routes;
    list<Route> l;
    vector<string> airlineCodes;

    // short, 1 route case
    Route r = {"OPO", "LIS", 0};
    r.addAirlineCode("RYR");
    r.addAirlineCode("RZO");
    r.addAirlineCode("TAP");
    r.addAirlineCode("TSC");
    r.addAirlineCode("USA");
    l.push_back(r);
    routes.push_back(l);

    // should find route
    airlineCodes = {"TAP"};
    EXPECT_EQ(g.shortestRoutes("OPO", "LIS", airlineCodes), routes);

    // should NOT find route
    routes = {};
    EXPECT_EQ(g.shortestRoutes("OPO", "DPS", airlineCodes), routes);
    airlineCodes = {"THY"};
    EXPECT_EQ(g.shortestRoutes("OPO", "LIS", airlineCodes), routes);
}

TEST(AirportGraph, calcAirportStats) {
    AirportGraph g = setupGraph();
    unordered_map <string, Airport> airports = DbLoader::loadAirports();
    unordered_map <string, set<string>> answeredStats = g.airportStats("OPO", 1, airports, {});

    // Airports
    EXPECT_EQ(answeredStats["airports"].size(), 61);

    // Airlines
    EXPECT_EQ(answeredStats["airlines"].size(), 22);

    // Cities
    EXPECT_EQ(answeredStats["cities"].size(), 57);

    // Countries
    EXPECT_EQ(answeredStats["countries"].size(), 16);
}

TEST(AirportGraph, calcAirportStatsWithReach) {
    AirportGraph g = setupGraph();
    unordered_map <string, Airport> airports = DbLoader::loadAirports();
    // with a higher reach
    unordered_map <string, set<string>> answeredStats = g.airportStats("OPO", 3, airports, {});

    // Airports
    EXPECT_EQ(answeredStats["airports"].size(), 2252);

    // Airlines
    EXPECT_EQ(answeredStats["airlines"].size(), 410);

    // Cities
    EXPECT_EQ(answeredStats["cities"].size(), 2198);

    // Countries
    EXPECT_EQ(answeredStats["countries"].size(), 214);
}

TEST(AirportGraph, calcNetworkStats) {
    AirportGraph g = setupGraph();
    unordered_map<string, Airport> airports = DbLoader::loadAirports();
    // with a higher reach
    unordered_map<string, set<string>> answeredStats = g.networkStats(airports);

    // Airports
    EXPECT_EQ(answeredStats["airports"].size(), 3006);

    // Airlines
    EXPECT_EQ(answeredStats["airlines"].size(), 444);

    // Cities
    EXPECT_EQ(answeredStats["cities"].size(), 2943);

    // Countries
    EXPECT_EQ(answeredStats["countries"].size(), 225);
}

TEST(AirportGraph, calcGraphDiameter) {
    AirportGraph g = setupGraph();
    EXPECT_EQ(g.calcGraphDiameter({"TAP"}), 4);
    EXPECT_EQ(g.calcGraphDiameter({}), 12);
}

TEST(AirportGraph, calcArticulationPoints) {
    AirportGraph g = setupGraph();
    EXPECT_EQ(g.calcArticulationPoints().size(), 47);
}