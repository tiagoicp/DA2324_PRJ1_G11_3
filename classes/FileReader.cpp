#include "FileReader.h"

using namespace std;

void FileReader::addReservoirs(const string &filename, WaterSupply &OurGraph)
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
                OurGraph.addReservoir(newReservoir);
            }
        }
    }

    inputFile.close();
}

void FileReader::addStations(const string &filename, WaterSupply &OurGraph)
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
                OurGraph.addPumpingStation(newStation);
            }
        }
    }

    inputFile.close();
}

void FileReader::addCities(const string &filename, WaterSupply &OurGraph)
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
                OurGraph.addCity(newCity);
            }
        }
    }

    inputFile.close();
}

void FileReader::addPipes(const string &filename, WaterSupply &ourGraph)
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
                Node source = ourGraph.findNode(servicePointA);
                Node target = ourGraph.findNode(servicePointB);

                Pipe newPipe = Pipe(source,target,stoi(capacity),stoi(direction));
                ourGraph.addPipe(newPipe);
            }
        }
    }
}