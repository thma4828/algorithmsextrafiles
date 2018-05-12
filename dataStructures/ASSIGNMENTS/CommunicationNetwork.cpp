#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include "CommunicationNetwork.h"
#include <sstream>
#include <cstring>

using namespace std;

void CommunicationNetwork::transmitMsg(char *theMsg){
    if(head == NULL){
        cout << "Empty List" << endl;
    }
    if(head != NULL){
        string msg1 = string(theMsg);
        vector<string> splitStr;
        istringstream iss(msg1);
        for(msg1; iss >> msg1;){
            splitStr.push_back(msg1);
        }
        City *CurrentCity = new City();
        CurrentCity = head;
        CurrentCity = CurrentCity->next;
        for(int i=0; i<splitStr.size(); i++){
            while(CurrentCity != NULL){
                CurrentCity->message = splitStr.at(i);
                cout << CurrentCity->cityName << " received " << splitStr.at(i) << endl;
                CurrentCity = CurrentCity->next;
            }
            if(CurrentCity == NULL){
                CurrentCity = head;
            }
        }
        CurrentCity = tail;
        for(int z=0; z<splitStr.size(); z++){
            while(CurrentCity->previous != NULL){
                CurrentCity = CurrentCity->previous;
                CurrentCity->message = splitStr.at(z);
                cout << CurrentCity->cityName << " received " << splitStr.at(z) << endl;
            }
            if(CurrentCity->previous == NULL){
                CurrentCity = tail;
            }
        }
    }
}

void CommunicationNetwork::addCity(string Name, string cityPrevious){
    City *theCity = new City();
    City *newCity = new City(Name, NULL, "");
    theCity = head;
    bool foundPrev = false;
    if(cityPrevious != "First"){
        while(theCity != NULL){
            if(theCity->cityName == cityPrevious){
                foundPrev = true;
                newCity->next = theCity->next;
                newCity->previous = theCity->previous;
                theCity->next = newCity;
            }
            theCity = theCity->next;
        }
    }
    else if(cityPrevious == "First"){
        newCity->next = head;
        head = newCity;
        foundPrev = true;
    }
    if(tail->cityName == cityPrevious){
        tail = newCity;
        foundPrev = true;
    }
    if(foundPrev){
        CityCount++;
    }
}

void CommunicationNetwork::deleteCity(string name){
    City *temp = new City();
    City *left = new City();
    bool found = false;
    if(head->cityName == name){
        found = true;
        temp = head;
        head = head->next;
        temp = NULL;
    }else{
        left = head;
        temp = head->next;
    }
    while(temp !=NULL && !found){
        if(temp->cityName == name){
            left->next = temp->next;
            if(temp == tail){
                tail = left;
            }
            temp = NULL;
            found = true;
        }else{
            left = temp;
            temp = temp->next;
        }
    }
    if(found){
        CityCount--;
    }else if(!found){
        cout << name << " not found" << endl;
    }
}

void CommunicationNetwork::buildNetwork(){
    City *LosAngeles = new City("Los Angeles", NULL, "");
    City *Phoenix = new City("Phoenix", NULL, "");
    City *Denver = new City("Denver", NULL, "");
    City *Dallas = new City("Dallas", NULL, "");
    City *StLouis = new City("St. Louis", NULL, "");
    City *Chicago = new City("Chicago", NULL, "");
    City *Atlanta = new City("Atlanta", NULL, "");
    City *WashingtonDC = new City("Washington, D.C.", NULL, "");
    City *NewYork = new City("New York", NULL, "");
    City *Boston = new City("Boston", NULL, "");

    LosAngeles->next = Phoenix;
    Phoenix->next = Denver;
    Denver->next = Dallas;
    Dallas->next = StLouis;
    StLouis->next = Chicago;
    Chicago->next = Atlanta;
    Atlanta->next = WashingtonDC;
    WashingtonDC->next = NewYork;
    NewYork->next = Boston;
    Boston->next = NULL;

    Boston->previous = NewYork;
    NewYork->previous = WashingtonDC;
    WashingtonDC->previous = Atlanta;
    Atlanta->previous = Chicago;
    Chicago->previous = StLouis;
    StLouis->previous = Dallas;
    Dallas->previous = Denver;
    Denver->previous = Phoenix;
    Phoenix->previous = LosAngeles;
    LosAngeles->previous = NULL;

    head = LosAngeles;
    tail = Boston;
}

void CommunicationNetwork::printNetwork(){
    City *CurrentCity = head;
    cout << "===CURRENT PATH===" << endl;
    while(CurrentCity != NULL){
        cout << CurrentCity->cityName << " -> ";
        CurrentCity = CurrentCity->next;
    }
    cout << "NULL" << endl;
    cout << "==================" << endl;
}

CommunicationNetwork::CommunicationNetwork(bool isB, int CC){
    CityCount = CC;
    isBuilt = isB;
}

void CommunicationNetwork::clearNetwork(){
    string TempName;
    City *TEMP = new City();
    TEMP = head;
    while(CityCount > 0){
        TempName = TEMP->cityName;
        cout << "Deleting " << TempName << endl;
        deleteCity(TempName);
        TEMP = TEMP->next;
    }
    head = NULL;
}
