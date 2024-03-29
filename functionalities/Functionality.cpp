// Implement the functionalities here

#include <sstream>
#include <iomanip>
#include "Functionality.h"
#include "../classes/edmonds_karp.h"

string Functionality::maxFlowCity(WaterSupply *graph, string &cityCode) {
    vector<Vertex<string> *> reachableSources;
    Vertex<string> *dstVertex = graph->findNode(cityCode);
    double totalFlow = 0;
    double capacity = 0;

    for (Vertex<string> *src: graph->getSrcSet()) { // checks which reservoirs are connected to the city
        graph->connectedReservoirsDfs(src, cityCode, reachableSources);
    }

    for (Vertex<string> *v: graph->getNodeSet()) {
        for (Edge<string> *e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    for (Vertex<string> *src: reachableSources) {
        edmondsKarp(graph, src, dstVertex);
    }

    for (auto e: dstVertex->getIncoming()) {
        totalFlow += e->getFlow();
        capacity += e->getWeight();
    }

    return "The maximum amount of water that can reach the city " + cityCode + " is " + to_string(int (totalFlow)) +
           " m^3/sec. City maximum capacity = " + to_string(int (capacity)) + ".";
}

void Functionality::maxFlowGraph(WaterSupply *graph) {
    unordered_map<string, Reservoir> reservoirs = graph->getReservoirs();
    unordered_map<string, City> cities = graph->getCities();
    vector<Vertex<string> *> dstVertexSet = graph->getDstSet();
    double totalFlow = 0;
    graph->addNode("master_source");
    graph->addNode("master_sink");
    Vertex<string> *source = graph->findNode("master_source");
    Vertex<string> *dest = graph->findNode("master_sink");

    for (Vertex<string> *src: graph->getSrcSet()) {
        Reservoir reservoir = reservoirs[src->getInfo()];
        graph->addPipe("master_source", src->getInfo(), reservoir.getMaxDelivery(), 1);
    }
    for (Vertex<string> *dst: graph->getDstSet()) {
        City city = cities[dst->getInfo()];
        graph->addPipe(dst->getInfo(), "master_sink", city.getDemand(), 1);
    }

    for (Vertex<string> *v: graph->getNodeSet()) {
        for (Edge<string> *e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    edmondsKarp(graph, source, dest);

    for (Vertex<string> *dstVertex: dstVertexSet) {
        City dstCity = cities[dstVertex->getInfo()];
        totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        cout << "With the existing network configuration, the maximum amount of water that can reach the city "
             << dstVertex->getInfo() << " is " << totalFlow
             << " m^3/sec.(water flow in deficit = " << dstCity.getDemand() - totalFlow << ") " << endl;

    }
}