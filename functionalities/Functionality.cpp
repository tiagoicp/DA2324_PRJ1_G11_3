// Implement the functionalities here

#include <sstream>
#include "Functionality.h"
#include "../classes/edmonds_karp.h"

/**
 * This function checks what could be the maximum flow for the selected city, if each reservoir
 * that can reach it would only try to send water to that city (imagine only the selected city exists, no other).
 *
 * Time Complexity = O(S*(V*E^2)) S= Number of Sources(Reservoirs).
 */
string Functionality::maxFlowCity(WaterSupply &graph, string &cityCode) {
    vector<Vertex<string> *> reachableSources;
    Vertex<string> *dstVertex = graph.findNode(cityCode);
    double totalFlow = 0;
    double capacity = 0;
    auto cities = graph.getCities();
    City city = cities[cityCode];

    for (Vertex<string> *src: graph.getSrcSet()) { // checks which reservoirs are connected to the city. O(S*(V+E))
        graph.connectedReservoirsDfs(src, cityCode, reachableSources);
    }

    for (Vertex<string> *v: graph.getNodeSet()) {       // O(E)
        for (Edge<string> *e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    for (Vertex<string> *src: reachableSources) {       // O(S*(V*E^2)) S= Number of Sources(Reservoirs).
        edmondsKarp(graph, src, dstVertex);
    }

    for (auto e: dstVertex->getIncoming()) {
        totalFlow += e->getFlow();
        capacity += e->getWeight();
    }

    if (city.getDemand() > totalFlow) {
        return "The maximum amount of water that can reach the city " + cityCode + " is " + to_string(int(totalFlow)) +
               " m^3/sec. Maximum incoming capacity = " + to_string(int(capacity)) + ".\nDemand = " +
               to_string(int(city.getDemand()))
               + ". There is no possible configuration that can meet this city's needs.";
    }

    return "The maximum amount of water that can reach the city " + cityCode + " is " + to_string(int(totalFlow)) +
           " m^3/sec. Maximum incoming capacity = " + to_string(int(capacity)) + ".\nDemand = " +
           to_string(int(city.getDemand()))
           + ".";
}

/**
 * This function uses a "Master Source" node connected to all Reservoirs and a "Master Sink" that all Cities are connected to,
 * to calculate the maximum flow for the entire graph.
 *
 * Time Complexity = O(V*E^2) (We run EdmondsKarp only once) */
vector<string> Functionality::maxFlowGraph(WaterSupply &graph, bool inverseOrder) {
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

    edmondsKarp(graph, source, dest, inverseOrder);
    vector<string> resultVector;
    resultVector.push_back("With the network configured to output the maximum flow:");

    double totalFlow;
    for (Vertex<string> *dstVertex: dstVertexSet) {
        City dstCity = cities[dstVertex->getInfo()];
        totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        if (totalFlow == dstCity.getDemand())
            resultVector.push_back("The city " + dstVertex->getInfo()
                                   + " is supplied with the desired water rate level of " + to_string(int(totalFlow)) +
                                   " m^3/sec.");
        else
            resultVector.push_back("The city "
                                   + dstVertex->getInfo() + " is supplied with only " + to_string(int(totalFlow))
                                   + " m^3/sec, resulting in a water flow deficit of " +
                                   to_string(int(dstCity.getDemand() - totalFlow)) + " m^3/sec.");
    }

    graph.removeNode("master_source");
    graph.removeNode("master_sink");

    return resultVector;
}

vector<string> Functionality::maxFlowGraph(WaterSupply &graph) {
    return maxFlowGraph(graph, false);
}

void rejectChildFlowChanges(Vertex<string> *node, double maxAmount) {
    auto pipes = node->getAdj();
    vector<Edge<string> *> pipesWithDiffs;
    for (auto pipe: pipes) {
        if (pipe->getFlow() - pipe->getPreviousFlow() != 0) pipesWithDiffs.push_back(pipe);
    }
    if (pipesWithDiffs.empty()) return;
    if (pipesWithDiffs.size() > 1) {
        pipesWithDiffs.pop_back(); // improve branch selection
    }

    auto pipe = pipesWithDiffs[0];
    auto diff = pipe->getFlow() - pipe->getPreviousFlow();
    cout << "REJECTED CHILD change from " << pipe->getOrig()->getInfo() << " to " << pipe->getDest()->getInfo()
         << " by ";

    if(abs(diff) > abs(maxAmount)){
        pipe->setFlow(pipe->getFlow() - maxAmount);
        cout << maxAmount << endl;
    }
    else {
        cout << pipe->getFlow() - pipe->getPreviousFlow() << endl;
        pipe->setFlow(pipe->getPreviousFlow());
    }

    rejectChildFlowChanges(pipe->getDest(), maxAmount);
}

/**
 * This function generates two alternatives and then attempts to reconcile their differences,
 * trying to pick the best alternative from each "splitting node" and rejecting the worst
 *
 * Time Complexity = O(V*E^2)
 * We need to run EdmondsKarp twice, then do several linear operations */
void Functionality::balanceMaxFlowGraph(WaterSupply &graph) {
    // run normal order / strategy
    maxFlowGraph(graph, false);

    // write previousFlow
    vector<Vertex<string> *> nodes = graph.getNodeSet();
    for (Vertex<string> *node: nodes) {
        vector<Edge<string> *> pipes = node->getAdj();
        for (auto pipe: pipes) {
            pipe->setPreviousFlow(pipe->getFlow());
        }
    }

    // run inverse order / strategy
    maxFlowGraph(graph, true);

    // discover alternate sources
    // Key: common dest, Value: path)
    unordered_map<string, vector<Edge<string> *>> diff_sources;

    // first from diff sources/reservoirs
    nodes = graph.getSrcSet();
    for (Vertex<string> *node: nodes) {
        vector<Edge<string> *> pipes = node->getAdj();
        for (auto pipe: pipes) {
            if (pipe->getFlow() == pipe->getPreviousFlow()) continue;

            // add to diff_sources
            string key = pipe->getDest()->getInfo();
            diff_sources[key].push_back(pipe);
        }
    }

    // will be used on next part
    unordered_map<string, vector<Edge<string> *>> diff_paths;

    // accept or reject alternative sources
    for (const auto &diff_pair: diff_sources) {
        // handle "splitting reservoirs" in next part
        if(diff_pair.second.size() == 1) {
            auto pipe = diff_pair.second[0];
            string key = pipe->getOrig()->getInfo();
            diff_paths[key].push_back(pipe);
            continue;
        }

        auto pipe1 = diff_pair.second[0];
        auto pipe2 = diff_pair.second[1];

        if (abs(pipe1->getFlow() - pipe2->getFlow()) > abs(pipe1->getPreviousFlow() - pipe2->getPreviousFlow())) {
            cout << "REJECTED change from " << pipe1->getOrig()->getInfo() << " to " << pipe1->getDest()->getInfo()
                 << " by " << pipe1->getFlow() - pipe1->getPreviousFlow() << endl;
            cout << "REJECTED change from " << pipe2->getOrig()->getInfo() << " to " << pipe2->getDest()->getInfo()
                 << " by " << pipe2->getFlow() - pipe2->getPreviousFlow() << endl;

            // alternate is rejected
            pipe1->setFlow(pipe1->getPreviousFlow());
            pipe2->setFlow(pipe2->getPreviousFlow());
        } else {
            cout << "Balanced pipe from " << pipe1->getOrig()->getInfo() << " to " << pipe1->getDest()->getInfo()
                 << " by " << pipe1->getFlow() - pipe1->getPreviousFlow() << endl;
            cout << "Balanced pipe from " << pipe2->getOrig()->getInfo() << " to " << pipe2->getDest()->getInfo()
                 << " by " << pipe2->getFlow() - pipe2->getPreviousFlow() << endl;
        }
    }

    // then discover alternative paths
    // by splitting nodes (pumping stations)
    nodes = graph.getPSSet();
    for (Vertex<string> *node: nodes) {
        vector<Edge<string> *> pipes = node->getAdj();
        for (auto pipe: pipes) {
            if (pipe->getFlow() == pipe->getPreviousFlow()) continue;

            // add to diff_sources
            string key = pipe->getOrig()->getInfo();
            diff_paths[key].push_back(pipe);
        }
    }

    // accept or reject alternative paths
    for (Vertex<string> *node: nodes) {
        // on original order
        auto search = diff_paths.find(node->getInfo());
        if(search == diff_paths.end()) continue;

        auto diff_pair = *search;
        if (diff_pair.second.size() < 2) continue;
        if (diff_pair.second.size() > 2) throw std::invalid_argument("Unexpected case of more than 2 alternate paths");

        auto pipe1 = diff_pair.second[0];
        auto pipe2 = diff_pair.second[1];

        if (abs(pipe1->getFlow() - pipe2->getFlow()) > abs(pipe1->getPreviousFlow() - pipe2->getPreviousFlow())) {
            cout << "REJECTED change from " << pipe1->getOrig()->getInfo() << " to " << pipe1->getDest()->getInfo()
                 << " by " << pipe1->getFlow() - pipe1->getPreviousFlow() << endl;
            cout << "REJECTED change from " << pipe2->getOrig()->getInfo() << " to " << pipe2->getDest()->getInfo()
                 << " by " << pipe2->getFlow() - pipe2->getPreviousFlow() << endl;

            double diff1 = pipe1->getFlow() - pipe1->getPreviousFlow();
            double diff2 = pipe2->getFlow() - pipe2->getPreviousFlow();

            // alternate is rejected
            pipe1->setFlow(pipe1->getPreviousFlow());
            pipe2->setFlow(pipe2->getPreviousFlow());

            // also reject all child diffs
            rejectChildFlowChanges(pipe1->getDest(), diff1);
            rejectChildFlowChanges(pipe2->getDest(), diff2);
        } else {
            cout << "Balanced pipe from " << pipe1->getOrig()->getInfo() << " to " << pipe1->getDest()->getInfo()
                 << " by " << pipe1->getFlow() - pipe1->getPreviousFlow() << endl;
            cout << "Balanced pipe from " << pipe2->getOrig()->getInfo() << " to " << pipe2->getDest()->getInfo()
                 << " by " << pipe2->getFlow() - pipe2->getPreviousFlow() << endl;
        }
    }

    // compensate any missing rejections
    for(auto node : graph.getNodeSet()){
        if(node->getIncoming().empty()) continue;

        double incomingFlow = 0;
        for(auto pipe : node->getIncoming()){
            incomingFlow += pipe->getFlow();
        }

        double adjFlow = 0;
        for(auto pipe : node->getAdj()){
            adjFlow += pipe->getFlow();
        }

        if(adjFlow > incomingFlow) {
            for(auto pipe : node->getIncoming()){
                if(pipe->getFlow() == pipe->getPreviousFlow()) continue;

                // reject change
                double diff =  pipe->getFlow() - pipe->getPreviousFlow();
                cout << "REJECTED change (compensated) from " << pipe->getOrig()->getInfo() << " to " << pipe->getDest()->getInfo()
                     << " by " << diff << endl;
                pipe->setFlow(pipe->getPreviousFlow());
                rejectChildFlowChanges(pipe->getOrig(), diff);
            }
        }
    }

    // then finally print balances on body of alternate path
    for (const auto &diff_pair: diff_paths) {
        if (diff_pair.second.size() != 1) continue;

        auto pipe = diff_pair.second[0];
        if (pipe->getFlow() == pipe->getPreviousFlow()) continue; // if it was corrected by rejectChildFlowChanges

        cout << "Balanced child pipe from " << pipe->getOrig()->getInfo() << " to " << pipe->getDest()->getInfo()
             << " by " << pipe->getFlow() - pipe->getPreviousFlow() << endl;
    }

    cout << endl;
}

/**
 * This function uses the previous maxFlowGraph to calculate and memorize each city's incoming flow,
 * removes the selected reservoir from the graph(actually sets the capacity of the reservoir's outgoing
 * edges to 0), recalculates the maximum flow of the new graph and then compares each city's new
 * incoming flow value to the old one.
 *
 * Time Complexity = O(V*E^2) (We run EdmondsKarp twice) */
void Functionality::removeReservoirAndListAffectedCities(WaterSupply &graph, const string &reservoirCode) {
    WaterSupply newGraph = graph;
    maxFlowGraph(newGraph);
    vector<Vertex<string> *> dstVertexSet = newGraph.getDstSet();
    Vertex<string> *reservoir = newGraph.findNode(reservoirCode);

    for (Vertex<string> *dstVertex: dstVertexSet) {
        double totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        dstVertex->setIncFlow(totalFlow);
    }

    newGraph.resetGraphFlow();

    for (Edge<string> *e: reservoir->getAdj()) {
        e->setWeight(0);
    }

    cout << "By removing the reservoir " << reservoirCode << " the following cities are affected: " << endl;

    maxFlowGraph(newGraph);
    for (Vertex<string> *dstVertex: dstVertexSet) {
        double totalFlow = 0;
        for (auto e: dstVertex->getIncoming()) {
            totalFlow += e->getFlow();
        }
        if (totalFlow != dstVertex->getIncFlow()) {
            double difference = dstVertex->getIncFlow() - totalFlow;
            cout << dstVertex->getInfo() << ": Lost " << difference << " units of water!" << endl;
        }
    }

}

/**
 * This function uses the previous maxFlowGraph to calculate and memorize the total sink flow as well as
 * each city's incoming flow, then for each Pumping Station sets its outgoing edges to 0 capacity, recalculates
 * maximum flow and, if the total sink flow is different, checks which cities got affected. Note that, while the
 * overall flow is smaller, some cities get increased flow because of the rearrangement of the graph.
 *
 * Time Complexity = O(P*(V*E^2)) P = Number of Pumping Stations (We run EdmondsKarp for each PS). */
void Functionality::checkUselessPumpingStations(WaterSupply &graph) {
    WaterSupply newGraph = graph;
    maxFlowGraph(newGraph);
    double totalSinkFlow = newGraph.getTotalSinkFlow();
    vector<Vertex<string> *> dstVertexSet = newGraph.getDstSet();
    vector<Vertex<string> *> psVertexSet = newGraph.getPSSet();

    for (Vertex<string> *dstVertex: dstVertexSet) {
        newGraph.getCityFlow(dstVertex);
    }

    newGraph.resetGraphFlow();

    for (Vertex<string> *ps: psVertexSet) {
        for (Edge<string> *e: ps->getAdj()) {
            e->setTempWeight(e->getWeight());
            e->setWeight(0);
        }

        maxFlowGraph(newGraph);

        if (newGraph.getTotalSinkFlow() != totalSinkFlow) {
            cout << "By removing the pumping station " << ps->getInfo() << " the following cities are affected:"
                 << endl;

            for (Vertex<string> *dstVertex: dstVertexSet) {
                double totalFlow = 0;
                for (auto e: dstVertex->getIncoming()) {
                    totalFlow += e->getFlow();
                }
                if (totalFlow != dstVertex->getIncFlow()) {
                    double difference = dstVertex->getIncFlow() - totalFlow;
                    if (difference < 0) {
                        double gain = -difference;
                        cout << dstVertex->getInfo() << ": Gained " << gain << " units of water!" << endl;
                    } else cout << dstVertex->getInfo() << ": Lost " << difference << " units of water!" << endl;
                }
            }
        } else {
            cout << "The pumping station " << ps->getInfo() << " can be safely removed without affecting any city!"
                 << endl;
        }
        cout << endl;
        for (Edge<string> *e: ps->getAdj()) {
            e->setWeight(e->getTempWeight());
            e->setTempWeight(0);
        }
    }
}

/**
 * Similarly to the previous two functions, this one calculates maxFlowGraph, then, for each edge of the graph,
 * sets its capacity to 0, recalculates max flow and checks which cities got affected.
 *
 * Time Complexity = O(V*E^3) (We run EdmondsKarp for each edge of the graph) */
void Functionality::checkCriticalPipes(WaterSupply &graph) {
    WaterSupply newGraph = graph;
    maxFlowGraph(newGraph);
    vector<Vertex<string> *> dstVertexSet = newGraph.getDstSet();

    for (Vertex<string> *dstVertex: dstVertexSet) {
        newGraph.getCityFlow(dstVertex);
    }

    for (Vertex<string> *v: newGraph.getNodeSet()) {
        for (Edge<string> *e: v->getAdj()) {
            cout << "By removing the pipe that connects " << e->getOrig()->getInfo() << " to "
                 << e->getDest()->getInfo() << endl;
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
                    if (difference < 0) {
                        double gain = -difference;
                        cout << dstVertex->getInfo() << ": Gained " << gain << " units of water!" << endl;
                    } else cout << dstVertex->getInfo() << ": Lost " << difference << " units of water!" << endl;
                }
            }
            if (!isCritical) cout << "No city gets affected!" << endl;
            cout << endl;
            e->setWeight(e->getTempWeight());
            e->setTempWeight(0);
        }
    }
}


