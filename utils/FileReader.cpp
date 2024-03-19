#include "FileReader.h"

using namespace std;

template<typename T>
void FileReader::addReservoirs(const string &filename, WaterSupply<T> &OurGraph)
{
    ifstream inputFile(filename);

    if(inputFile.is_open())
    {
        string line;
        getline(inputFile, line);

        while(getline(inputFile,line))
        {
            istringstream iss(line);
            string name, municipality, id, code, maxDelivery;

            if( getline(iss, name,',') &&
                getline(iss, municipality,',') &&
                getline(iss, id,',') &&
                getline(iss, code,',') &&
                getline(iss, maxDelivery,'\n'))
            {
                Reservoir newReservoir = Reservoir(name,municipality,stoi(id),code,stoi(maxDelivery));
                OurGraph.addNode(newReservoir);
            }
        }
    }

    inputFile.close();
}

template<typename T>
void FileReader::addStations(const string &filename, WaterSupply<T> &OurGraph)
{
    ifstream inputFile(filename);

    if(inputFile.is_open())
    {
        string line;
        getline(inputFile, line);

        while(getline(inputFile,line))
        {
            istringstream iss(line);
            string id, code;

            if( getline(iss, id,',') &&
                getline(iss, code,'\n'))
            {
                PumpingStation newStation = PumpingStation(stoi(id),code);
                OurGraph.addNode(newStation);
            }
        }
    }

    inputFile.close();
}

template<typename T>
void FileReader::addCities(const string &filename, WaterSupply<T> &OurGraph)
{
    ifstream inputFile(filename);

    if(inputFile.is_open())
    {
        string line;
        getline(inputFile, line);

        while(getline(inputFile,line))
        {
            istringstream iss(line);
            string city, id, code, demand, population;

            if( getline(iss, city,',') &&
                getline(iss, id,',') &&
                getline(iss, code,',') &&
                getline(iss, demand,',') &&
                getline(iss, population,'\n'))
            {
                City newCity = City(city,stoi(id),code,stoi(demand),stoi(population));
                OurGraph.addNode(newCity);
            }
        }
    }

    inputFile.close();
}

template<typename T>
void FileReader::addPipes(const string &filename, WaterSupply<T> &ourGraph)
{
    ifstream inputFile(filename);

    if(inputFile.is_open())
    {
        string line;
        getline(inputFile, line);

        while(getline(inputFile,line))
        {
            istringstream iss(line);
            string servicePointA, servicePointB, capacity, direction;

            if(getline(iss, servicePointA,',') &&
               getline(iss, servicePointB,',') &&
               getline(iss, capacity,',') &&
               getline(iss, direction,'\n'))
            {
                Vertex<T> source = ourGraph.findNode(servicePointA);
                Vertex<T> target = ourGraph.findNode(servicePointB);
                if (direction == "0"){
                    Pipe newPipe = Pipe(target,source,stoi(capacity),stoi(direction));
                    ourGraph.addPipe(newPipe);
                }
                Pipe newPipe = Pipe(source,target,stoi(capacity),stoi(direction));
                ourGraph.addPipe(newPipe);
            }
        }
    }
}