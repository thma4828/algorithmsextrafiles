#include <stdio.h>
#include <stdlib.h>
#define S 100

int random_partition(int *A, int p, int r){
	int tmp;
	int x = A[r];
	int i = p-1;
	for(int j=p; j<r; j++){
		if(A[j] <= x){
			i = i + 1;
			tmp = A[j];
			A[j] = A[i];
			A[i] = tmp;
		}
	}
	tmp = A[r];
	A[r] = A[i+1];
	A[i+1] = tmp;
	return i+1;
}

int quick_sort(int *A, int p, int r){
	if(p < r){
		int q = random_partition(A, p, r);
		quick_sort(A, q+1, r);
		quick_sort(A, p, q-1);
	}
}

int *get_rand_array(){
	int *A = malloc(sizeof(int)*S);
	for(int i=0; i<S; i++){
		A[i] = rand() % 1000;
		printf(" %d\n ", A[i]);
	}
	return A;

}


int main(){
	int *A = get_rand_array();
	quick_sort(A, 0, S);
	for(int k=0; k<S; k++){
		printf("%d\n", A[k]);
	}
	return 0;
}
