#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}
int find_gcd(int n1, int n2){
  int temp;
  while (n1 != 0){
    temp = n2 % n1;
    n2 = n1;
    n1 = temp;
  }
  return n2;
}


Fraction reduce (Fraction a){
  if (a.num == 0 && a.den == 0){
    return (Fraction) {a.num, a.den};
  }
  else if (a.den == 0 && a.num !=0){
    return (Fraction) {1 , a.den};
  }
  else if (a.den != 0 && a.num == 0){
    return (Fraction) {a.num, 1};
  }
  else {
  if (a.den > 0 && a.num > 0){
    int gcd = find_gcd (a.num, a.den);
    a.num = a.num / gcd;
    a.den = a.den / gcd; 
  return (Fraction) {a.num , a.den};
  }
  else if (a.den < 0 && a.num > 0){
    int m1 = (-1) * a.den;
    int gcd = find_gcd (a.num, m1);
    a.num = (-1) * (a.num / gcd);
    a.den = m1 / gcd; 
  return (Fraction) {a.num , a.den};
  }
  else if (a.den > 0 && a.num < 0){
    int m1 = (-1) * a.num;
    int gcd = find_gcd (m1, a.den);
    a.num = (-1) * (m1 / gcd);
    a.den = a.den / gcd;
    return (Fraction) {a.num , a.den}; 
  }
  else {
    int m1 = (-1) * a.den;
    int m2 = (-1) * a.num;
    int gcd = find_gcd (m2, m1);
    a.num = m2 / gcd;
    a.den = m1 / gcd; 
    return (Fraction) {a.num , a.den};
  }
  }
}