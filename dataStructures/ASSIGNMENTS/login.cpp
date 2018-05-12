#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

struct realLogin{
    string U;
    string P;

    realLogin(string u, string p){
        U = u;
        P = p;
    }
};

class User{
public:
    User(bool init){
        userInit = init;
    }
    bool login(string user, string pass);
    void setPasswords();

private:
    string *passWords;
    string *userNames;
    bool userInit;
    vector<realLogin*>logs;

};


void User::setPasswords(){
    ifstream fileIn;
    string line, seg;
    vector <string> lineVector;
    fileIn.open("passwords.txt");
    int lineC = 0;
    while(getline(fileIn, line)){
        //cout << line << endl;
        if(lineC != 0){
            istringstream ss(line);
            while(getline(ss, seg, ',')){
                lineVector.push_back(seg);
            }
            string userName = lineVector[0];
            string passWord = lineVector[1];
            //cout << userName << passWord << endl;
            realLogin *LOG = new realLogin(userName, passWord);
            logs.push_back(LOG);
            lineVector.clear();
        }
        lineC++;
    }
    //cout << "-----passcodes loaded-----" << endl;

}

bool User::login(string Uname, string Pcode){
    for(int x=0; x<logs.size(); x++){
        if(logs[x]->P == Pcode && logs[x]->U == Uname){
            return true;
        }
    }
    return false;
}


int main() {
    User Theo(true);
    Theo.setPasswords();
    string user;
    string pass;
    cout << "Enter username: " << endl;
    cin >> user;
    cout << "Enter password: " << endl;
    cin >> pass;

    bool isIn = Theo.login(user, pass);

    if(isIn){
        cout << "PROFILE: THEODORE MARGOLES" << endl;
        cout << "AGE: 19" << endl;
        cout << "WEIGHT: 145" << endl;
        cout << "HEIGHT: 5'9''"<< endl;
    }else{
        cout << "user name and passcode do not match, shutting down" << endl;
        return -1;

    }
    return 0;

}
