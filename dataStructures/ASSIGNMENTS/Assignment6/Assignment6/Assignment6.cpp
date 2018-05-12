#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue(int QS){
    queueSize = QS;
    arrayQueue = new string[queueSize];
    queueHead = 0;
    queueTail = 0;
}

bool Queue::queueIsFull(){
    bool QF;
    if(queueSize == queueCount){
        QF = true;
    }else if(queueSize != queueCount){
        QF = false;
    }
    return QF;
}

bool Queue::queueIsEmpty(){
    bool QE;
    if(queueCount == 0){
        QE = true;
    }else{
        QE = false;
    }
    return QE;
}

void Queue::enqueue(string s1){
    if(!queueIsFull()){
        arrayQueue[queueTail] = s1;
        queueCount++;
        if(queueTail == queueSize -1){
            queueTail = 0;
        }else{
            queueTail++;
        }
    }else{
        cout << "queue full" << endl;
    }
}

string Queue::dequeue(){
    string value = "";
    if(!queueIsEmpty()){
        value = arrayQueue[queueHead];
        queueCount--;
        if(queueHead == queueSize -1){
            queueHead = 0;
        }else{
            queueHead++;
        }
    }else{
        cout << "que empty" << endl;
    }
    return value;
}

void PrintMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Enqueue word" << endl;
    cout << "2. Dequeue word" << endl;
    cout << "3. Print queue" << endl;
    cout << "4. Enqueue sentence" << endl;
    cout << "5. Quit" << endl;
    cout << "=====================" << endl;
}

int main(){
    string s2;
    int UserIn;
    bool MenuOn = true;
    Queue Q1(10);
    PrintMenu();
    cin >> UserIn;
    while(MenuOn){
        if(UserIn == 1){
            cout << "enter word to enqueue: " << endl;
            cin >> s2;
            Q1.enqueue(s2);
            //Q1.printQueue();
            PrintMenu();
            cin >> UserIn;
        }
        if(UserIn == 5){
            MenuOn = false;
        }
    }

    return 0;
}


