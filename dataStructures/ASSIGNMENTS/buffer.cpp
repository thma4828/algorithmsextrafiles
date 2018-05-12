#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;

int main(){
    //use const parameter for pointers for maximum protection
    //makes it a read only location being pointed to
    //char is constant
    const char * A;
    //it is now illegal to say
    *A = ' x';
    //but you could say
    const char *B;
    A = B;
    //with this declaration the pointer now may not be changed
    char* const C = new char;
    *C = 'X';
    //illegal to say
    C = B;
    //C is now a read only variable
    //the pointer is constant;

    //both are constant
    const char* const D = new char;
}
