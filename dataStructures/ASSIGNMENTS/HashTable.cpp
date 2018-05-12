//CS 2270 FINAL PROJECT
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

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
    vector<BallPlayer*>TeamMates;
    bool isINtable;
};

struct lineUp{
    queue<BallPlayer*>line_up;
};

class BallStats{
public:
    int sample_size;
    float avg_years_played;
    vector<int>salaries;
    vector<int>heights;
    vector<int>weights;
    vector<char>bats;
    int avg_s;
    BallStats(int ss){
        sample_size = ss;
    }
    long get_avg_sal(){
        long sum = 0;
        for(int i=0; i<salaries.size(); i++){
            sum += salaries[i];
        }
        long avg = sum / salaries.size();
        return avg;
    }
    int get_avg_height(){
        int sum = 0;
        for(int j=0; j<heights.size(); j++){
            sum += heights[j];
        }
        return(sum/heights.size());
    }
    int get_avg_weight(){
        int sum = 0;
        for(int j=0; j<weights.size(); j++){
            sum += weights[j];
        }
        return(sum/weights.size());
    }
    int * batsR_batsL(){
        int left = 0;
        int right = 0;
        for(int i=0; i<bats.size(); i++){
            if(bats[i] == 'R'){
                right++;
            }else if(bats[i] == 'L'){
                left++;
            }
        }
        int *lr = new int[2];
        lr[0] = left;
        lr[1] = right;
        return lr;
    }
    ~BallStats(){ //
    }
};

class HashTable{
private:
    int TableSize;
    vector<BallPlayer*>Table1;
    bool isInit;
    int hash_mod;
public:
    HashTable(bool, int s, string name){
        isInit = true;
        hash_mod = 31;
        t_stats = new BallStats(s);
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
        line_set = true;
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
    bool line_set;
    int STOA;
    void getTeam(BallPlayer *x);
    void analyze_line();
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
        duplicates = 0;
    }
    int get_t_size(){
        return TableSize;
    }
    int get_hash_mod(){
        return hash_mod;
    }
    void set_hash_mod(int hm){
        hash_mod = hm;
    }
    BallPlayer * SearchTableLL(string firstLast);
    BallPlayer * SearchTableOA(string firstL);
    BallStats *t_stats;
    lineUp my_lineup;
    int duplicates;
};

int HashTable::hashSum(string name, int dataSize){
    int sum = 0;
    for(int x=0; x<name.size(); x++){
        sum = sum*hash_mod + name[x];
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
                if(m == 1){
                    Insert(CurrentPlayer);
                    getTeam(CurrentPlayer);
                }else if(m == 2)
                    Insert2(CurrentPlayer);
                playerData.clear();

            }
        }
        lineCounter++;
    }
}
void HashTable::getTeam(BallPlayer *X){
    for(int i=0; i<TableSize; i++){
        if(Table1[i] != NULL){
            if((Table1[i]->teamID == X->teamID) && (Table1[i]->yearID == X->yearID) && (Table1[i]->playerID != X->playerID)){
                X->TeamMates.push_back(Table1[i]);
            }
        }
    }
}
void HashTable::Insert(BallPlayer *C){
    //cout << C->salary << endl;
    t_stats->salaries.push_back(C->salary);
    t_stats->heights.push_back(C->height);
    t_stats->weights.push_back(C->weight);
    t_stats->bats.push_back(C->bats);
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
                ++duplicates;
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
                ++duplicates;
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

void HashTable::analyze_line(){
    long total_salary, mean_salary;
    long counTT = 0;
    long one = 1;
    while(!my_lineup.line_up.empty()){
        BallPlayer *current = my_lineup.line_up.front();
        my_lineup.line_up.pop();
        cout << current->playerID << " -=- " << current->height << " -=- " << current->salary << " -=- " <<endl;
        total_salary += current->salary;
        counTT += one;
    }
    if(counTT != 0){
        mean_salary = total_salary/counTT;
        cout << "mean team member yearly salary = " << mean_salary << endl;
    }else{
        cerr << "dividing by zero" << endl;
    }
}
void PrintMenu(){
    cout << "1. Query HashTable" << endl;
    cout << "2. Build lineup" << endl;
    cout << "3. My lineup stats" << endl;
    cout << "4. Modify hash function" << endl;
    cout << "5. Quit" << endl;
}

int main(){
    cout << "LOADING......" << endl;
    int tableSize = 5147;
    string fileN = "bball.txt";
    HashTable T1(true, tableSize, fileN);
    cout << "-------------------------------" << endl;
    cout << "Table size: " << tableSize << endl;
    cout << "-------------------------------" << endl;
    T1.readFileIn(1);
    int dup = T1.duplicates;
    cout << T1.linkedCOL << "  total collisions with linked list fix." << endl;
    cout << T1.linkedSearch << " total search operations for linked list fix." << endl;
    cout << "-------------------------------" << endl;
    T1.ResetTable();
    T1.readFileIn(2);
    cout << T1.openACOL << " total collisions with open addressing fix." << endl;
    cout << T1.openSearch << " total search operations with  open addressing fix." << endl;
    cout << "-------------------------------" << endl;
    cout << "hash modulator = " << T1.get_hash_mod() << endl;
    cout << "-------------------------------" << endl;
    cout << "{+} ******Stats****** {+}" << endl;
    cout << "Average salary from players surveyed: " << T1.t_stats->get_avg_sal()  << " dollars" << endl;
    cout << "Average height of players surveyed: " << T1.t_stats->get_avg_height() << " inches "<< endl;
    cout << "Average weight of players surveyed: " << T1.t_stats->get_avg_weight() << " lbs" << endl;
    int *s = T1.t_stats->batsR_batsL();
    cout << "There are " << s[0] << " left batters" << endl;
    cout << "There are " << s[1] << " right batters" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //cout << "There are " << dup << " duplicates in the table." << endl;
    //Scout << "Duplicates make up " << 100*(dup/T1.get_t_size()) << " %  of the table" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    float total_batters = s[0] + s[1];
    float left = s[1];
    float right = s[0];
    cout << (right / total_batters)*100 << "% right batters --(note: inaccurate because of dups)" << endl;
    cout << (left / total_batters)*100 << "% left batters" << endl;
    cout << "-------------------------------" << endl;
    cout << "{-} ************* {-}" << endl;
    T1.ResetTable();
    int userIn;
    PrintMenu();
    cin >> userIn;
    bool menuOn = true;
    while(menuOn){
        if(userIn == 1){
            cout <<"LOADING..." << endl;
            T1.readFileIn(1);
            cout << "Query the hashtable with the concatenated string of the player! (ex. Len Barker -->>> LenBarker" << endl;
            cout << "Enter player name: ";
            string fL;
            cin >> fL;
            //cout << "Searching for: " << fL << endl;
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
                cout << "-=-=-=-=-=-=-=-=-=-=-" << endl;
                cout << "-----TEAM MATES------" << endl;
                for(int i=0; i<U->TeamMates.size(); i++){
                    cout << U->TeamMates[i]->playerID << endl;
                }
                if(U->TeamMates.size() == 0){cout << "NONE" << endl;}
                cout << "-=-=-=-=-=-=-=-=-=-=-=" << endl;
            }else{
                cout << "Player not found." << endl;
            }
            cout << endl;
            T1.ResetTable();
            PrintMenu();
            cin >> userIn;
        }else if(userIn == 2){
            cout << "LOADING" << endl;
            T1.readFileIn(1);
            cout << "-=-=-=-=-=-=TEAM LINEUP-=-=-=-=-=-=-=-" << endl;
            cout << "Enter number of players to queue to your team: " << endl;
            int n;
            cin >> n;
            int c = 0;
            while(n > 0){
                 n--;
                 c++;
                 cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
                 cout << "Player number : " << c << endl;
                 cout << "Enter concatenated name of player aka LenBarker to search and add to your lineup." << endl;
                 string name_player;
                 cin >> name_player;
                 BallPlayer *I = T1.SearchTableLL(name_player);
                 //cout << "Searching for: " << name_player << endl;
                 if(I != NULL){
                    T1.my_lineup.line_up.push(I);
                 }else{
                    cout << "Player not found..." << endl;
                    c--;
                    n++;
                 }
            }
            cout << "~~~--------------------~~~" << endl;
            cout << endl;
            PrintMenu();
            T1.ResetTable();
            cin >> userIn;
        }else if(userIn == 5){
            cout << endl;
            cout << "Goodbye!" << endl;
            menuOn = false;
        }else if(userIn == 3){
            if(!T1.line_set){
                cout << "You have not chosen a lineup!" << endl;
            }else{
                T1.analyze_line();
            }
            cin >> userIn;
            cout << "-------~~~~~~~~~~~~~~-------" << endl;
        }else if(userIn == 4){
            int hmod;
            cout << "Enter new hash_mod to use! (should be integer)" << endl;
            cin >> hmod;
            T1.set_hash_mod(hmod);
            T1.ResetTable();
            cout << "LOADING" << endl;
            T1.readFileIn(1);
            cout << T1.linkedCOL << "  total collisions with linked list fix." << endl;
            cout << T1.linkedSearch << " total search operations for linked list fix." << endl;
            T1.ResetTable();
            cin >> userIn;
        }
    }
    return 0;
}
