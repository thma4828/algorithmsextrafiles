#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
#include "MovieTreeRB.h"

using namespace std;
void MovieTreeRB::DeleteAll(MovieNode *x){
    if(x->leftChild != nil){
        DeleteAll(x->leftChild);
    }
    if(x->rightChild != nil){
        DeleteAll(x->leftChild);
    }
    cout << "Deleting: " << x->title << endl;
    rbDelete(x);
}
int MovieTreeRB::countMovieNodes(int cc, MovieNode *R1){
    cc++;
    if(R1->leftChild != nil)
        cc = countMovieNodes(cc, R1->leftChild);
    if(R1->rightChild != nil){
        cc = countMovieNodes(cc, R1->rightChild);
    }
    return cc;
}
// Returns 0 if the tree is invalid, otherwise returns the black node height.
int MovieTreeRB::rbValid(MovieNode * node)
{
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1;

    else
    {
        // First check for consecutive red links.
        if (node->isRed)
        {
            if(node->leftChild->isRed || node->rightChild->isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }
        // Check for valid binary search tree.
        if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0))
        {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }

        // Deteremine the height of let and right children.
        lh = rbValid(node->leftChild);
        rh = rbValid(node->rightChild);

        // If neither height is zero, incrament if it if black.
        if (lh != 0 && rh != 0)
        {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }

        else
            return 0;

    }
}

MovieNode* MovieTreeRB::addMovieNode(int r, string t, int ry, int q){
    MovieNode *temp = new MovieNode();
    MovieNode *newFilm = new MovieNode();
    MovieNode *parent = new MovieNode();
    if(!isB){
        root = nil;
        isB = true;
    }
    temp = root;
    newFilm->ranking = r;
    newFilm->title = t;
    newFilm->year = ry;
    newFilm->quantity = q;
    newFilm->parent = NULL;
    newFilm->leftChild = nil;
    newFilm->rightChild = nil;
    newFilm->color = 'R';

    if(temp == nil){
        root = newFilm;
        root->leftChild = nil;
        root->rightChild = nil;
    }else{
        while(temp != nil){
            parent = temp;
            if(newFilm->title < temp->title){
                temp = temp->leftChild;
            }else{
                temp = temp->rightChild;
            }
        }if(newFilm->title < parent->title){
            parent->leftChild = newFilm;
            newFilm->parent = parent;
        }else{
            parent->rightChild = newFilm;
            newFilm->parent = parent;
        }
    }
    return newFilm;
}

void MovieTreeRB::RedBlackInsert(int r1, string t1, int ry1, int q1){
    cout << "INSERT STARTED" << endl;
    MovieNode *x;
    MovieNode *Uncle;
    x = addMovieNode(r1, t1, ry1, q1);
    if(x != root){
        while(x->parent->color == 'R'){
              if(x->parent == x->parent->parent->leftChild){
                cout << "X PARENT IS A LEFTCHILD" << endl;
                Uncle = x->parent->parent->rightChild;
                if(Uncle->color == 'R'){
                    cout << "CASE A1: UNCLE IS RED" << endl;
                    x->parent->color = 'B';
                    Uncle->color = 'B';
                    x->parent->parent->color = 'R';
                    x = x->parent->parent;
                    if(x == root){
                        break;
                    }
                }else{
                    cout << "CASE A2: UNCLE IS BLACK" << endl;
                    if(x == x->parent->rightChild){
                        cout << "CASE A2a: X IS RIGHTCHILD" << endl;
                        x = x->parent;
                        leftRotate(x);
                    }else if(x == x->parent->leftChild)
                        cout << "CASE A2b: X IS LEFTCHILD" << endl;
                        x->parent->color = 'B';
                        x->parent->parent->color = 'R';
                        rightRotate(x->parent->parent);
                }
              }else if(x->parent == x->parent->parent->rightChild){
                  cout << "X PARENT IS A RIGHTCHILD" << endl;
                  Uncle = x->parent->parent->leftChild;
                  if(Uncle->color == 'R'){
                    cout << "CASE B1: UNCLE IS RED" << endl;
                    x->parent->color = 'B';
                    Uncle->color = 'B';
                    x->parent->parent->color = 'R';
                    x = x->parent->parent;
                    if(x == root)
                        break;
                  }else{
                      cout << "CASE B2: UNCLE IS BLACK" << endl;
                      if(x == x->parent->leftChild){
                        cout << "CASE B2a" << endl;
                        x = x->parent;
                        rightRotate(x);
                      }else if(x == x->parent->rightChild)
                        cout << "CASE B2b" << endl;
                        x->parent->color = 'B';
                        x->parent->parent->color = 'R';
                        leftRotate(x->parent->parent);
                  }
              }
        }
    }
    root->color = 'B';
    cout << "INSERT COMPLETE" << endl;
}
void MovieTreeRB::RBCase3Left(MovieNode *x){
    x->parent->color = 'B';
    x->parent->parent->color = 'R';
    rightRotate(x->parent->parent);
}
void MovieTreeRB::RBCase1Left(MovieNode *p, MovieNode *uncle){
    p->parent->color = 'B';
    uncle->color = 'B';
    p->parent->parent->color = 'R';
}

void MovieTreeRB::RBCase3Right(MovieNode *y){
    y->parent->color = 'B';
    y->parent->parent->color = 'R';
    leftRotate(y->parent->parent);
}
void MovieTreeRB::RBCase1Right(MovieNode *m, MovieNode *uncle){
    m->parent->color = 'B';
    uncle->color = 'B';
    m->parent->parent->color = 'R';
}

void MovieTreeRB::findMovie(string name){
    bool Found = false;
    MovieNode *Current;
    Current = root;
    while(Current != nil && !Found){
        if(Current->title == name){
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << Current->ranking << endl;
            cout << "Title:" << Current->title << endl;
            cout << "Year:" << Current->year << endl;
            cout << "Quantity:" << Current->quantity << endl;
            Found = true;
        }else if(Current->title < name){
            Current = Current->rightChild;
        }else if(Current->title > name){
            Current = Current->leftChild;
        }
    }if(!Found){
        cout << "Movie not found." << endl;
    }
}

void MovieTreeRB::rentMovie(string name1){
    bool Found = false;
    MovieNode *Current;
    Current = root;
    while(Current != nil && !Found){
        if(Current->title == name1){
            if(Current->quantity > 0){
                Current->quantity --;
                cout << "Movie Info:" << endl;
                cout << "===========" << endl;
                cout << "Ranking:" << Current->ranking << endl;
                cout << "Title:" << Current->title << endl;
                cout << "Year:" << Current->year << endl;
                cout << "Quantity:" << Current->quantity << endl;
                Found = true;
                if(Current->quantity == 0){
                    //deleteMovieNode(Current->title);
                    MovieNode *rx = getRoot();
                    MovieNode *delN = searchMovieTree(rx, Current->title);
                    rbDelete(delN);
                }
            }
            else if(Current->quantity == 0){
                //deleteMovieNode(Current->title);
                MovieNode *rx1 = getRoot();
                MovieNode *delN1 = searchMovieTree(rx1, Current->title);
                rbDelete(delN1);
            }
        }else if(Current->title < name1){
            Current = Current->rightChild;
        }else if(Current->title > name1){
            Current = Current->leftChild;
        }
    }if(!Found){
        cout << "Movie not found." << endl;
    }
}

void MovieTreeRB::printMovieInventory(MovieNode *n1){
    cout << "Movie: " << n1->title << "|| Color: " << n1->color << endl;
    if(n1->leftChild != nil){
        cout << "Left: " << n1->leftChild->title << endl;
    }
    if(n1->rightChild != nil){
        cout << "Right: " << n1->rightChild->title << endl;
    }

    if(n1->leftChild != nil){
        printMovieInventory(n1->leftChild);
    }

    if(n1->rightChild != nil){
        printMovieInventory(n1->rightChild);
    }
}

MovieNode* MovieTreeRB::searchMovieTree(MovieNode *n1, string value){
    if(n1 != nil){
        if(n1->title == value){
            return n1;
        }else if(n1->title > value){
            return searchMovieTree(n1->leftChild, value);
        }else{
            return searchMovieTree(n1->rightChild, value);
        }
    }else{
        return nil;
    }
}
void MovieTreeRB::leftRotate(MovieNode *x){
    MovieNode *y;
    y = x->rightChild;
    x->rightChild = y->leftChild;
    if(y->leftChild != nil){
        y->leftChild->parent = x;
    }
    y->parent = x->parent;
    if(x == root){
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
void MovieTreeRB::rightRotate(MovieNode *y){
    MovieNode *x;
    x = y->leftChild;
    y->leftChild = x->rightChild;
    if(x->rightChild != nil){
        x->rightChild->parent = y;
    }
    x->parent = y->parent;
    if(root == y){
        root = x;
    }else if(y == y->parent->leftChild){
        y->parent->leftChild = x;
    }else{
        y->parent->rightChild = x;
    }
    x->rightChild = y;
    y->parent = x;
}

void MovieTreeRB::rbTransplant(MovieNode *U, MovieNode *V){
    if(U->parent == nil){
        root = V;
    }else if(U == U->parent->leftChild){
        U->parent->leftChild = V;
    }else{
        U->parent->rightChild = V;
    }
    V->parent = U->parent;
}

MovieNode* MovieTreeRB::TreeMin(MovieNode *X){
    cout << "TreeMin init" << endl;
    while(X->leftChild != nil){
        X = X->leftChild;
    }
    cout << "TreeMin complete" << endl;
    return X;
}

MovieNode* MovieTreeRB::TreeMax(MovieNode *Y){
    while(Y->rightChild != nil){
        Y = Y->rightChild;
    }
    return Y;
}

void MovieTreeRB::rbDelete(MovieNode *Z){
    cout << "RB delete init" << endl;
    MovieNode *Y;
    MovieNode *X;
    Y = Z;
    if(Z->leftChild == NULL)
        Z->leftChild = nil;
    if(Z->rightChild == NULL)
        Z->rightChild = nil;
    char yCOLOR = Y->color;
    if(Z != root){
        if(Z->leftChild == nil && Z->rightChild != nil){
            cout << "case1 nodes left child is nil" << endl;
            X = Z->rightChild;
            rbTransplant(Z, Z->rightChild);
        }else if(Z->rightChild == nil && Z->leftChild != nil){
            cout << "case2 nodes right child is nil" << endl;
            X = Z->leftChild;
            rbTransplant(Z, Z->leftChild);
        }else if(Z->rightChild != nil && Z->leftChild != nil){
            cout << "case3 node has 2 children" << endl;
            Y = TreeMin(Z->rightChild);
            yCOLOR = Y->color;
            X = Y->rightChild;
            if(Y->parent == Z){
                cout << "case3a the minimum nodes parent is the node to be deleted" << endl;
                X->parent = Y;
            }else{
                cout << "case3b min node is NOT the child of node to be deleted" << endl;
                rbTransplant(Y, Y->rightChild);
                Y->rightChild = Z->rightChild;
                Y->rightChild->parent = Y;
            }
            rbTransplant(Z, Y);
            Y->leftChild = Z->leftChild;
            Y->leftChild->parent = Y;
            Y->color = Z->color;
            if(yCOLOR == 'B'){
                rbDeleteFixup(X);
            }
        }else if(Z->leftChild == nil && Z->rightChild == nil){
            cout << "case no children" << endl;
            if(Z == Z->parent->leftChild){
                cout << "no children case 1" << endl;
                MovieNode *parentZ = Z->parent;
                parentZ->leftChild = nil;
            }else{
                cout << "no children case 2" << endl;
                MovieNode *parentZ2 = Z->parent;
                parentZ2->rightChild = nil;
            }
        }
    }else{
        cout << "NOTE ROOT DELETION IS SUS AS FUCK" << endl;
        if(Z->leftChild == nil && Z->rightChild == nil){
            Z = nil;
        }else if(Z->leftChild == nil && Z->rightChild != nil){
            MovieNode *XB = new MovieNode();
            XB = Z->rightChild;
            rightRotate(Z);
            rbDelete(Z);
        }else if(Z->rightChild == nil && Z->leftChild != nil){
            MovieNode *XA = new MovieNode();
            XA = Z->leftChild;
            leftRotate(Z);
            rbDelete(Z);
        }else{
            Y = TreeMin(Z->rightChild);
            if(Y == Z->rightChild){
                Z->leftChild->parent = Y;
                Y->leftChild = Z->leftChild;
                root = Y;
                Y->color = 'B';
            }else{
                Z->leftChild->parent = Y;
                Z->rightChild->parent = Y;
                Y->leftChild = Z->leftChild;
                Y->rightChild = Z->rightChild;
                Y->parent->leftChild = nil;
                Y->parent = nil;
                root = Y;
            }
        }
    }
}
void MovieTreeRB::rbDeleteFixup(MovieNode *X){
    cout << "rbDeleteFixup init" << endl;
    MovieNode *W;
    while((X != root)&&(X->color == 'B')){
        if(X == X->parent->leftChild){
            cout << "c1: X is left child" << endl;
            W = X->parent->rightChild;
            if(W->color == 'R'){
                cout << "c1a: sister node is red" << endl;
                W->color = 'B';
                X->parent->color = 'R';
                leftRotate(X->parent);
                W = X->parent->rightChild;
            }
            if(W == nil){ cout << "W is NIL" << endl;}
            if(W->leftChild->color == 'B' && W->rightChild->color ==  'B'){
                cout << "c1b: sister node's left child is black and right child is black" << endl;
                W->color = 'R';
                X = X->parent;
            }else{
                cout << "c1c all other cases" << endl;
                if(W->rightChild->color == 'B'){
                    cout << "c1cb: sister node is black" << endl;
                    W->leftChild->color = 'B';
                    W->color = 'R';
                    rightRotate(W);
                    W = X->parent->rightChild;
                }
                W->color = X->parent->color;
                X->parent->color = 'B';
                W->rightChild->color = 'B';
                leftRotate(X->parent);
                X = root;
            }
        }else{
            cout << "c2: X is right child" << endl;
            W = X->parent->leftChild;
            if(W->color == 'R'){
                cout << "c2a sister node is red" << endl;
                W->color = 'B';
                X->parent->color = 'R';
                rightRotate(X->parent);
                W = X->parent->leftChild;
            }
            if(W == nil){ cout << "W is NIL" << endl;}
            if(W->leftChild->color == 'B' && W->rightChild->color == 'B'){
                cout << "c2b sisters left child is black and right child is black"<< endl;
                W->color = 'R';
                X = X->parent;
            }else{
                cout << "c2c all other cases" << endl;
                if(W->leftChild->color == 'B'){
                    cout << "c2ca sisters left child is black" << endl;
                    W->rightChild->color = 'B';
                    W->color = 'R';
                    leftRotate(W);
                    W = X->parent->leftChild;
                }
                W->color = X->parent->color;
                X->parent->color = 'B';
                W->leftChild->color = 'B';
                rightRotate(X->parent);
                X = root;
            }
        }
    }
}

void PrintMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Count the longest path" << endl;
    cout << "7. Quit" << endl;
}

MovieNode* MovieTreeRB::getRoot(){
    return root;
}

int main(){

    bool built = false;
    MovieTreeRB T1(built);

    int InP;
    bool menuOn = true;
    ifstream movies_in;
    movies_in.open("Movies1.txt");
    string line;
    string token;
    vector <string> lineVector;
    while(getline(movies_in, line)){
        istringstream ss(line);
        while(getline(ss, token, ',')){
            lineVector.push_back(token);
        }
        int inrank = stoi(lineVector.at(0));
        string title = lineVector.at(1);
        int year = stoi(lineVector.at(2));
        int quantity = stoi(lineVector.at(3));

        T1.RedBlackInsert(inrank, title, year, quantity);
        lineVector.clear();
    }
    PrintMenu();
    int userIn;
    cin >> userIn;
    while(menuOn){
            if(userIn == 1){
                cin.ignore();
                string t1;
                cout << "Enter title: " << endl;
                getline(cin, t1);
                T1.findMovie(t1);
                PrintMenu();
                cin >> userIn;
            }
            else if(userIn == 2){
                cin.ignore();
                string t2;
                cout << "Enter title: " << endl;
                getline(cin, t2);
                T1.rentMovie(t2);
                PrintMenu();
                cin >> userIn;
            }
            else if(userIn == 3){
                MovieNode *r;
                r = T1.getRoot();
                T1.printMovieInventory(r);
                PrintMenu();
                cin >> userIn;
            }
            else if(userIn == 4){
                cin.ignore();
                string t3;
                cout << "Enter title: " << endl;
                getline(cin, t3);
                MovieNode *RT = T1.getRoot();
                MovieNode *Dnode = T1.searchMovieTree(RT, t3);
                if(Dnode != T1.getNil()){
                    T1.rbDelete(Dnode);
                }else{
                    cout << "Movie not found" << endl;
                }

                PrintMenu();
                cin >> userIn;
            }
            else if(userIn == 5){
                int c_count = 0;
                MovieNode *r2 = T1.getRoot();
                int m = T1.countMovieNodes(c_count, r2);
                cout << "nodes in tree: " << m << endl;
                cin >> userIn;
            }
            else if(userIn == 6){
                MovieNode *RooT = T1.getRoot();
                int k = T1.rbValid(RooT);
                cout << k << endl;
                PrintMenu();
                cin >> userIn;
            }
            else if(userIn == 7){
                cout << "Goodbye" << endl;
                menuOn = false;

            }
            else{
                cin >> userIn;
            }

    }

    return 0;
}

