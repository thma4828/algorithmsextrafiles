//CS 2270 FINAL PROJECT
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct team{
    int year;
    string teamID;
    int salary;
    string leagueID;
};

struct BallPlayer{
    BallPlayer *next;
    int yearID;
    string teamID;
    string leagueID;
    string playerID;
    int salary;
    string firstName;
    string lastName;
    int birthYear;
    string birthCountr;
    int weight;
    int height;
    char bats;
    char throws;
    vector<team*>TEAMS;
    bool isINtable;
};

class HashTable{
private:
    int TableSize;
    vector<BallPlayer*>Table1;
    bool isInit;
public:
    HashTable(bool, int s, string name){
        isInit = true;
        for(int x=0; x<s; x++){
            Table1.push_back(NULL);
        }
        linkedCOL = 0;
        openACOL = 0;
        linkedSearch = 0;
        openSearch = 0;
        STLL = 0;
        STOA = 0;
        TableSize = s;
        FILENAME = name;
    }
    void Insert(BallPlayer *C);
    void Insert2(BallPlayer *D);
    int hashSum(string firstLAST, int s);
    void readFileIn(int m);
    int linkedCOL;
    int openACOL;
    int linkedSearch;
    int openSearch;
    int STLL;
    int STOA;
    string FILENAME;
    void ResetTable(){
        Table1.clear();
        for(int x=0; x<TableSize; x++){
            Table1.push_back(NULL);
        }
        linkedCOL = 0;
        openACOL = 0;
        linkedSearch = 0;
        openSearch = 0;
        STLL = 0;
        STOA = 0;
    }
    BallPlayer * SearchTableLL(string firstLast);
    BallPlayer * SearchTableOA(string firstL);
};

int HashTable::hashSum(string name, int dataSize){
    int sum = 0;
    for(int x=0; x<name.size(); x++){
        sum = sum*31 + name[x];
        sum = sum%dataSize;
    }
    return sum;
}

void HashTable::readFileIn(int m){
    int gMcount = 0;
    ifstream moneyball;
    moneyball.open("bball.txt");
    string line, token;
    vector<string>playerData;
    vector<string>dataMembers;
    int lineCounter = 0;
    while(getline(moneyball, line)){
        if(line[0] != ' '){
        //cout << "line 61" << endl;
            if(lineCounter != 0){
                //cout << "line 63" << endl;
                istringstream ss(line);
                while(getline(ss, token, ',')){
                    playerData.push_back(token);
                }
                //cout << "line 68" << endl;
                BallPlayer *CurrentPlayer = new BallPlayer;
                CurrentPlayer->yearID = stoi(playerData[0]);
                CurrentPlayer->teamID = playerData[1];
                CurrentPlayer->leagueID = playerData[2];
                CurrentPlayer->playerID = playerData[3];
                CurrentPlayer->salary= stoi(playerData[4]);
                CurrentPlayer->firstName = playerData[5];
                //cout << "First name is: " << CurrentPlayer->firstName << endl;
                CurrentPlayer->lastName = playerData[6];
                //cout << "Last name is: " << CurrentPlayer->lastName << endl;
                CurrentPlayer->birthYear = stoi(playerData[7]);
                CurrentPlayer->birthCountr = playerData[8];
                CurrentPlayer->weight = stoi(playerData[9]);
                //cout << "line 80" << endl;
                CurrentPlayer->height = stoi(playerData[10]);
                char B, T;
                B = 'B';
                T = 'B';
                if(playerData[11] == "R")
                    B = 'R';
                else if(playerData[11] == "L"){
                    B = 'L';
                }
                //cout << "line 91" << endl;
                //cout << playerData[12] << " should be player data at [12]" << endl;
                if(playerData[12] == "R")
                    T = 'R';
                else if(playerData[12] == "L"){
                    T = 'L';
                }
                CurrentPlayer->bats = B;
                CurrentPlayer->throws = T;
                team *TM = new team();
                TM->leagueID = playerData[2];
                TM->salary = stoi(playerData[4]);
                TM->teamID = playerData[1];
                TM->year = stoi(playerData[0]);
                CurrentPlayer->TEAMS.push_back(TM);
                if(m == 1)
                    Insert(CurrentPlayer);
                else if(m == 2)
                    Insert2(CurrentPlayer);
                playerData.clear();

            }
        }
        lineCounter++;
    }
}

void HashTable::Insert(BallPlayer *C){
    string ln = C->lastName;
    string fn = C->firstName;
    fn += ln;
    int hash1 = hashSum(fn, TableSize);
    if(Table1[hash1] == NULL){
        Table1[hash1] = C;
        C->next = NULL;
    }else{
        linkedCOL++;
        bool isInTable = false;
        BallPlayer *Current = Table1[hash1];
        while(Current->next != NULL){
            if(Current->playerID == C->playerID){
                team *TM1 = new team();
                TM1->leagueID = C->leagueID;
                TM1->salary = C->salary;
                TM1->year = C->yearID;
                TM1->teamID = C->teamID;
                Current->TEAMS.push_back(TM1);
                linkedCOL--;
                isInTable = true;
                break;
            }
            Current = Current->next;
            linkedSearch++;
        }
        if(!isInTable)
            Current->next = C;
            C->next = NULL;
    }
}

void HashTable::Insert2(BallPlayer *D){
    string ln = D->lastName;
    string fn = D->firstName;
    fn += ln;
    int hash1 = hashSum(fn, TableSize);

    if(Table1[hash1] == NULL){
        Table1[hash1] = D;
    }else{
        openACOL++;
        bool isIN = false;
        while(Table1[hash1] != NULL){
            if(Table1[hash1]->playerID == D->playerID){
                isIN = true;
                openACOL--;
                break;
            }
            hash1++;
            openSearch++;
        }
        if(!isIN){
            Table1[hash1] = D;
        }else{
            team *TM2 = new team();
            TM2->leagueID = D->leagueID;
            TM2->salary = D->salary;
            TM2->year = D->yearID;
            TM2->teamID = D->teamID;
            Table1[hash1]->TEAMS.push_back(TM2);
        }
    }
}

BallPlayer * HashTable::SearchTableLL(string firstLast){
    STLL++;
    int h = hashSum(firstLast, TableSize);
    if(Table1[h] != NULL){
        BallPlayer *temp = Table1[h];
        while(temp != NULL){
            STLL++;
            if((temp->firstName + temp->lastName) == firstLast){
                return temp;
            }else{
                temp = temp->next;
            }
        }
    }
    return NULL;
}

BallPlayer *HashTable::SearchTableOA(string fl){
    STOA++;
    int hSUM = hashSum(fl, TableSize);
    if(Table1[hSUM] != NULL){
        BallPlayer *temp;
        while(hSUM < TableSize){
            STOA++;
            temp = Table1[hSUM];
            if(temp->firstName + temp->lastName == fl){
                return temp;
            }else{
                hSUM++;
            }
        }
    }
    return NULL;
}
void PrintMenu(){
    cout << "1. Query HashTable" << endl;
    cout << "2. Quit" << endl;
}
int main(){
    int tableSize = 5147;
    string fileN = "bball.txt";
    HashTable T1(true, tableSize, fileN);
    cout << "-------------------------------" << endl;
    cout << "Table size: " << tableSize << endl;
    cout << "-------------------------------" << endl;
    T1.readFileIn(1);
    cout << T1.linkedCOL << "  total collisions with linked list fix." << endl;
    cout << T1.linkedSearch << " total search operations for linked list fix." << endl;
    cout << "-------------------------------" << endl;
    T1.ResetTable();
    T1.readFileIn(2);
    cout << T1.openACOL << " total collisions with open addressing fix." << endl;
    cout << T1.openSearch << " total search operations with  open addressing fix." << endl;
    cout << "-------------------------------" << endl;
    T1.ResetTable();
    int userIn;
    PrintMenu();
    cin >> userIn;
    bool menuOn = true;
    while(menuOn){
        if(userIn == 1){
            T1.readFileIn(1);
            cout << "Query the hashtable with the concatenated string of the player! (ex. Len Barker -->>> LenBarker" << endl;
            cout << "Enter player name: ";
            string fL;
            cin >> fL;
            BallPlayer *U = T1.SearchTableLL(fL);
            if(U != NULL){
                cout << "First name: "<< U->firstName << endl;
                cout << "Last name: " << U->lastName << endl;
                cout << "Bats: " << U->bats << endl;
                cout << "Throws: " << U->throws << endl;
                cout << "Birth Year: " << U->birthYear << endl;
                cout << "Height: " << U->height << endl;
                cout << "Weight: " << U->weight << endl;
                cout << endl;
                cout << "TEAMS AND SALARIES: " << endl;
                cout << endl;
                cout << T1.STLL << " searches required to find player with linked list fix" << endl;
                T1.ResetTable();
                T1.readFileIn(2);
                BallPlayer *K = T1.SearchTableOA(fL);
                cout << T1.STOA << " searches required to find player with open addressing fix" << endl;
                if(K != NULL){
                    for(int i=0; i<K->TEAMS.size(); i++){
                        cout << i +1 << ":" << endl;
                        cout << "team: " << K->TEAMS[i]->teamID << endl;
                        cout << "league: " <<K->TEAMS[i]->leagueID << endl;
                        cout << "year: " <<K->TEAMS[i]->year << endl;
                        cout << "salary: "<<K->TEAMS[i]->salary << endl;
                    }
                }else{
                    for(int m=0; m<U->TEAMS.size(); m++){
                        cout << m+1 << ":" << endl;
                        cout << "team: " << U->TEAMS[m]->teamID << endl;
                        cout << "league: " <<U->TEAMS[m]->leagueID << endl;
                        cout << "year: " <<U->TEAMS[m]->year << endl;
                        cout << "salary: "<<U->TEAMS[m]->salary << endl;
                    }
                }
            }else{
                cout << "Player not found." << endl;
            }
            cout << endl;
            T1.ResetTable();
            PrintMenu();
            cin >> userIn;
        }else if(userIn == 2){
            cout << endl;
            cout << "Goodbye!" << endl;
            menuOn = false;
        }
    }
    return 0;
}
