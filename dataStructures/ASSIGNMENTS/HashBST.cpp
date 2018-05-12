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
    BallPlayer *left;
    BallPlayer *right;
    BallPlayer *parent;
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
        linkedSearch = 0;
        STLL = 0;
        TableSize = s;
        FILENAME = name;
        BSTsearches = 0;
    }
    void Insert(BallPlayer *C);
    int hashSum(string firstLAST, int s);
    void readFileIn();
    int linkedCOL;
    int linkedSearch;
    int STLL;
    int BSTsearches;
    void printBST();
    string FILENAME;
    void ResetTable(){
        Table1.clear();
        for(int x=0; x<TableSize; x++){
            Table1.push_back(NULL);
        }
        linkedCOL = 0;
        //openACOL = 0;
        linkedSearch = 0;
        //openSearch = 0;
        STLL = 0;
        //STOA = 0;
    }
    BallPlayer * SearchTableBST(string first, string Last);
    void BSTinsert(BallPlayer *root, BallPlayer *C);
};
void HashTable::printBST(){
    for(int x=0; x<TableSize; x++){
        cout << Table1[x]->firstName << " " << Table1[x]->lastName << endl;
    }
}

int HashTable::hashSum(string name, int dataSize){
    int sum = 0;
    for(int x=0; x<name.size(); x++){
        sum = sum*31 + name[x];
        sum = sum%dataSize;
    }
    return sum;
}

void HashTable::readFileIn(){
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
                team CurrentTeam;
                CurrentTeam.year = stoi(playerData[0]);
                CurrentTeam.teamID = playerData[1];
                CurrentTeam.leagueID = playerData[2];
                CurrentTeam.salary = stoi(playerData[4]);
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

                Insert(CurrentPlayer);

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
        C->left = NULL;
        C->right = NULL;
    }else{
        BallPlayer *temp = Table1[hash1];
        BSTinsert(temp, C);
    }
}

void HashTable::BSTinsert(BallPlayer *root, BallPlayer *C){

    BallPlayer *temp = root;
    BallPlayer *parent;
    while(temp != NULL){

        parent = temp;
        if(C->firstName >= root->firstName){
            temp = temp->right;
        }
        if(C->firstName < root->firstName){
            temp = temp->left;
        }
    }
    if(C->firstName > parent->firstName){
        parent->right = C;
        C->parent = parent;
        C->left = NULL;
        C->right = NULL;
    }else if(C->firstName < parent->firstName){
        parent->left = C;
        C->parent = parent;
        C->left = NULL;
        C->right = NULL;
    }

    //cout << "BSTinsert complete" << endl;
 }


BallPlayer * HashTable::SearchTableBST(string first, string Last){
    int h = hashSum(first + Last, TableSize);
    string firstLast = first + Last;
    BallPlayer *t1 = Table1[h];
    if(t1->firstName + t1->lastName == firstLast){
        BSTsearches++;
        return t1;
    }else{
        while((t1->firstName + t1->lastName != firstLast) && (t1 != NULL)){
            if(first >= t1->firstName){
                BSTsearches++;
                t1 = t1->right;
            }
            if(first < t1->firstName){
                BSTsearches++;
                t1 = t1->left;
            }
        }
        return t1;
    }

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
    T1.readFileIn();
    int userIn;
    PrintMenu();
    cin >> userIn;
    bool menuOn = true;
    T1.printBST();
    while(menuOn){
        if(userIn == 1){
            cout << "Query the hashtable by entering first and last name, ex: Len Barker"<< endl;
            cout << "Enter player first name: ";
            string fn;
            cin >> fn;
            cout << "Enter player last name: ";
            string ln;
            cin >>ln;
            BallPlayer *U = T1.SearchTableBST(fn, ln);
            if(U != NULL){
                cout << "First name: "<< U->firstName << endl;
                cout << "Last name: " << U->lastName << endl;
                cout << "Bats: " << U->bats << endl;
                cout << "Throws: " << U->throws << endl;
                cout << "Birth Year: " << U->birthYear << endl;
                cout << "Height: " << U->height << endl;
                cout << "Weight: " << U->weight << endl;
                cout << endl;
            }else{
                cout << "Player not found." << endl;
            }
            cout << endl;
            cout << "BST searches to find player: " << T1.BSTsearches << endl;
            T1.BSTsearches = 0;
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
