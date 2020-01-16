#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */


typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complexes together
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add ( Complex a, Complex b );

/*! Multiply two complexes together 
 *  \param a The first complex
 *  \param b The second complex
 */
Complex multiply ( Complex a, Complex b );

Complex negate (Complex a);

double magnitude (Complex a);



#endif