#include <iostream>
#include "WaterSupply.h"

using namespace std;

void WaterSupply::addReservoir(Reservoir& reservoir)
{
    addVertex(reservoir);
}
void WaterSupply::removeReservoir(const Reservoir& reservoir)
{
    removeVertex(reservoir);
}

void WaterSupply::addPumpingStation(PumpingStation& station)
{
    addVertex(station);
}

void WaterSupply::removePumpingStation(PumpingStation& station)
{
    removeVertex(station);
}

void WaterSupply::addCity(City& city)
{
    addVertex(city);
}

void WaterSupply::removeCity(City& city)
{
    removeVertex(city);
}

void WaterSupply::addPipe(Pipe& pipe)
{
    addEdge(pipe.getSource(), pipe.getTarget(), pipe);
}

void WaterSupply::removePipe(Pipe& pipe)
{
    removeEdge(pipe.getSource(), pipe.getTarget());
}