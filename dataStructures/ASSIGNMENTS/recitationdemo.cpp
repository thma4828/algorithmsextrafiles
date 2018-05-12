#include <iostream>

using namespace std;

const int SIZE = 4;

void InsertionSort(int A[]){
    int index, j;
    for(int i=1; i<SIZE; i++){
        index = A[i];
        j = i;
        while((j>0) && (A[j-1] > index)){
            A[j] = A[j-1];
            j = j-1;
        }
        A[j] = index;
    }

}

int main(){

    int A[SIZE] = {2, 4, 3, 1};

    InsertionSort(A);




}
