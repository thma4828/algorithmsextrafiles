#include <stdio.h>

int get_max_subarr(int A[6], int l, int r){
    if(l < r){
        int sum = 0;
        int max = 0;
        for(int i=l; i<r; i++){
            sum += A[i];
            if(sum > max){
                printf("maxsum: %d\n", sum);
                max = sum;
            }
        }
        int mid = (int) (l+r) /2;

        int max_left = get_max_subarr(A, l, mid);
        int max_right = get_max_subarr(A, mid+1, r);

        if(max_left >= max_right && max_left >= max)
            return max_left;
        if(max_right >= max_left && max_right >=max)
            return max_right;
        return max;
    }
    if(l==r){
        return A[l];
    }
    if(l > r)
        return 0;
}

int main(){

    int A[6] = {-1, -3, -5, -12, -1, 1};
    int m = get_max_subarr(A, 0, 6); ///should be 1?
    printf("%d", m);
    return m;
}
