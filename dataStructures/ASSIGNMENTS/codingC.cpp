#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;


int main() {
    int T;
    cin >> T;
    map<string,int>blackBook;
    for(int i=0; i<T; i++){
        string name, name_num;
        int number;
        cin >> name_num;
        int pos;
        pos = name_num.find(' ', 1);
        if(pos != -1){
            name = name_num.substr(0, pos);
            number = stoi(name_num.substr(pos));
            blackBook.emplace(name, number);
        }else{
            cout << "logic error" << endl;
        }

    }
    //vector<string>lines;
    string c_line;
    while(getline(cin, c_line)){
        int number = blackBook[c_line];
        if(number != -1){
            cout << c_line << "=" << number;
        }else{
            cout << "Not found";
        }
        cout << "\n";
    }

    return 0;
}
