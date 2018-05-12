#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main() {
    string num;
    getline(cin, num);
    int NUM = stoi(num);
    //cout << NUM << endl;
    string line;
    getline(cin, line);
    vector<char>charVEC(NUM);
    char one;
    //vector<int>intV;
    for(int i=0; i<line.length(); i++){
        //cout << i << endl;
        //cout << line[0] << " == is line[0]" << endl;
        if(line[i] != ' '){
           charVEC.push_back(line[i]);
        }
    }
    for(int j=charVEC.size()-1; j>0; j--){
        if(charVEC[j] != ' ')
            cout << charVEC[j] << " ";
    }
    //cout << one << endl;
    return 0;

}
