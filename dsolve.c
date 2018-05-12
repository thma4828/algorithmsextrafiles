#include <stdio.h>

int get_max_subarr(int A[10], int l, int r){
    if(l < r){
        int sum=0;
        int max = 0;
        for(int i=l; i<r; i++){
            sum += A[l];
            if(sum > max){
                max = sum;
            }
        }
        int mid = (l+r) /2;
        int max_left = get_max_subarr(A, l, mid);
        int max_right = get_max_subarr(A, mid, r);
        if(max_left > max_right){
            if(max > max_left)
                return max;
            if(max <= max_left)
                return max_left;
        }
        if(max_right > max_left){
            if(max_right > max)
                return max_right;
            if(max_right <= max)
                return max;
        }
        if(max_right == max_left){
            if(max > max_right)
                return max
            return max_right;
        }
    }
    if(l==r){
        return A[l];
    }
    if(l > r)
        return 0;
}


int main(){
    int A[10]= {5,6,10,-1,3,56,7,1,2,10};
    int B[10][10];

    int sum = 0;
    for(int i=0; i<10; i++){
        sum += A[i];
        B[0][i] = sum;
    }
    for(int j=1; j<10; j++){
        for(int k=j+1; k<10; k++){
            B[j][k] = B[j-1][k] - A[j-1];
        }
    }

    return 0;
}
