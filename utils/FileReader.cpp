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
                getline(iss, maxDelivery,'\n'))
            {
                Reservoir newReservoir = Reservoir(name,municipality,stoi(id),code,stoi(maxDelivery));
                network.addReservoir(code,newReservoir);
            }
        }
    }

    inputFile.close();
}

void FileReader::addStations(const string &filename, WaterSupply &network)
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
                network.addPS(code,newStation);
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
                getline(iss, population,'\n'))
            {
                City newCity = City(city,stoi(id),code,stod(demand),stoi(population));
                network.addCity(code,newCity);
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
               getline(iss, direction,'\n'))
            {
                network.addPipe(servicePointA,servicePointB, stoi(capacity), stoi(direction));
            }
        }
    }

    inputFile.close();
}