#include <iostream>
#include "WaterSupply.h"

using namespace std;

template <class T>
void WaterSupply<T>::addNode(Vertex<T>& node)
{
    addVertex(node);
}

template <class T>
void WaterSupply<T>::removeNode(const Vertex<T>& node)
{
    removeVertex(node);
}

template <class T>
void WaterSupply<T>::addPipe(Edge<T>& pipe)
{
    addEdge(pipe.getOrigin(), pipe.getDest(), pipe);
}

template <class T>
void WaterSupply<T>::removePipe(Edge<T>& pipe)
{
    removeEdge(pipe.getOrigin(), pipe.getDest());
}

template <class T>
Vertex<T> WaterSupply<T>::findNode(const T &in) const{
    return findVertex(in);
}