//
// Created by jonas on 27/03/2024.
//

#ifndef DA2324_PRJ1_G11_3_EDMONDS_KARP_H
#define DA2324_PRJ1_G11_3_EDMONDS_KARP_H

#include "WaterSupply.h"

using namespace std;

/* This file contains an adapted Edmonds Karp algorithm for our graph.
 * It also allows for reversing the order of adj and incoming vectors.
 * Time Complexity = O(V*E^2) */

bool findAugmentingPath(WaterSupply &g, Vertex<string> *source, Vertex<string> *target, bool inverse_order) {
    for (Vertex<string> *v: g.getNodeSet()) {
        v->setVisited(false);
    }
    source->setVisited(true);
    std::queue<Vertex<string> *> q;
    q.push(source);
    while (!q.empty()) {
        Vertex<string> *v = q.front();
        q.pop();
        if (inverse_order) v->reverseAdj();
        for (Edge<string> *e: v->getAdj()) {
            Vertex<string> *w = e->getDest();
            if (!w->isVisited() && e->getWeight() > e->getFlow()) {
                q.push(w);
                w->setPath(e);
                w->setVisited(true);
            }
        }
        if (inverse_order) v->reverseIncoming();
        for (Edge<string> *e: v->getIncoming()) {
            Vertex<string> *w = e->getOrig();
            if (!w->isVisited() && e->getFlow() > 0) {
                q.push(w);
                w->setPath(e);
                w->setVisited(true);
            }
        }
    }
    return (target->isVisited());
}

void edmondsKarp(WaterSupply &g, Vertex<string> *s, Vertex<string> *t, bool inverse_order) {
    while (findAugmentingPath(g, s, t, inverse_order)) {
        double minFlow = INF;
        for (Vertex<string> *v = t; v != s;) {
            Edge<string> *e = v->getPath();
            if (e->getDest() == v) {
                minFlow = std::min(e->getWeight() - e->getFlow(), minFlow);
                v = e->getOrig();
            } else {
                minFlow = std::min(e->getFlow(), minFlow);
                v = e->getDest();
            }
        }
        for (Vertex<string> *v = t; v != s;) {
            Edge<string> *e = v->getPath();
            if (e->getDest() == v) {
                e->setFlow(e->getFlow() + minFlow);
                v = e->getOrig();
            } else {
                e->setFlow(e->getFlow() - minFlow);
                v = e->getDest();
            }
        }
    }
}

void edmondsKarp(WaterSupply &g, Vertex<string> *s, Vertex<string> *t) {
    edmondsKarp(g, s, t, false);
}

#endif //DA2324_PRJ1_G11_3_EDMONDS_KARP_H
