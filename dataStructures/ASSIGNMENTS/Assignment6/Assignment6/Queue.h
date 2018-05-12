#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>

using namespace std;

class Queue
{
    public:
        Queue(int);
        ~Queue(){
            //empty for now
        }
        //circular queue methods
        void enqueue(string);
        string dequeue(); //should send through network, call transmit msg
        void printQueue();
        bool queueIsFull(); //send when full
        bool queueIsEmpty(); //send when empty

    protected:
    private:
        int queueSize;
        int queueHead;
        int queueTail;
        int queueCount;
        string *arrayQueue;
};

#endif // QUEUE_H
