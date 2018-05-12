#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    int num_points = 11;
    int change_in_x = 1;
    int leftSum=0;
    int rightSum=0;
    int *f_of_x = new int[num_points];
    for(int z=0; z<num_points; z++){
        f_of_x[z] = z*3;
        cout << f_of_x[z] << endl;
    }
    //left endpoints =
    int *leftEndpoints = new int[num_points -1];
    int *rightEndpoints = new int[num_points -1];
    float *midPoints = new float[num_points];
    for(int l=0; l<num_points-1; l++){
        leftEndpoints[l] = f_of_x[l];
        leftSum = leftSum + f_of_x[l];
    }

    for(int r=1; r<num_points; r++){
        rightEndpoints[r-1] = f_of_x[r];
        rightSum = rightSum + f_of_x[r];
    }
    float MidVal1, MidVal2;
    float midSum = 0;
    float midTemp;
    for(int m=0; m<num_points -1; m++){
        MidVal1 = ((float)leftEndpoints[m]);
        MidVal2 = ((float)leftEndpoints[m + 1]);
        midTemp = (MidVal1 + MidVal2) / 2;
        midPoints[m] = midTemp;
        cout << "midTemp = " << midTemp << endl;
        midSum = midSum + midTemp;
    }
    leftSum = leftSum * change_in_x;
    rightSum = rightSum * change_in_x;
    cout << "for the function f(x) = 3x, 0<=x<=10, x' = 1" << endl;
    cout << "The leftSum = " << leftSum << endl;
    cout << "The rightSum = " << rightSum << endl;
    cout << "The midSum = " << midSum << endl;

    return 0;
}
