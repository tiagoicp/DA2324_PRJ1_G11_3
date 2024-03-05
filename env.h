#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <map>

using namespace std;

namespace constants {
    static const int CHOSEN_FLOW = 0; // 0 - test | 1 - terminal
    static const int TOP_QUERY_RESULTS = 10;
    static const map<string, string> PATH_MAP = {
            {"airlines",      "../App/Assets/csv/airlines.csv"},
            {"airports",      "../App/Assets/csv/airports.csv"},
            {"flights",       "../App/Assets/csv/flights.csv"}
    };
}

#endif
