#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>
#include<queue>

using namespace std;

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
    bool visited;
};

struct vertex{
    int ID;
    string name;
    int district;
    bool visited;
    bool solved;
    int distance;
    vector<adjVertex> adj;
    vertex *parent;
    vertex(){
        parent = NULL;
    }
};

struct queueVertex{
    int distance;
    vector<vertex *> path;
};

class Graph
{
    public:
        Graph(bool IT){
            IniT = IT;
        }
        ~Graph(){
            IniT = false;
        }
        void setALLVisistedFalse();
        void addEdge(string v1, string v2, int weight);
        void addVertex(string name);
        void displayEdges();
        void assignDistricts();
        void BFTraversalLabel(string v, int i);
        vertex * BFSL(string sv, string ev);
        vertex * BFTsearch(string startVal, string endVal);
        int DFS(vertex *V, int d);
        void Dijkstra(string startingCity,string endingCity);
        void printGraph();
        void ReadFileIn(string fName);
        vertex Search(string value);
        vector<vertex> getVertices(){
            return vertices;
        }
        vertex * findVertex(string name);
        bool isEdgeAdded(string v1, string v2);
        vector <string> CNAMES;
    private:
        vector<vertex> vertices;
        queue<vertex> BFTqueue;
        bool IniT;
        string *Cnames;
        int numCities;
};

#endif // GRAPH_H

