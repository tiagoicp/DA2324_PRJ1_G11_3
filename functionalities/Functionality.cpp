// Implement the functionalities here

#include <sstream>
#include "Functionality.h"
#include "../classes/edmonds_karp.h"

/* This function checks what could be the maximum flow for the selected city, if each reservoir
 * that can reach it would only try to send water to that city (imagine only the selected city exists, no other). */
string Functionality::maxFlowCity(WaterSupply& graph, string &cityCode) {
    vector<Vertex<string> *> reachableSources;
    Vertex<string> *dstVertex = graph.findNode(cityCode);
    double totalFlow = 0;
    double capacity = 0;
    auto cities = graph.getCities();
    City city = cities[cityCode];

    for (Vertex<string> *src: graph.getSrcSet()) { // checks which reservoirs are connected to the city
        graph.connectedReservoirsDfs(src, cityCode, reachableSources);
    }

    for (Vertex<string> *v: graph.getNodeSet()) {
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

    if (city.getDemand() > totalFlow){
        return "The maximum amount of water that can reach the city " + cityCode + " is " + to_string(int (totalFlow)) +
               " m^3/sec. Maximum incoming capacity = " + to_string(int (capacity)) + ".\nDemand = " + to_string(int (city.getDemand()))
               + ". There is no possible configuration that can meet this city's needs.";
    }

    return "The maximum amount of water that can reach the city " + cityCode + " is " + to_string(int (totalFlow)) +
           " m^3/sec. Maximum incoming capacity = " + to_string(int (capacity)) + ".\nDemand = " + to_string(int (city.getDemand()))
            + ".";
}

/* This function uses a "Master Source" node connected to all Reservoirs and a "Master Sink" that all Cities are connected to,
 * to calculate the maximum flow for the entire graph. */
vector<string> Functionality::maxFlowGraph(WaterSupply& graph) {
    unordered_map<string, Reservoir> reservoirs = graph.getReservoirs();
    unordered_map<string, City> cities = graph.getCities();
    vector<Vertex<string> *> dstVertexSet = graph.getDstSet();

    graph.addNode("master_source");
    graph.addNode("master_sink");
    Vertex<string> *source = graph.findNode("master_source");
    Vertex<string> *dest = graph.findNode("master_sink");

    for (Vertex<string> *src: graph.getSrcSet()) {
        Reservoir reservoir = reservoirs[src->getInfo()];
        graph.addPipe("master_source", src->getInfo(), reservoir.getMaxDelivery(), 1);
    }
    for (Vertex<string> *dst: graph.getDstSet()) {
        City city = cities[dst->getInfo()];
        graph.addPipe(dst->getInfo(), "master_sink", city.getDemand(), 1);
    }

    graph.resetGraphFlow();

    edmondsKarp(graph, source, dest);
    vector<string> resultVector;
    resultVector.push_back("With the network configured to output the maximum flow:");

    double totalFlow;
    for (Vertex<string> *dstVertex: dstVertexSet) {
        City dstCity = cities[dstVertex->getInfo()];
        totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        if (totalFlow == dstCity.getDemand()) resultVector.push_back("The city " + dstVertex->getInfo()
        + " is supplied with the desired water rate level of " + to_string(int(totalFlow)) + " m^3/sec." );
        else resultVector.push_back("The city "
             + dstVertex->getInfo() + " is supplied with only " + to_string(int(totalFlow))
             + " m^3/sec, resulting in a water flow deficit of " + to_string(int(dstCity.getDemand() - totalFlow)) + " m^3/sec.");
    }


    graph.removeNode("master_source");
    graph.removeNode("master_sink");


    return resultVector;
}

void Functionality::maxFlowGraphBalanced(WaterSupply& graph) {
    maxFlowGraph(graph);
    double avg;
    vector<double> ratios;
    for (Vertex<string>* v : graph.getNodeSet()){
        for (Edge<string>* e : v->getAdj()){
            ratios.push_back(e->getFlow()/e->getWeight());
        }
    }
    double sum = 0;
    for(double d : ratios){
        sum+= d;
    }
    avg = sum/ratios.size();
    for (Vertex<string>* v : graph.getSrcSet()){
        for(Edge<string>* e : v->getAdj()){
            if ((e->getFlow()/ e->getWeight()) > avg) {
                e->setWeight(e->getWeight() * 0.9); // decrease to 90%
            }
        }
    }

    maxFlowGraph(graph);
}

/* This function uses the previous maxFlowGraph to calculate and memorize each city's incoming flow,
 * removes the selected reservoir from the graph(actually sets the capacity of the reservoir's outgoing
 * edges to 0), recalculates the maximum flow of the new graph and then compares each city's new
 * incoming flow value to the old one. */
void Functionality::removeReservoirAndListAffectedCities(WaterSupply& graph, const string& reservoirCode) {
    WaterSupply newGraph = graph;
    maxFlowGraph(newGraph);
    vector<Vertex<string>*> dstVertexSet = newGraph.getDstSet();
    Vertex<string>* reservoir = newGraph.findNode(reservoirCode);

    for (Vertex<string> *dstVertex : dstVertexSet) {
        double totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        dstVertex->setIncFlow(totalFlow);
    }

    newGraph.resetGraphFlow();

    for (Edge<string>* e : reservoir->getAdj()){
        e->setWeight(0);
    }

    cout << "By removing the reservoir " << reservoirCode << " the following cities are affected: " << endl;

    maxFlowGraph(newGraph);
    for (Vertex<string> *dstVertex : dstVertexSet) {
        double totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        if (totalFlow != dstVertex->getIncFlow()){
            double difference = dstVertex->getIncFlow() - totalFlow;
            cout << dstVertex->getInfo() << ": Lost " << difference << " units of water!" << endl;
        }
    }

}

/* This function uses the previous maxFlowGraph to calculate and memorize the total sink flow as well as
 * each city's incoming flow, then for each Pumping Station sets its outgoing edges to 0 capacity, recalculates
 * maximum flow and, if the total sink flow is different, checks which cities got affected. Note that, while the
 * overall flow is smaller, some cities get increased flow because of the rearrangement of the graph. */
void Functionality::checkUselessPumpingStations(WaterSupply &graph) {
    WaterSupply newGraph = graph;
    maxFlowGraph(newGraph);
    double totalSinkFlow = newGraph.getTotalSinkFlow();
    vector<Vertex<string>*> dstVertexSet = newGraph.getDstSet();
    vector<Vertex<string>*> psVertexSet = newGraph.getPSSet();

    for (Vertex<string> *dstVertex : dstVertexSet) {
        newGraph.getCityFlow(dstVertex);
    }

    newGraph.resetGraphFlow();

    for (Vertex<string>* ps : psVertexSet){
        for (Edge<string>* e : ps->getAdj()){
            e->setTempWeight(e->getWeight());
            e->setWeight(0);
        }

        maxFlowGraph(newGraph);

        if (newGraph.getTotalSinkFlow() != totalSinkFlow) {
            cout << "By removing the pumping station " << ps->getInfo() << " the following cities are affected:" << endl;

            for (Vertex<string> *dstVertex: dstVertexSet) {
                double totalFlow = 0;
                for (auto e: dstVertex->getIncoming()) {
                    totalFlow += e->getFlow();
                }
                if (totalFlow != dstVertex->getIncFlow()) {
                    double difference = dstVertex->getIncFlow() - totalFlow;
                    if (difference < 0){
                        double gain = -difference;
                        cout << dstVertex->getInfo() << ": Gained " << gain << " units of water!" << endl;
                    }
                    else cout << dstVertex->getInfo() << ": Lost " << difference << " units of water!" << endl;
                }
            }
        }
        else{
            cout << "The pumping station " << ps->getInfo() << " can be safely removed without affecting any city!" << endl;
        }
        cout << endl;
        for (Edge<string> *e: ps->getAdj()) {
            e->setWeight(e->getTempWeight());
            e->setTempWeight(0);
        }
    }
}

/* similarly to the previous two functions, this one calculates maxFlowGraph, then, for each edge of the graph,
 * sets its capacity to 0, recalculates max flow and checks which cities got affected. */
void Functionality::checkCriticalPipes(WaterSupply &graph) {
    WaterSupply newGraph = graph;
    maxFlowGraph(newGraph);
    vector<Vertex<string>*> dstVertexSet = newGraph.getDstSet();

    for (Vertex<string> *dstVertex : dstVertexSet) {
        newGraph.getCityFlow(dstVertex);
    }

    for (Vertex<string>* v : newGraph.getNodeSet()){
        for (Edge<string>* e : v->getAdj()){
            cout << "By removing the pipe that connects " << e->getOrig()->getInfo() << " to " << e->getDest()->getInfo() << endl;
            bool isCritical = false;
            e->setTempWeight(e->getWeight());
            e->setWeight(0);

            maxFlowGraph(newGraph);

            for (Vertex<string> *dstVertex: dstVertexSet) {
                double currentFlow = 0;
                double cityFlow = dstVertex->getIncFlow();
                for (auto cityEdge: dstVertex->getIncoming()) {
                    currentFlow += cityEdge->getFlow();
                }

                if (currentFlow != cityFlow) {
                    isCritical = true;
                    double difference = cityFlow - currentFlow;
                    if (difference < 0){
                        double gain = -difference;
                        cout << dstVertex->getInfo() << ": Gained " << gain << " units of water!" << endl;
                    }
                    else cout << dstVertex->getInfo() << ": Lost " << difference << " units of water!" << endl;
                }
            }
            if (!isCritical) cout << "No city gets affected!" << endl;
            cout << endl;
            e->setWeight(e->getTempWeight());
            e->setTempWeight(0);
        }
    }
}


