# Sky Scannix

## AED 2022 - 2nd Group Work
 
Author: Tiago Loureiro (200706716)

Description: Terminal Module, allowing a user to see several analysis or queries to airline data. 

## Feature List
1) Load Files
2) Store classes in a key -> reference solution (unordered_map)
3) Build graphs for later use
4) Show Menu
5) Query top routes between 2 locations (based on lowest nr of routes +1)
   1) Allow "smart" input location (nome aeroporto, código aeroporto, OU cidade, país, OU coordenadas + kms)
   2) Allow Airline filtering (all, one or many)
   3) If same nr, choose based on lowest nr of Airline changes, then Distance
6) Airport Reach Stats
7) Network Stats
8) Network Analysis
   1) Graph Diameter
   2) Articulation points 

## Classes
- SkyScannix (MainController, State Machine, DB)
  - Airports (AirportCode -> Airport)
  - Airlines (AirlineCode -> Airline)
  - Flights vector<Route>
  - AirportGraph (Airport (vertice) -> set<AirlineCodes> (edges))
    - AirportPosix (AirportCode -> Position in AirportGraph)
    - nodes (vector<list<set<AirlineCodes>)
  - AirportCodesByCountry (Country -> set<AirportCodes>)
  - AirportCodesByCity ("City, Country" -> set<AirportCodes>)
- Models
  - Airport
  - Airline
  - Route
- Controllers && Views
  - Menu
  - ShortestPathQuery
  - AirportStats
  - AirportReachStats
  - NetworkStats
  - ArticulationPoints
- Lib
  - CsvParser
  - DbLoader
  - InputWrapper
  - FileWrapper
  

## Other Notes