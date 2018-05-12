#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct BallPlayer;
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
};

class HashTable{
private:
    int TableSize;
    vector<BallPlayer>HashTable;
public:
    void Insert(BallPlayer *C);
    int hashSum(string firstLAST);
    HashTable();
};

#endif // HASHTABLE_H
