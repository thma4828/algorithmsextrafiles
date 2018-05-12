#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node{
    string color;
    int key;
    node *leftChild;
    node *rightChild;
    node *parent;
    node(int k, string C){
        key = k;
        color = C;
    }
    node(){};
};

class RedBlackTree{
public:
    node *root;
    node *insertRB(int value);
    node *searchTree(int value);
    void leftRotate(node *sub_n1);
    void rightRotate(node *sub_n2);
    void rbBalance(node *snode);
    void RedBlackInsert(int k1);
    void RedBlackDelete(int k);
    void DeleteTree();
    void RBCase3Left(node *x);
    void RBprint(node *n1);
    void RBCase1Left(node *p, node *uncle);
    bool isBuilt;
    node *Nil;
    node *getRoot(){
        return root;
    }
    RedBlackTree(bool isb){
        isb = true;
        isBuilt = isb;
        root = NULL;
        Nil = new node();
        Nil->key = -10;
        Nil->color = "Black";
        Nil->leftChild = NULL;
        Nil->rightChild = NULL;
    }
};

void RedBlackTree::leftRotate(node *x){
    node *y;
    y = x->rightChild;
    x->rightChild = y->rightChild;
    if(y->leftChild != NULL){
        y->leftChild->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        root = y;
    }else{
        if(x == x->parent->leftChild){
            x->parent->leftChild = y;
        }else{
            x->parent->rightChild = y;
        }
    }
    y->leftChild = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(node *y){
    node *x;
    x = y->leftChild;
    y->leftChild = x->rightChild;
    if(x->rightChild != NULL){
        x->rightChild->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NULL){
        root = x;
    }else if(y == y->parent->leftChild){
        y->parent->leftChild = x;
    }else{
        y->parent->rightChild = x;
    }
    x->rightChild = y;
    y->parent = x;
}
node *RedBlackTree::insertRB(int v){
    int cc = 0;
    node *X = new node(v, "Red");
    node *temp = new node();
    X->leftChild = Nil;
    X->rightChild = Nil;
    node *parent = new node();
    temp = root;
    cout << "seg fault test" << endl;
    cout << "001" << endl;
    if(root != NULL){
        cout << "002" << endl;
        while(temp != Nil){
            parent = temp;
            if(X->key < temp->key){
                temp = temp->leftChild;
            }else{
                temp = temp->rightChild;
            }
            cout << "003" << endl;
        }
        if(X->key < parent->key){
           cout << "004" << endl;
           parent->leftChild = X;
           X->parent = parent;
           cout << "005" << endl;
        }else{
            parent->rightChild = X;
            X->parent = parent;
            cout << "006" << endl;
        }
    }else if(root == NULL){
        root = X;
        root->color = "Black";
        X->parent = NULL;
    }
    cout << "007";
    return X;
}
void RedBlackTree::RedBlackInsert(int key1){
    node *x;
    node *Uncle;
    x = insertRB(key1);
    while((x != root)&&(x->parent->color == "Red")){
          if(x->parent = x->parent->parent->leftChild){
            Uncle = x->parent->parent->rightChild;
            if(Uncle->color == "Red"){
                RBCase1Left(x, Uncle);
                x = x->parent->parent;
            }else{
                if(x == x->parent->rightChild){
                    x = x->parent;
                    leftRotate(x);
                }else if(x == x->parent->leftChild){
                    RBCase3Left(x);
                }
            }
          }else{
              Uncle = x->parent->parent->leftChild;
              if(Uncle->color == "Red"){
                RBCase1Left(x, Uncle);
              }else{
                  if(x == x->parent->rightChild){
                    x = x->parent;
                    leftRotate(x);
                  }else if(x == x->parent->leftChild){
                    RBCase3Left(x);
                  }

              }
          }
    }
    root->color = "Black";
}

void RedBlackTree::RBCase3Left(node *x){
    x->parent->color = "Black";
    x->parent->parent->color = "Red";
    rightRotate(x->parent->parent);
}

/***void RedBlackTree::RedBlackDelete(int key1){
    node = searchTree(int value);

}***/

void RedBlackTree::RBCase1Left(node *p, node *uncle){
    p->parent->color = "Black";
    uncle->color = "Black";
    p->parent->parent->color = "Black";
}

void RedBlackTree::RBprint(node *R){
    if(R->leftChild != Nil){
        RBprint(R->leftChild);
    }
    cout << "Key: " << R->key << "||Color: " << R->color << "||Parent: " << R->parent << "||LeftChild: " << R->leftChild << "||RightChild: " << R->rightChild << endl;
    if(R->rightChild != Nil){
        RBprint(R->rightChild);
    }
}

void printMenu(){
    cout << "1. AddNode" << endl;
    cout << "2. PrintTree" << endl;

}

int main(){
    RedBlackTree RBTree(false);
    bool menuOn = true;
    int userIn;
    printMenu();
    cin >> userIn;
    while(menuOn){
        if(userIn == 1){
            cin.ignore();
            cout << "Enter a value to insert" << endl;
            int val1;
            cin >> val1;
            RBTree.RedBlackInsert(val1);
            cin >> userIn;
        }
        if(userIn == 2){
            node *r = RBTree.getRoot();
            RBTree.RBprint(r);
            cin >> userIn;
        }
        if(userIn == 3){
            cin >> userIn;
        }
        if(userIn == 4){
            cin >> userIn;
        }

    }
}
