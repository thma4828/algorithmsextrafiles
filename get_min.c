#include <stdio.h>

int get_min_k2(int A[10]){
	int i=0;
	int lf = 0;
	int rf = 0;
	int lmin, rmin;
	int mid = 10 >> 1;
	while((i < mid)&&( (!lf) || (!rf) )){
		if(A[i+1] > A[i]){
			lmin = A[i];
			lf = 1;	
		}
		if(A[mid + i + 1] > A[mid + i]){
			rmin = A[mid + i];
			rf = 1;
		}
		i = i + 1;
		
	}
	if(lf && rf){
		if(lmin < rmin)
			return lmin;
		return rmin;
	}
	return 0x7fffffff;
}



int main(){
	int a[10] = {10,9,8,20,30,-1,-2,-3,100,200};
	printf("\n%d\n", get_min_k2(a));
	return 0;

}
