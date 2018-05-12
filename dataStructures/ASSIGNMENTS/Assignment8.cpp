#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "MovieTree.h"

using namespace std;

void MovieTree::addMovieNode(int r, string t, int ry, int q){
    MovieNode *temp = new MovieNode();
    MovieNode *newFilm = new MovieNode();
    MovieNode *parent = new MovieNode();
    temp = root;

    newFilm->ranking = r;
    newFilm->title = t;
    newFilm->year = ry;
    newFilm->quantity = q;
    newFilm->parent = NULL;
    newFilm->leftChild = NULL;
    newFilm->rightChild = NULL;

    if(temp == NULL){
        root = newFilm;
    }else{
        while(temp != NULL){
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
}

void MovieTree::findMovie(string name){
    bool Found = false;
    MovieNode *Current;
    Current = root;
    while(Current != NULL && !Found){
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

void MovieTree::rentMovie(string name1){
    bool Found = false;
    MovieNode *Current;
    Current = root;
    while(Current != NULL && !Found){
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
                    deleteMovieNode(Current->title);
                }
            }
            else if(Current->quantity == 0){
                deleteMovieNode(Current->title);
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

void MovieTree::printMovieInventory(MovieNode *n1){
    if(n1->leftChild != NULL){
        printMovieInventory(n1->leftChild);
    }
    cout << "Movie: " << n1->title << " " << n1->quantity << endl;
    if(n1->rightChild != NULL){
        printMovieInventory(n1->rightChild);
    }
}

MovieNode* MovieTree::searchRecursive(MovieNode *n1, string value){
    if(n1 != NULL){
        if(n1->title == value){
            return n1;
        }else if(n1->title > value){
            return searchRecursive(n1->leftChild, value);
        }else{
            return searchRecursive(n1->rightChild, value);
        }
    }else{
        return NULL;
    }
}

MovieNode* MovieTree::treeMinimum(MovieNode *theNode){
    while(theNode->leftChild != NULL){
        theNode = theNode->leftChild;
    }
    return theNode;
}

void MovieTree::deleteMovieNode(string the_title){
    MovieNode *CNode;
    MovieNode *CParent;
    MovieNode *Cleft;
    MovieNode *Cright;
    MovieNode *Cmin;
    CNode = searchRecursive(root, the_title);
    if(CNode != NULL){
        if(CNode != root){
            if(CNode->leftChild == NULL && CNode->rightChild == NULL){ // no children
                if(CNode->title < CNode->parent->title)
                    CNode->parent->leftChild = NULL;
                else
                    CNode->parent->rightChild = NULL;
            }else if(CNode->leftChild != NULL && CNode->rightChild != NULL){ //two children
                Cmin = treeMinimum(CNode->rightChild);
                if(Cmin == CNode->rightChild || Cmin == CNode->leftChild){
                    if(CNode->title > CNode->parent->title)
                        CNode->parent->rightChild = Cmin;
                    else
                        CNode->parent->leftChild = Cmin;
                    Cmin->parent = CNode->parent;
                    Cmin->leftChild = CNode->leftChild;
                    Cmin->leftChild->parent = Cmin;
                }else{
                    Cmin->parent->leftChild = Cmin->rightChild;
                    Cmin->rightChild->parent = Cmin->parent;
                    Cmin->parent = CNode->parent;
                    CNode->parent->leftChild = Cmin;
                    Cmin->leftChild = CNode->leftChild;
                    Cmin->rightChild = CNode->rightChild;
                    CNode->leftChild->parent = Cmin;
                    CNode->rightChild->parent = Cmin;
                }
            }else{ //one child
                if(CNode->leftChild != NULL){
                    Cleft = CNode->leftChild;
                    if(CNode->title > CNode->parent->title)
                        CNode->parent->rightChild = Cleft;
                    else
                        CNode->parent->leftChild = Cleft;
                    Cleft->parent = CNode->parent;
                }else{
                    Cright = CNode->rightChild;
                    if(CNode->title > CNode->parent->title)
                        CNode->parent->rightChild = Cright;
                    else
                        CNode->parent->leftChild = Cright;
                    Cright->parent = CNode->parent;
                }
            }
        }else{
            if(CNode->leftChild == NULL && CNode->rightChild == NULL){ // no children
                CNode = NULL;
                root = NULL;
            }else if(CNode->leftChild != NULL && CNode->rightChild != NULL){ //two children
                Cmin = treeMinimum(CNode->rightChild);
                if(Cmin == CNode->rightChild || Cmin == CNode->leftChild){
                    if(Cmin->title >= CNode->title){
                        CNode->leftChild->parent = Cmin;
                        Cmin->leftChild = CNode->leftChild;
                        CNode = NULL;
                        root = Cmin;
                    }else{
                        CNode->rightChild->parent = Cmin;
                        Cmin->rightChild = CNode->rightChild;
                        CNode = NULL;
                        root = Cmin;
                    }
                }else{
                    Cmin->parent->leftChild = Cmin->rightChild;
                    if(Cmin->rightChild != NULL){
                        Cmin->rightChild->parent = Cmin->parent;
                        Cmin->parent->leftChild = Cmin->rightChild;
                    }
                    Cmin->parent = NULL;
                    Cmin->leftChild = CNode->leftChild;
                    Cmin->rightChild = CNode->rightChild;
                    CNode->leftChild->parent = Cmin;
                    CNode->rightChild->parent = Cmin;
                    root = Cmin;
                }
            }else{ //one child
                MovieNode *Ctemp;
                if(CNode->leftChild != NULL){
                    Ctemp = CNode->leftChild;
                    Ctemp->parent = NULL;
                    root = Ctemp;
                    CNode = NULL;
                }
            }
        }
        //delete CNode;
    }else{
        cout << "Movie not found." << endl;
    }
}

int MovieTree::countMovieNodes(MovieNode *knode, int counter){
    if(knode->leftChild != NULL){
        counter++;
        counter = countMovieNodes(knode->leftChild, counter);
    }
    if(knode->rightChild != NULL){
        counter++;
        counter = countMovieNodes(knode->rightChild, counter);
    }

    return counter;
}

void printMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Quit" << endl;
}

int main(){
    bool built = true;
    MovieTree Mtree(built);
    ifstream movies_in;
    movies_in.open("Movies.txt");
    string line;
    string token;
    printMenu();
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
        Mtree.addMovieNode(inrank, title, year, quantity);
        lineVector.clear();
    }
    bool menuOn = true;
    int UserIn;
    cin >> UserIn;
    while(menuOn){
        if(UserIn == 1){
            cin.ignore();
            string title;
            cout << "Enter title:" << endl;
            getline(cin, title);
            Mtree.findMovie(title);
            cin >> UserIn;

        }else if(UserIn == 2){
            cin.ignore();
            string t1;
            cout << "Enter title:" << endl;
            getline(cin, t1);
            Mtree.rentMovie(t1);
            cin >> UserIn;

        }else if(UserIn == 3){
            MovieNode *MNode = Mtree.getRoot();
            Mtree.printMovieInventory(MNode);
            cin >> UserIn;

        }else if(UserIn == 4){
            cin.ignore();
            string t2;
            cout << "Enter title:" << endl;
            getline(cin, t2);
            Mtree.deleteMovieNode(t2);
            cin >> UserIn;

        }else if(UserIn == 5){
            int cc = 0;
            int total;
            MovieNode *rt;
            rt = Mtree.getRoot();
            total = Mtree.countMovieNodes(rt, cc);
            cout << "Tree contains: " << total+1 << " movies." << endl;
            cin >> UserIn;

        }else if(UserIn == 6){
            menuOn = false;
        }
    }
}
