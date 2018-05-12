#include <iostream>
#include <string>

using namespace std;

struct node


node *DeleteNode(node *head, int value){

    node *currentNode = new node();
    currentNode = head;
    bool allFound = false;
    if(head->next != NULL){
        while(!allFound){

            if(currentNode->next->value != value){
                currentNode = currentNode->next;
            }
            if(currentNode->next->value == value){
                currentNode->next = currentNode->next->next;
            }

            if(currentNode->next == NULL){
                allFound = true;
            }

        }
    }



    return head;

}
