#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct BNode{
    int key;
    vector<BNode*>KEYS;
    BNode *parent;
    bool leafNode;
    int minDegree;
    int maxDegree:
    BNode(){
        minDegree = 2;
        maxDegree = 4;
    }
};

class BTree{
public:
    BTree(bool tb){
        treeBUILT = tb;
        root->leafNode = false;
    }

private:
    bool treeBUILT;
    BNode *root;

};

int main(){

}
