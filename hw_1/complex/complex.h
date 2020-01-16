#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Fraction object and method definitions
 *
 *  A fraction object is a struct with a numerator, denoted num, and
 *  a denominator, denoted den. Varions Methods that take fractions and return 
 *  fractions do arithmetical operations on them.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two fractions together
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add ( Complex a, Complex b );

/*! Multiply two fractions together (does not reduce)
 *  \param a The first term
 *  \param b The second term
 */
Complex multiply ( Complex a, Complex b );

Complex negate (Complex a);

double magnitude (Complex a);



#endif