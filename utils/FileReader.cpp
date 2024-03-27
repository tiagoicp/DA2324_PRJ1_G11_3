#include "FileReader.h"

using namespace std;
void FileReader::addReservoirs(const string &filename, WaterSupply &network)
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
                getline(iss, maxDelivery,'\r'))
            {
                Reservoir newReservoir = Reservoir(name,municipality,stoi(id),code,stoi(maxDelivery));
                network.addReservoir(code,newReservoir);
                network.addSrc(network.findNode(code));
            }
        }
    }

    inputFile.close();
}

void FileReader::addPumpingStations(const string &filename, WaterSupply &network)
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
                getline(iss, code,'\r'))
            {
                PumpingStation newStation = PumpingStation(stoi(id),code);
                network.addPumpingStation(code,newStation);
            }
        }
    }

    inputFile.close();
}

void FileReader::addCities(const string &filename, WaterSupply &network)
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
                getline(iss, population,'\r'))
            {
                City newCity = City(city,stoi(id),code,stod(demand),stoi(population));
                network.addCity(code,newCity);
                network.addDst(network.findNode(code));
            }
        }
    }

    inputFile.close();
}

void FileReader::addPipes(const string &filename, WaterSupply &network)
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
               getline(iss, direction,'\r'))
            {
                network.addPipe(servicePointA,servicePointB, stoi(capacity), stoi(direction));
            }
        }
    }

    inputFile.close();
}