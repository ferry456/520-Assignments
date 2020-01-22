#include "solutions.h"
#include <stdio.h>

int rt = 0;
int add_one(int x) { 
    return x+1;
}

int Running_Total(int x){
    return rt = rt + x;
}

void Reverse_in_place(int x[] , int size){
    for (int cur = 0; cur < size/2; cur++){
        int temp = x[cur];
        x[cur] = x[size - 1 - cur];
        x[size - 1 - cur] = temp;
    }
}

int *Reverse(int x[] , int size){
    int *y;
    y = (int*)calloc(size , sizeof(int));
    for (int i = 0; i <= size; i++){
        y[i] = x[size - 1 - i];
    }
    return y;
}

int num_instance(int x[] , int size , int y){
    int count = 0;
    for(int i = 0; i <= size - 1; i++){
        if (x[i] == y){
            count++;
        }
    }
    return count;    
}

Point * map(Point x[] , int size , Point (*func) (Point)){
    Point *b;
    b = (Point*)calloc(size , sizeof(Point));
    for (int i = 0; i < size; i++){
        b[i] = func(x[i]);
    }
    return b;
}