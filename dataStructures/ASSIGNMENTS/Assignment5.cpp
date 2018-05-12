#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include "CommunicationNetwork.h"
#include <sstream>
#include <cstring>

using namespace std;

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
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-to-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
    cin >> userIn;
    string newCity, cityToFollow;
    while(MenuOn){
        if(userIn == 1){
            NetWork1.buildNetwork();
            cin >> userIn;
        }
        if(userIn == 2){
            NetWork1.printNetwork();
            cin >> userIn;
        }
        if(userIn == 3){
            NetWork1.transmitMsg(MsgIn);
            cin >> userIn;
        }
        if(userIn == 4){
            cin.ignore();
            cout << "Enter Name of New City" << endl;
            getline(cin, newCity);
            cout << "Enter Name of Previous City in Link" << endl;
            getline(cin, cityToFollow);
            NetWork1.addCity(newCity, cityToFollow);
            cin >> userIn;
        }
        if(userIn == 5){
            string CityName;
            cout << "Enter City to Delete from List" << endl;
            cin >> CityName;
            NetWork1.deleteCity(CityName);
            cin >> userIn;
        }
        if(userIn == 6){
            NetWork1.clearNetwork();
            cin >> userIn;
        }
        if(userIn == 7){
            cout << "Goodbye!" << endl;
            MenuOn = false;
        }
    }
    return 0;
}
