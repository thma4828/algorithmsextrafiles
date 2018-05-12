#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;
const int COMMONSIZE = 50;
int unique_index = -1;

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
            UniqueWords[x].counter = UniqueWords[x].counter + 1;
            found = true;
        }else{
            x++;
        }
    }
    return found;
}

void BubbleSort(Word UniqueWords[], int the_count){
    int swapI;
    string swapStr;
    for(int i=0; i<the_count; i++){
        for(int j=0; j<the_count - i - 1; j++){
            if(UniqueWords[j].counter < UniqueWords[j + 1].counter){
                swapI = UniqueWords[j].counter;
                swapStr = UniqueWords[j].name;
                UniqueWords[j].counter = UniqueWords[j+1].counter;
                UniqueWords[j].name = UniqueWords[j+1].name;
                UniqueWords[j+1].counter = swapI;
                UniqueWords[j+1].name = swapStr;
            }
        }
    }

}



int main(){
    int Size = 100;
    //create an array of all WORDS not just Unique ones and them do comparison with counters.
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
    int double_counter = 0;
    int total_words = 0;
    while(getline(book, line)){
        if(line != " "){
            vector <string> split_str;
            istringstream iss(line);
            for(line; iss >> line;){
                split_str.push_back(line);
            }
            for(int i = 0; i<split_str.size(); i++){
                string temp = split_str.at(i);
                bool MatchFound = SearchCommonWords(commonWords, temp);
                if(!MatchFound){
                    isCommon = false;
                    Word_Counter++;
                }else{
                    isCommon = true;
                }
                if(!isCommon){
                    Umatch = SearchUniqueArray(UniqueWords, temp, UniqueCounter);
                    if(!Umatch){
                        UniqueWords[UniqueCounter].name = temp;
                        UniqueWords[UniqueCounter].counter = 1;
                        UniqueCounter++;
                        if(UniqueCounter >= Size){
                            double_counter++;
                            Size = Size*2;
                            Word* UniqueWords2 = new Word[Size];
                            for(int m=0; m<Size/2; m++){
                                UniqueWords2[m].name = UniqueWords[m].name;
                                UniqueWords2[m].counter = UniqueWords[m].counter;
                            }
                            delete []UniqueWords;
                            UniqueWords = UniqueWords2;
                        }
                    }
                }
            }
        }
    }

    //function to get top nth most common words.


    cout << "Array doubled:" << double_counter << endl;
    cout << "Unique non-common words:" << UniqueCounter << endl;
    cout << "Total non-common words:" << Word_Counter << endl;

    BubbleSort(UniqueWords, UniqueCounter);

    int n;
    cin >> n;
    for(int m=0; m<n; m++){
        cout << UniqueWords[m].name << " " << UniqueWords[m].counter << endl;
    }
}
