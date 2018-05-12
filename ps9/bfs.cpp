#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#define INF 0xfafafafa

using namespace std;


struct vertex{
	char val;
	int dist;
	vertex *pred;
	bool v1;
	bool v2;
	vector<vertex*>adj_vertices;
};

struct tuple_ans{
	int d;
	int k;	
};

class graph{
public:
	vertex *vertices[10];
	graph(int a){
		num_vertices = a; 
	}
	int get_num_vertices(){
		return num_vertices;
	}
private:
	int num_vertices;
};

tuple_ans *BFS(graph G, vertex s, vertex t){
	for(int i=0; i<G.get_num_vertices(); i++){
		vertex *current;
		current = G.vertices[i];
		current->v1 = false;
		current->dist = INF;
		current->pred = NULL;
	}
	int countpop = 0;
	s.v1 = true;
	s.dist = 0;
	s.pred = NULL;

	queue<vertex> Q;
	Q.push(s);
	while(Q.size() != 0){
		vertex U = Q.front();
		U.v1 = true;
		Q.pop();
		countpop++;
		for(int j=0; j<(int)U.adj_vertices.size(); j++){
			vertex *cur = U.adj_vertices[j];
			if(cur->v1 == false){
				cur->v1 = true;
				cur->dist = U.dist + 1;
				if(cur->val == t.val){
					tuple_ans *answer = new tuple_ans();
					answer->d = cur->dist;
					answer->k = countpop;
					return answer;
				}else{
					Q.push(*cur);
				}
			}
		}
	}
	printf("no path!\n");
	return NULL;
}



int main(){
	vertex a,b,c,d,e,f; //test graph
	a.adj_vertices.push_back(&b);
	a.adj_vertices.push_back(&c);

	b.adj_vertices.push_back(&d);
	b.adj_vertices.push_back(&e);
	b.adj_vertices.push_back(&a);

	c.adj_vertices.push_back(&a);
	c.adj_vertices.push_back(&d);
	c.adj_vertices.push_back(&f);

	d.adj_vertices.push_back(&c);
	d.adj_vertices.push_back(&b);

	e.adj_vertices.push_back(&b);
	e.adj_vertices.push_back(&f);

	f.adj_vertices.push_back(&c);
	f.adj_vertices.push_back(&e);

	graph G(6);
	G.vertices[0] = &a;
	G.vertices[1] = &b;
	G.vertices[2] = &c;
	G.vertices[3] = &d;
	G.vertices[4] = &e;
	G.vertices[5] = &f;

	tuple_ans * my_ans = BFS(G, a, f); 
	if(my_ans)
		printf("distance: %d, k times popped from queue: %d\n", my_ans->d, my_ans->k);
	else{
		printf("error: BFS returned null\n");
	}


	return 0;
}