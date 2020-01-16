#include<math.h>
#include "complex.h"

Complex add (Complex a , Complex b){
    return (Complex) {a.real + b.real , a.im + b.im};
}

Complex multiply (Complex a , Complex b){
    return (Complex) {a.real * b.real - a.im * b.im , a.im * b.real + a.real * b.im};
}

double magnitude (Complex a){
    return sqrt(a.real * a.real + a.im * a.im);
}

Complex negate (Complex a){
    return (Complex) {(-1) * a.real , (-1) * a.im};
}
