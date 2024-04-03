//
// Created by jonas on 27/03/2024.
//

#ifndef DA2324_PRJ1_G11_3_EDMONDS_KARP_H
#define DA2324_PRJ1_G11_3_EDMONDS_KARP_H

#include "WaterSupply.h"
using namespace std;

// This file contains an adapted Edmonds Karp algorithm for our graph.

bool findAugmentingPath(WaterSupply& g, Vertex<string>* source, Vertex<string>* target){
    for (Vertex<string>* v : g.getNodeSet()) {
        v->setVisited(false);
    }
    source->setVisited(true);
    std::queue<Vertex<string>*> q;
    q.push(source);
    while(!q.empty()){
        Vertex<string>* v = q.front();
        q.pop();
        for (Edge<string>* e : v->getAdj()){
            Vertex<string>* w = e->getDest();
            if (!w->isVisited() && e->getWeight() > e->getFlow()){
                q.push(w);
                w->setPath(e);
                w->setVisited(true);
            }
        }
        for (Edge<string>* e : v->getIncoming()){
            Vertex<string>* w = e->getOrig();
            if (!w->isVisited() && e->getFlow() > 0){
                q.push(w);
                w->setPath(e);
                w->setVisited(true);
            }
        }
    }
    return (target->isVisited());
}

void edmondsKarp(WaterSupply& g, Vertex<string>* s, Vertex<string>* t) {
    while(findAugmentingPath(g,s,t)){
        double minFlow = INF;
        for (Vertex<string>* v = t; v!=s;){
            Edge<string>* e = v->getPath();
            if (e->getDest() == v){
                minFlow = std::min(e->getWeight()-e->getFlow(),minFlow);
                v = e->getOrig();
            }
            else{
                minFlow = std::min(e->getFlow(),minFlow);
                v = e->getDest();
            }
        }
        for (Vertex<string>* v = t; v!=s;){
            Edge<string>* e = v->getPath();
            if (e->getDest() == v){
                e->setFlow(e->getFlow()+minFlow);
                v = e->getOrig();
            }
            else{
                e->setFlow(e->getFlow()-minFlow);
                v = e->getDest();
            }
        }
    }
}

#endif //DA2324_PRJ1_G11_3_EDMONDS_KARP_H
