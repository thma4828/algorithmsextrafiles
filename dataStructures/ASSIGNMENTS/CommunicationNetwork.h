#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H
#include <iostream>

using namespace std;
struct City{
    string cityName;
    string message;
    City *next;
    City *previous;

    City(){}; // default constructor

    City(string initName, City *initNext, string initMessage)
    {
        cityName = initName;
        next = initNext;
        message = initMessage;
    }

};

class CommunicationNetwork
{
    public:
        CommunicationNetwork(bool, int);
        ~CommunicationNetwork(){
            clearNetwork();
        }
        void addCity(string, string);
        void buildNetwork();
        void transmitMsg(char *); //this is like a string
        void printNetwork();
        void deleteCity(string);
        void clearNetwork();
    protected:
    private:
        bool isBuilt;
        City *head;
        City *tail;
        int CityCount;
};

#endif // COMMUNICATIONNETWORK_H
