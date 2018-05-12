#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;
//defining word struct
struct Word{
    string name;
    int counter;
};

class WordAnalysis{
	private:
		int timesDoubled;
		Word *words;
		int wordCount;
		int UniqueCounter;
    public:
		void doubleArrayAndAdd();
		bool checkIfCommonWord(string wrd);
		bool SearchUniqueArray(string wrd2);
		void AddArrayElement(string name);
		void sortData();
	    int Size;
	    void IncrementUniqueCounter(){
            UniqueCounter++;
	    }
	    void IncrementWordCounter(){
	        wordCount++;
	    }
	    void IncrementArrayDouble(){
	        timesDoubled++;
	    }
		bool readDataFile(string); //returns an error if file not opened
		int getWordCount();
		int getUniqueWordCount();
		int getArrayDoubling();
		void printCommonWords(int);
		WordAnalysis(int n){
		    Size = n;
            words = new Word[Size];
            UniqueCounter = 0;
            timesDoubled = 0;
            wordCount = 0;
		}
		WordAnalysis(){
            //empty
		}
		~WordAnalysis(){
		    //empty
		}
};

void WordAnalysis::printCommonWords(int num){
    for(int m=0; m<num; m++){
        cout << words[m].counter << " - " << words[m].name << endl;
    }

}
bool WordAnalysis::readDataFile(string fname){
    ifstream teststream;
    teststream.open(fname);
    return true;
}
int WordAnalysis::getWordCount(){
    return wordCount;
}
int WordAnalysis::getUniqueWordCount(){
    return UniqueCounter;
}
int WordAnalysis::getArrayDoubling(){
    return timesDoubled;
}
void WordAnalysis::doubleArrayAndAdd(){
    //doubling array and copying new value
    Size = Size*2;
    Word* word2 = new Word[Size];
    for(int m=0; m<Size/2; m++){
        word2[m].name = words[m].name;
        word2[m].counter = words[m].counter;
    }
                            //deleting old array and assigning new pointer to old pointer
    delete []words;
    words = word2;
}
void WordAnalysis::AddArrayElement(string currentWrd){
    words[UniqueCounter].name = currentWrd;
    words[UniqueCounter].counter = 1;
}
//defining Search Common Words function to search common words array
bool WordAnalysis::checkIfCommonWord(string current_word){
    string commonWords[50]= {"the", "be", "to", "of", "and",
                                     "a", "in", "that", "have", "i",
                                     "it", "for", "not", "on", "he",
                                     "as", "you", "do", "at", "this",
                                     "but", "his", "by", "from", "they",
                                     "we", "say", "her", "she", "or", "will",
                                     "my", "one", "all", "would", "there", "their",
                                     "what", "so", "up", "out", "if", "about",
                                     "who", "get", "which", "with", "an", "go", "me"};
    bool found = false;
    int index = -1;
    int x = 0;
    while(!found && x < 50){
        if(commonWords[x] == current_word){
            found = true;
        }else{
            x++;
        }
    }
    return found;
}
//function to search the array of unique words
bool WordAnalysis::SearchUniqueArray(string w){
    bool found = false;
    int index = -1;
    int x = 0;
    while(!found && x < UniqueCounter){
        if(words[x].name == w){
            words[x].counter = words[x].counter + 1;
            found = true;
        }else{
            x++;
        }
    }
    return found;
}
//function to sort most common array words and put them at the top
void WordAnalysis::sortData(){
    int swapI;
    string swapStr;
    for(int i=0; i<UniqueCounter; i++){
        for(int j=0; j<UniqueCounter - i - 1; j++){
            if(words[j].counter < words[j + 1].counter){
                swapI = words[j].counter;
                swapStr = words[j].name;
                words[j].counter = words[j+1].counter;
                words[j].name = words[j+1].name;
                words[j+1].counter = swapI;
                words[j+1].name = swapStr;
            }
        }
    }

}
//main passing in command line arguments
int main(/***int argc, char *argv[]***/){
    int the_size = 100;
    WordAnalysis Analysis1(the_size);
    WordAnalysis *wrdptr;
    wrdptr = &Analysis1;
    string filename, line;
    ifstream book;
    filename = "msgBoard.txt";
    bool isOpen = Analysis1.readDataFile(filename);
    book.open(filename);
    bool isUnique;
    bool isCommon = true;
    bool Umatch;
    //iterating through lines
    if(isOpen){
        while(getline(book, line)){
            if(line != " "){
                //splitting lines into a words in a vector
                vector <string> split_str;
                istringstream iss(line);
                for(line; iss >> line;){
                    split_str.push_back(line);
                }
                    //iterating through words to do operations on them
                for(int i = 0; i<split_str.size(); i++){
                    string temp = split_str.at(i);
                    //searching for match in common words
                    bool MatchFound = Analysis1.checkIfCommonWord(temp);
                    if(!MatchFound){
                        isCommon = false;
                        Analysis1.IncrementWordCounter();
                    }else{
                        isCommon = true;
                    }
                        //searching for match in unique array
                    if(!isCommon){
                        Umatch = Analysis1.SearchUniqueArray(temp);
                        if(!Umatch){
                            Analysis1.AddArrayElement(temp);
                            Analysis1.IncrementUniqueCounter();
                            int currentCount = Analysis1.getUniqueWordCount();
                            if(currentCount >= wrdptr->Size){
                                Analysis1.doubleArrayAndAdd();
                                Analysis1.IncrementArrayDouble();
                            }
                        }
                    }
                }
            }
        }


    }
    Analysis1.sortData();
    int n;
    cin >> n;
    Analysis1.printCommonWords(n);
    int double_counter = Analysis1.getArrayDoubling();
    int UniqueCounter = Analysis1.getUniqueWordCount();
    int Word_Counter =  Analysis1.getWordCount();
    cout << "#" << endl;
    cout << "Array doubled: " << double_counter << endl;
    cout << "#" << endl;
    cout << "Unique non-common words: " << UniqueCounter << endl;
    cout << "#" << endl;
    cout << "Total non-common words: " << Word_Counter << endl;
}
