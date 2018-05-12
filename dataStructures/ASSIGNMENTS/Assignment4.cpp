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
        cout << "Empty list" << endl;
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
        for(int i=0; i<splitStr.size(); i++){
            while(CurrentCity != NULL){
                CurrentCity->message = splitStr.at(i);
                cout << CurrentCity->cityName << " received " << splitStr.at(i) << endl;
                CurrentCity = CurrentCity->next;
            }

            CurrentCity = tail;
            CurrentCity = CurrentCity->previous;
            while(CurrentCity != NULL){
                CurrentCity->message = splitStr.at(i);
                cout << CurrentCity->cityName << " received " << splitStr.at(i) << endl;
                CurrentCity = CurrentCity->previous;
            }
            CurrentCity = head;
        }
    }
}

void CommunicationNetwork::addCity(string Name, string cityPrevious){
    isBuilt = true;
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
        newCity->previous = NULL;
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
        //if the head name is the city to delete
        found = true;
        temp = head;
        //head = head->next;
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
        cout << name << "not found" << endl;
    }
}

void CommunicationNetwork::buildNetwork(){
    isBuilt = true;
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
    if(isBuilt){
       cout << "NULL <- ";
        while(CurrentCity != NULL){
            cout << CurrentCity->cityName;
            if(CurrentCity->next != NULL){
                cout << " <-> ";
            }else if(CurrentCity->next == NULL){
                cout << " -> ";
            }
            CurrentCity = CurrentCity->next;
        }
    }
    cout << "NULL" << endl;
    cout << "==================" << endl;
}

CommunicationNetwork::CommunicationNetwork(bool isB, int CC){
    CityCount = CC;
    isBuilt = isB;
}

void CommunicationNetwork::clearNetwork(){
    isBuilt = false;
    string TempName;
    City *TEMP = new City();
    TEMP = head;
    while(CityCount > 0){
        TempName = TEMP->cityName;
        cout << "deleting " << TempName << endl;
        deleteCity(TempName);
        TEMP = TEMP->next;
    }
    head = NULL;
}

void printMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
}

int main(/***int argc, char *argv[]***/){
    ifstream msgIn;
    string filename = "msgIn.txt"; //argv[1];
    msgIn.open(filename);
    string TheMessage, line;
    while(getline(msgIn, line)){
        TheMessage = line;
    }
    vector<char> vec(TheMessage.begin(), TheMessage.end());
    char *MsgIn = &vec[0];
    bool Built = false;
    bool MenuOn = true;
    CommunicationNetwork NetWork1(Built, 10);
    int userIn;
    printMenu();
    cin >> userIn;
    string newCity, cityToFollow;
    while(MenuOn){
        if(userIn == 1){
            NetWork1.buildNetwork();
            NetWork1.printNetwork();
            printMenu();
            cin >> userIn;
        }
        if(userIn == 2){
            NetWork1.printNetwork();
            printMenu();
            cin >> userIn;
        }
        if(userIn == 3){
            NetWork1.transmitMsg(MsgIn);
            printMenu();
            cin >> userIn;
        }
        if(userIn == 4){
            cin.ignore();
            cout << "Enter a city name: " << endl;
            getline(cin, newCity);
            cout << "Enter a previous city name: " << endl;
            getline(cin, cityToFollow);
            NetWork1.addCity(newCity, cityToFollow);
            printMenu();
            cin >> userIn;
        }
        if(userIn == 5){
            string CityName;
            cout << "Enter a city name: " << endl;
            cin >> CityName;
            NetWork1.deleteCity(CityName);
            printMenu();
            cin >> userIn;
        }
        if(userIn == 6){
            NetWork1.clearNetwork();
            printMenu();
            cin >> userIn;
        }
        if(userIn == 7){
            cout << "Goodbye!" << endl;
            MenuOn = false;
        }
    }
    return 0;
}
