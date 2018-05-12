#ifndef MOVIETREERB_H
#define MOVIETREERB_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct MovieNode{
    int ranking;
    string title;
    int year;
    int quantity;
    char color;
    bool isRed;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        // Now that we are using nil these NULL's should be overwritten in addMovieNode.
    	leftChild = NULL;
    	rightChild = NULL;
        parent = NULL;
        isRed = true;
    }

};

class MovieTreeRB
{

    public:
        bool isB;
        MovieTreeRB(bool i){
            nil = new MovieNode();
            nil->title = "Null";
            nil->color = 'B';
            nil->leftChild = NULL;
            nil->rightChild = NULL;
            isB = i;
        }
        //virtual ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        //void deleteMovieNode(string title);
        MovieNode* addMovieNode(int ranking, string title, int releaseYear, int quantity);
        void RedBlackInsert(int r1, string t1, int ry1, int q1);
        void findMovie(string title);
        void rentMovie(string title);
        void RBCase1Left(MovieNode *x, MovieNode *Uncle);
        void RBCase3Left(MovieNode *x);
        MovieNode* getRoot();
        bool isValid();
        int countLongestPath();
        void printMovieInventory(MovieNode * node);
        int rbValid(MovieNode * node); //check if the tree is valid, with node as the root of the tree
        int countMovieNodes(int c, MovieNode *node); //number of unique titles in the tree
        void rbDelete(MovieNode * z);
        void rbTransplant(MovieNode *u, MovieNode *v);
        MovieNode* TreeMin(MovieNode *X);
        MovieNode* TreeMax(MovieNode *Y);
        void rbDeleteFixup(MovieNode *C);
        MovieNode* searchMovieTree(MovieNode * node, string title);
        void RBCase3Right(MovieNode *y);
        void RBCase1Right(MovieNode *m, MovieNode *Uncle);
        void DeleteAll(MovieNode * node);
        MovieNode * getNil(){
            return nil;
        }
        //void rbBalance(MovieNode *P);

    protected:

    private:

        //void rbAddFixup(MovieNode * node); // called after insert to fix tree
        void leftRotate(MovieNode * x); //rotate the tree left with x as the root of the rotation
        void rightRotate(MovieNode * x); //rotate the tree right with x as the root of the rotation
        //int countLongestPath(MovieNode *node); //longest path from node to a leaf node in the tree

        MovieNode *root;
        MovieNode *nil;


};

#endif // MOVIETREE_H

