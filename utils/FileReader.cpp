#include "FileReader.h"

using namespace std;
template <class T>
void FileReader::addReservoirs(const string &filename, WaterSupply<T> &ourGraph)
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
                Reservoir<T> newReservoir = Reservoir<T>(name,municipality,stoi(id),code,stoi(maxDelivery));
                ourGraph.addNode(newReservoir);
            }
        }
    }

    inputFile.close();
}

template<typename T>
void FileReader::addStations(const string &filename, WaterSupply<T> &ourGraph)
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
                PumpingStation<T> newStation = PumpingStation<T>(stoi(id),code);
                ourGraph.addNode(newStation);
            }
        }
    }

    inputFile.close();
}

template <class T>
void FileReader::addCities(const string &filename, WaterSupply<T> &ourGraph)
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
                City<T> newCity = City<T>(city,stoi(id),code,stoi(demand),stoi(population));
                ourGraph.addNode(newCity);
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
                    Pipe<T> newPipe = Pipe<T>(target,source,stoi(capacity),stoi(direction));
                    ourGraph.addPipe(newPipe);
                }
                Pipe<T> newPipe = Pipe<T>(source,target,stoi(capacity),stoi(direction));
                ourGraph.addPipe(newPipe);
            }
        }
    }
}