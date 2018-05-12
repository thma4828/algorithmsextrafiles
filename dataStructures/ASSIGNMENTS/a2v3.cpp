#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

const int COMMONSIZE = 50;

struct Word{
    string name;
    int counter;
};

bool SearchCommonWords(string commonWords[], string current_word){
    bool found = false;
    int index = -1;
    int x = 0;
    while(!found && x < COMMONSIZE){
        if(commonWords[x] == current_word){
            found = true;
        }else{
            x++;
        }
    }

    return found;
}

bool SearchUniqueArray(Word UniqueWords[], string w, int Ucount){
    bool found = false;
    int index = -1;
    int x = 0;
    while(!found && x < Ucount){
        if(UniqueWords[x].name == w){
            found = true;
        }else{
            x++;
        }
    }

    return found;
}

void newfunc(bool IC){
    if(!IC){
        Umatch = SearchUniqueArray(UniqueWords, temp, UniqueCounter);
        if(!Umatch){
            UniqueWords[UniqueCounter].name = temp;
            cout << "UNIQUE WORD: " << temp << endl;
            UniqueCounter++;
        }

    }

}


int main(){
    //creation of dynamic array of structs
    int Size = 100;

    Word* UniqueWords = new Word[Size];
    string commonWords[COMMONSIZE]= {"the", "be", "to", "of", "and",
                                     "a", "in", "that", "have", "i",
                                     "it", "for", "not", "on", "he",
                                     "as", "you", "do", "at", "this",
                                     "but", "his", "by", "from", "they",
                                     "we", "say", "her", "she", "or", "will",
                                     "my", "one", "all", "would", "there", "their",
                                     "what", "so", "up", "out", "if", "about",
                                     "who", "get", "which", "with", "an", "go", "me"};
    string filename, line;
    ifstream book;
    cin >> filename;
    book.open(filename);
    int len_line;
    int Word_Counter = 0;
    bool isUnique;
    bool isCommon = true;
    bool Umatch;
    int UniqueCounter = 0;
    while(getline(book, line)){

        vector <string> split_str;

        istringstream iss(line);
        for(line; iss >> line;){
            split_str.push_back(line);
        }

        for(int i = 0; i<split_str.size(); i++){
            cout << split_str.at(i) << endl;
            string temp = split_str.at(i);
            bool MatchFound = SearchCommonWords(commonWords, temp);
            if(!MatchFound){
                isCommon = false;
            }else{
                isCommon = true;
            }


        }

        Word_Counter++;

    }






}
