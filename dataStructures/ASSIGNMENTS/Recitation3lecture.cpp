#include <iostream>

using namespace std;

int main(){
    int sizeData = 10;

    int *dynamicData = new int[sizeData];
    int *dynamicData2 = new int[sizeData*2];

    for(int x=0; x<sizeData/2; x++){
        dynamicData2[x] = dynamicData[x];
    }

    delete []dynamicData;
    dynamicData = dynamicData2;

    for(int i=0; i<sizeData; i++){
        cout << dynamicData[i] << endl;
    }




}
