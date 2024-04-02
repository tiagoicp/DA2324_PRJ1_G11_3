// Implement the functionalities here

#include <sstream>
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

vector<string> Functionality::maxFlowGraph(WaterSupply *graph) {
    unordered_map<string, Reservoir> reservoirs = graph->getReservoirs();
    unordered_map<string, City> cities = graph->getCities();
    vector<Vertex<string> *> dstVertexSet = graph->getDstSet();

    if(graph->findNode("master_source")){
        graph->removeNode("master_source");
        graph->removeNode("master_sink");
    }
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
    vector<string> resultVector;
    resultVector.push_back("With the existing network configuration:");
    double totalFlow;
    for (Vertex<string> *dstVertex: dstVertexSet) {
        City dstCity = cities[dstVertex->getInfo()];
        totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        resultVector.push_back("The maximum amount of water that can reach the city "
             + dstVertex->getInfo() + " is " + to_string(int(totalFlow))
             + " m^3/sec. (water flow in deficit = " + to_string(int(dstCity.getDemand() - totalFlow)) + ")");
    }

    return resultVector;
}

void Functionality::maxFlowGraphBalanced(WaterSupply *graph) {
    maxFlowGraph(graph);
    double avg;
    vector<double> ratios;
    double sum = 0;
    for (Vertex<string>* v : graph->getNodeSet()){
        for (Edge<string>* e : v->getAdj()){
            ratios.push_back(e->getFlow()/e->getWeight());
        }
    }
    for(double d : ratios){
        sum+= d;
    }
    avg = sum/ratios.size();
    for (Vertex<string>* v : graph->getSrcSet()){
        for(Edge<string>* e : v->getAdj()){
            if ((e->getFlow()/ e->getWeight()) > avg) {
                e->setFlow(e->getWeight()*avg);
                e->setWeight(e->getWeight() * avg);
            }
        }
    }
    maxFlowGraph(graph);

}
