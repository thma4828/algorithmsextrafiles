#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main(){
    queue <int> myqueue;
    cout << myqueue.size() << endl;
    myqueue.push(3);
    myqueue.push(6);
    myqueue.push(5);
    cout << myqueue.size() << endl;
    while(!myqueue.empty()){
        myqueue.pop();
    }
    cout << myqueue.size() << endl;
}





