#include <stdio.h>
#include <stdlib.h>
#define PMAX 50
/*program to print the first n non-zero pell numbers*/
int main(int argc, char **argv){
	if(argc != 2){
		printf("usage: ./pell <unsigned int < 50\n>");
		return 0;
	}
	int n = atoi(argv[1]);
	if(n >= PMAX){
		n = PMAX;
		printf("note: only first 50 pell numbers will be printed, n set to PMAX\n");
	}
	unsigned long pelln[PMAX];
	int i;
	pelln[0] = 0;
	pelln[1] = 1;
	for(i=2; i<PMAX; i++){
		pelln[i] = ((pelln[i-1]) << 1) + pelln[i-2];
	}
	for(int j=0; j<n; j++){
		printf("%lu\n", pelln[j]);
	}
	return 0;
	
}
