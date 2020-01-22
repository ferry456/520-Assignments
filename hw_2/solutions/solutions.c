#include "example.h"

int rt = 0;
int add_one(int x) { 
    return x+1;
}

int Running_Total(int x){
    return rt = rt + x;
}

int Reverse_In_Place(int x[] , int y){
    //int len = sizeof(x) / sizeof(x[0]);
    int len = y;
    if (x[0] == NULL){
        return x[];
    } else {
    for (int cur = 0; cur < len/2; cur++){
        int temp = x[cur];
        x[cur] = x[len - 1 - cur];
        x[len - 1 - cur] = temp;
        }
    return int x[];
    }
}

int Reverse(int x[] , int z){
    int *y;
    y = (int*)calloc(z , sizeof(x[]));
    for (i = 0; i <= z ; i++){
        y[i] = x[z - 1 - i];
    }
    return int *y;
}

