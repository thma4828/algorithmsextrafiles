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
        MovieTreeRB(){
            nil = new MovieNode();
            nil->title = "Null";
        }
        virtual ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(string title);
        void addMovieNode(int ranking, string title, int releaseYear, int quantity);
        void RedBlackInsert(int r1, string t1, int ry1, int q1)
        void findMovie(string title);
        void rentMovie(string title);
        MovieNode* getRoot(){
            return root;
        }
        bool isValid();
        int countLongestPath();

    protected:

    private:
        void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void printMovieInventory(MovieNode * node);
        void rbAddFixup(MovieNode * node); // called after insert to fix tree
        void leftRotate(MovieNode * x); //rotate the tree left with x as the root of the rotation
        void rbDelete(MovieNode * z); //delete a node. Call this from deleteMovieNode, the actual delete functionality happens here.
        void rightRotate(MovieNode * x); //rotate the tree right with x as the root of the rotation
        void rbDeleteFixup(MovieNode * node); //called after delete to fix the tree
        void rbTransplant(MovieNode * u, MovieNode * v); //replace node u in tree with node v. Your solution doesn't necessarily need to use this method
        int rbValid(MovieNode * node); //check if the tree is valid, with node as the root of the tree
        int countMovieNodes(MovieNode *node); //number of unique titles in the tree
        int countLongestPath(MovieNode *node); //longest path from node to a leaf node in the tree
        MovieNode* searchMovieTree(MovieNode * node, string title);
        MovieNode *root;
        MovieNode *nil;


};

#endif // MOVIETREE_H

