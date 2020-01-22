#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>

int add_one(int x);

int Running_Total(int x);

void Reverse_in_place(int x[] , int size);

int *Reverse(int x[] , int size);

int num_instance(int x[] , int size , int y);

typedef struct {
   double x, y, z;
 } Point;

Point * map(Point x[] , int size , Point (*func)(Point));

#endif