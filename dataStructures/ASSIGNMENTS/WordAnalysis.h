#ifndef _WORDANALYSIS_H_INCLUDED
#define _WORDANALYSIS_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
#endif // _WORDANALYSIS_H_INCLUDED
