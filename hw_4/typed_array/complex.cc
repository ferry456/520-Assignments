#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

Complex Complex::operator+(const Complex& b) {
    double c = real() + b.real();
    double d = imaginary() + b.imaginary();
    Complex m = Complex(c , d);
    return m;
}

Complex Complex::operator*(const Complex& b) {
    double c = real() * b.real() - b.imaginary() * imaginary();
    double d = real() * b.imaginary() + b.real() * imaginary();
    Complex m = Complex(c , d);
    return m;
}

bool Complex::operator==(const Complex& a , const Complex& b){
    if (a.real() == b.real() && a.imaginary() == b.imaginary()){
        return ture;
    }else{
        return false;
    }
}

double Complex::real() const {
    return re;
}

double Complex::imaginary() const {
    return im;
}

Complex Complex::cojugate() const {
    Complex a = Complex(re, -im);
    return a;
}