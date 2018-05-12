#include <stdio.h>
#include <stdlib.h>
#define NX 5
#define NY 5
#define INDEL 1
#define SUB 12
#define SWAP 13

int sub = SUB;
int swap = SWAP;
int Array[NX * NY];

int tcost = 0;

int min(int a, int b, int c, int d){
	int m = a;
	if(b<=m)
		m=b;
	if(c<=m)
		m=c;
	if(d<=m)
		m=d;
	return m;
}

int cost(int i, int j){
	if(i>=2 && j>=2){
		return min(cost(i-2, j-2) + SWAP, cost(i-1, j-1) + SUB, cost(i-1, j) + INDEL, cost(i, j-1) + INDEL);
	}else if(i>=1 && j>=1){
		return min(cost(i-1, j-1) + SUB, cost(i-1, j) + INDEL, cost(i, j-1) + INDEL, 1000);
	}else if(i==0 && j>0){
		return(cost(i, j-1) + INDEL);
	}else if(i>0 && j==0){
		return(cost(i-1, j) + INDEL);
	}else if(i==0 && j==0){
		return swap; //base case
	}
	
}

void align_strings(int S[NX][NY], char *x, char *y){
	int i, j;
	printf("in align strings\n");
	S[0][0] = sub; 
	for(i=1; i<NX; i++){
		printf("\n---\n");
		for(j=1; j<NY; j++){
			S[i][j] = cost(i, j);
			printf("S[%d][%d]: %d\n", i, j, S[i][j]);
		}
	}
}

void extract_alignment(int S[NX][NY], char *x, char *y){
	//Array[] is initialized as global Array[NX * NY]
	i = NX;
	j = NY;
	while(i || j){
		Array[i] = detOptOp()
		int a[2];
		updateIndices(S, i, j, Array, a);
		i = a[0];
		j = a[1];
	}
	//return is Array modified global state
}


commonSubstrings(int S[NX][NY], char *x, int L, char *y){ //5th param is global variable Array
	int i=1;
	int done = 0;
	char**commonSub == malloc(8 * NX * NY);
	int k=0;
	while(!done && i<L){
		x = edit(x, y, Array[i]);
		i++;
		if(strncmp(x, y == 0)){
			commonSub[k] = x;
			k++;
		}
	}
}
int main(){
	int S[NX][NY];
	char *x = malloc(NX);
	char *y = malloc(NY);
	align_strings(S, x, y);

}