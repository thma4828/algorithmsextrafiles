#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include "Graph.h"

using namespace std;

void Graph::setALLVisistedFalse(){
    for(int m=0; m<vertices.size(); m++){
        vertices[m].visited = false;
    }
}

vertex Graph::Search(string V){
    vertex T;
    T.name = "NIL";
    for(int x=0; x<vertices.size(); x++){
        if(vertices[x].name == V){
            return vertices[x];
        }
    }
    return T;
}

void Graph::addVertex(string value){
    if(vertices.size() != 0){
        bool found = false;
        for(int x=0; x < vertices.size(); x++){
            if(vertices[x].name == value){
                found = true;
                break;
            }

        }
        if(!found){
                vertex v;
                v.name = value;
                v.visited = false;
                v.district = -1;
                vertices.push_back(v);
        }
    }else{
        vertex c;
        c.name = value;
        c.visited = false;
        c.district = -1;
        vertices.push_back(c);
    }
}

bool Graph::isEdgeAdded(string v1, string v2)
{
    vertex X;
    X = Search(v1);
    vertex Y;
    Y = Search(v2);
    for(int m=0; m<X.adj.size(); m++){
        if(X.adj[m].v->name == v2){
            return true;
        }
    }
    return false;
}
void Graph::addEdge(string v1, string v2, int weight){
    for(int x=0; x<vertices.size(); x++){
        if(vertices[x].name == v1){
            for(int y=0; y<vertices.size(); y++){
                if((vertices[y].name == v2) && (x != y)){
                    adjVertex av;
                    av.v = &vertices[y];
                    av.weight = weight;
                    vertices[x].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::printGraph(){
    for(int x=0; x<vertices.size(); x++){
        cout << vertices[x].district << ":" << vertices[x].name << "-->";
        for(int y=0; y<vertices[x].adj.size(); y++){
            cout << vertices[x].adj[y].v->name;
            if(y != vertices[x].adj.size()-1)
                cout << "***";
        }
        cout << endl;
    }
}

void Graph::ReadFileIn(string Fname){
    ifstream t_in;
    t_in.open(Fname);
    string line, token;
    vector <string> CityData;
    int line_CNT = 0;
    string CITY;
    int cn = 0;
    while(getline(t_in, line)){
        if(line[0] != ' '){
            istringstream ss(line);
            while(getline(ss, token, ',')){
                CityData.push_back(token);
            }
            if(line_CNT == 0){
                numCities = CityData.size()-1;
                for(int k=1; k<CityData.size(); k++){
                    addVertex(CityData.at(k));
                    CNAMES.push_back(CityData.at(k));
                }
            }else if(line_CNT > 0){
                CITY = CityData.at(0);
                for(int m=0; m<CityData.size(); m++){
                    if(m != 0){
                        string C = CityData.at(m);
                        int I = stoi(C);
                        if(I == 0){
                            //destroyed
                        }
                        else if(I == -1){
                            //empty
                        }
                        else{
                            if(!isEdgeAdded(CITY, CNAMES.at(m-1))){
                                addEdge(CITY, CNAMES.at(m-1), I);
                            }

                        }
                    }

                }

            }
            line_CNT++;
            CityData.clear();

        }
    }

}

void Graph::BFTraversalLabel(string value, int DNum){
    vertex V;
    V = Search(value);
    V.visited = true;
    BFTqueue.push(V);
    vertex N;
    while(!BFTqueue.empty()){
        N = BFTqueue.front();
        for(int x=0; x<N.adj.size(); x++){
            if(!N.adj[x].v->visited){
                N.adj[x].v->visited = true;
                N.adj[x].v->district = DNum;
                BFTqueue.push(*N.adj[x].v);
            }

        }
        BFTqueue.pop();
    }
    for(int i=0; i<BFTqueue.size(); i++){
        BFTqueue.pop();
    }
}

vertex * Graph::BFSL(string startV, string endV){
    vertex S;
    vertex E;
    vertex N;

    S = Search(startV);
    E = Search(endV);

    S.distance = 0;
    S.visited = true;

    cout << S.name << ",";

    BFTqueue.push(S);
    while(!BFTqueue.empty()){
        N = BFTqueue.front();
        BFTqueue.pop();
        //cout << "N.adj.size == " << N.adj.size() << endl;
        for(int x=0; x<N.adj.size(); x++){
            if(N.adj.size() == 1)
                cout << N.adj[0].v->name << ",";
            //cout << "FOR LOOP AT X: " << x << endl;
            if(!N.adj[x].v->visited){
                N.adj[x].v->distance = N.distance + 1;
                if(N.adj[x].v->name == endV){
                    cout << N.name << "," << endV << endl;
                    //cout << "N.ADJ[x].v->name == " << N.adj[x].v->name << endl;
                    for(int i=0; i<BFTqueue.size(); i++){
                        BFTqueue.pop();
                    }
                    setALLVisistedFalse();
                    return N.adj[x].v;
                }else{
                    N.adj[x].v->visited = true;
                    //cout << "PUSHING: " << N.adj[x].v->name << "ONTO BFT QUEUE AT X == "<< x << endl;
                    BFTqueue.push(*N.adj[x].v);
                }
            }else{
                //cout << "N.adj[x].v->visited == true" << endl;
            }

        }
    }
    for(int i=0; i<BFTqueue.size(); i++){
        BFTqueue.pop();
    }
    setALLVisistedFalse();

    return NULL;
}

vertex * Graph::BFTsearch(string startV, string endV){
    vertex S;
    vertex E;
    vertex N;

    S = Search(startV);
    E = Search(endV);

    if(S.name == "NIL" || E.name == "NIL"){
        cout << "One or more cities doesn't exist" << endl;
        return NULL;
    }
    if(S.district == -1 || E.district == -1){
        cout << "Please identify the districts before checking distances" << endl;
        return NULL;
    }
    if(S.district != E.district){
        cout << "No safe path between cities" << endl;
        return NULL;
    }

    S.distance = 0;
    S.visited = true;

    BFTqueue.push(S);
    while(!BFTqueue.empty()){
        N = BFTqueue.front();
        BFTqueue.pop();
        //cout << "N.adj.size == " << N.adj.size() << endl;
        for(int x=0; x<N.adj.size(); x++){
            //cout << "FOR LOOP AT X: " << x << endl;
            if(!N.adj[x].v->visited){
                N.adj[x].v->distance = N.distance + 1;
                if(N.adj[x].v->name == endV){
                    //cout << "N.ADJ[x].v->name == " << N.adj[x].v->name << endl;
                    for(int i=0; i<BFTqueue.size(); i++){
                        BFTqueue.pop();
                    }
                    setALLVisistedFalse();
                    return N.adj[x].v;
                }else{
                    N.adj[x].v->visited = true;
                    //cout << "PUSHING: " << N.adj[x].v->name << "ONTO BFT QUEUE AT X == "<< x << endl;
                    BFTqueue.push(*N.adj[x].v);
                }
            }else{
                //cout << "N.adj[x].v->visited == true" << endl;
            }

        }
    }
    for(int i=0; i<BFTqueue.size(); i++){
        BFTqueue.pop();
    }
    setALLVisistedFalse();

    return NULL;
}

void PrintMenu(){
    cout << "1. Print vertices" << endl;
    cout << "2. Find districts" << endl;
    cout << "3. Find shortest path" << endl;
    cout << "4. Quit" << endl;
}

int main(){
    Graph G1(true);
    string fileN = "zombieCities.txt";
    G1.ReadFileIn(fileN);
    PrintMenu();
    int US;
    cin >> US;
    bool menuON = true;
    while(menuON){
        if(US == 1){
            G1.printGraph();
            cin >> US;
        }
        else if(US == 2){
            int k, cc;
            cc = 1;
            for(k=0; k<G1.CNAMES.size(); k++){
                vertex M = G1.Search(G1.CNAMES[k]);
                if(!M.visited){
                    G1.BFTraversalLabel(G1.CNAMES[k], cc);
                    cc++;
                }
            }

            G1.setALLVisistedFalse();
            cin >> US;
        }
        else if(US == 3){
            cin.ignore();
            string s1, s2;
            cout << "Enter a starting city:" << endl;
            getline(cin, s1);
            cout << "Enter an ending city:" << endl;
            getline(cin, s2);
            vertex *N = G1.BFTsearch(s1, s2);
            if(N != NULL){
                cout << N->distance;
                cout << ",";
                if(N->distance == 1)
                    cout << s1 << "," << s2 << endl;
                else
                    G1.BFSL(s1, s2);
            }else{
                //
            }
            cin >> US;
        }
        else if(US == 4){
            cout << "Goodbye!" << endl;
            menuON = false;
        }
        else{
            cin >> US;
        }

    }
    return 0;
}

