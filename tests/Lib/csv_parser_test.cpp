#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../App/Lib/csv_parser.h"

using testing::Eq;

TEST(CsvParser, ParsesHeader) {
    string header = "Code,Name,Callsign,Country";
    vector<string> parsed = {"Code", "Name", "Callsign", "Country"};

    EXPECT_EQ(CsvParser::parseHeader(header), parsed);
}

TEST(CsvParser, ParsesToFlight) {
    string line = "ORY,LHR,IBE";

    Route r = Route("ORY", "LHR", 0);
    r.addAirlineCode("IBE");

    unordered_map<string, Route> routes1;
    unordered_map<string, Route> routes2;

    routes1[r.getCompositeKey()] = r;
    unordered_map<string, Airport> airports;
    airports["ORY"] = {};
    airports["LHR"] = {};
    CsvParser::parseToRoute(line, routes2, airports);
    EXPECT_EQ(routes1, routes2);
}

TEST(CsvParser, ParsesToAirport) {
    string line = "PUM,Pomalaa,Pomalaa,Indonesia,-4.183333,121.616670";

    Airport a = Airport("PUM", "Pomalaa", "Pomalaa", "Indonesia", -4.183333, 121.616670);

    EXPECT_EQ(CsvParser::parseToAirport(line), a);
}

TEST(CsvParser, ParsesToAirline) {
    string line = "IBE,Iberia Airlines,IBERIA,Spain";

    Airline a = Airline("IBE","Iberia Airlines","IBERIA","Spain");

    EXPECT_EQ(CsvParser::parseToAirline(line), a);
}