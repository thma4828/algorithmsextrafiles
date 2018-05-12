#include <iostream>
#include <string>

using namespace std;

struct node{
    int ID;
    node *nextNode;
    node *previousNode;

    node(){}
    node(int id, node *NXTnode, node *PRVnode){
        ID = id;
        nextNode = NXTnode;
        previousNode = PRVnode;
    }
};

int main(){

    node *x1 = new node(1, NULL, NULL);
    node *x2 = new node(2, NULL, x1);
    node *x3 = new node(3, NULL, x2);

    x1->nextNode = x2;
    x2->nextNode = x3;

    node *current = x1;
    while(current->nextNode != NULL){
        cout << current->ID << endl;
        current = current->nextNode;
    }
    node *c2 = x3;
    while(current->previousNode != NULL){
        cout << current->ID << endl;
        c2 = c2->previousNode;
    }
    return 0;
}
