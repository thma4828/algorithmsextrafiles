#include <iostream>
#include <string>

using namespace std;

/***int *removeEvens(int *a, int length, int *oddsFound){
    int *odds = new int[*oddsFound];
    int counter = 0;
    for(int i=0; i<length; i++){
       if(a[i]%2 !=0){
            oddsFound[counter] = a[i];
            counter++;
       }
    }
    return odds;
}
***/
void myFunc(int **a){
    //empty
}

int main(){
    int A[] = {2, 4, 6, 8, 10};

    for(int i=2; i>0; i--){
        A[i] = A[i+2];
    }
    for(int j=0; j<5; j++){
        cout<<A[j]<<endl;
        }

    int b = 5;
    int *a2 = &b;

    int *a = new int;
    myFunc(&a);




}
