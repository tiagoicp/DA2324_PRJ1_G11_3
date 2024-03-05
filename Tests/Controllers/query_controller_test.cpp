#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../App/Controllers/query_controller.h"

using testing::Eq;

TEST(QueryController, sortsByAirlineChanges) {
    AirportGraph graph;
    unordered_map<string, Airport> airports;
    unordered_map<string, Airline> airlines;

    QueryController q = {graph, airports, airlines, {}, {}};

    list<Route> l1;
    list<Route> l2;
    Route r = {"OPO", "LIS", 0};
    r.addAirlineCode("TAP");
    r.addAirlineCode("RYR");
    l1.push_back(r);
    l2.push_back(r);

    // Same Airline
    r = {"LIS", "MAD", 0};
    r.addAirlineCode("RYR");
    l1.push_back(r);
    r = {"MAD", "PMI", 0};
    r.addAirlineCode("TAP");
    r.addAirlineCode("RYR");
    l1.push_back(r);

    // 1 Airline Change
    r = {"LIS", "BCN", 0};
    r.addAirlineCode("TAP");
    l2.push_back(r);
    r = {"BCN", "PMI", 0};
    r.addAirlineCode("RYR");
    l2.push_back(r);

    vector<list<Route>> routes = {l2, l1};

    q.sortAndSelectTop(routes);

    EXPECT_EQ(*routes.begin(), l1);
}

TEST(QueryController, sortsByDistance) {
    AirportGraph graph;
    unordered_map<string, Airport> airports;
    unordered_map<string, Airline> airlines;

    QueryController q = {graph, airports, airlines, {}, {}};

    list<Route> l1;
    list<Route> l2;
    Route r = {"OPO", "LIS", 1};
    r.addAirlineCode("TAP");
    r.addAirlineCode("RYR");
    l1.push_back(r);
    l2.push_back(r);

    // shorter distance
    r = {"LIS", "MAD", 1};
    r.addAirlineCode("TAP");
    r.addAirlineCode("RYR");
    l1.push_back(r);
    r = {"MAD", "PMI", 1};
    r.addAirlineCode("TAP");
    r.addAirlineCode("RYR");
    l1.push_back(r);

    // bigger distance
    r = {"LIS", "BCN", 2};
    r.addAirlineCode("TAP");
    r.addAirlineCode("RYR");
    l2.push_back(r);
    r = {"BCN", "PMI", 2};
    r.addAirlineCode("TAP");
    r.addAirlineCode("RYR");
    l2.push_back(r);

    vector<list<Route>> routes = {l2, l1};

    q.sortAndSelectTop(routes);

    EXPECT_EQ(*routes.begin(), l1);
}