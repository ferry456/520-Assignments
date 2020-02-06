#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "gtest/gtest.h"
#include "complex.h"

namespace {
    /*
    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }
    
    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }
    
    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }
    
    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }
    */
    TEST(TypedArray, push_push_front){
        TypedArray<double> x;
        TypedArray<double> y;
        x.set(0,0);
        x.set(1,1);
        x.set(2,2);
        double m = 4;
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(x.push(m).get(3) , 4);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(x.push_front(m).get(0) , 4);
        std::cout << x << "\n";

    }
    
    TEST(TypedArray, pop_pop_front){
        TypedArray<double> x;
        x.set(0,0);
        x.set(1,1);
        x.set(2,2);
        double m = 4;
        EXPECT_DOUBLE_EQ(x.pop() , 2);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(x.pop_front() , 0);
        std::cout << x << "\n";
    }
    
    TEST(TypedArray, concat){
        TypedArray<double> x;
        TypedArray<double> y;
        TypedArray<double> z;
        x.set(0,0);
        x.set(1,1);
        x.set(2,2);
        y = x.concat(x).concat(x);
        //z = y.concat(x);
        std::cout << x << "\n";
        std::cout << x.size() << "\n";
        std::cout << y << "\n";
        std::cout << y.size() << "\n";
        //std::cout << z << "\n";
        EXPECT_DOUBLE_EQ(y.size() , 9);
        EXPECT_DOUBLE_EQ(y.get(5) , 2);
    }
    
    TEST(TypedArray, reverse){
        TypedArray<double> x;
        x.set(0,0);
        x.set(1,1);
        x.set(2,2);
        std::cout << x << "\n";
        std::cout << x.reverse() << "\n";
        EXPECT_DOUBLE_EQ(x.safe_get(0) , 2);
    }
    
    TEST(TypedArray, operator_1){
        TypedArray<double> x;
        TypedArray<double> y;
        x.set(0,0);
        x.set(1,1);
        x.set(2,2);
        y = x;
        std::cout << x << "\n";
        std::cout << y << "\n";
    }
    
    TEST(TypedArray, operator_2){
        TypedArray<double> x;
        TypedArray<double> y;
        x.set(0,0);
        x.set(1,1);
        x.set(2,2);
        y = x + x + x;
        std::cout << x << "\n";
        std::cout << y << "\n";
        EXPECT_DOUBLE_EQ(y.get(5) , x.get(2));
    }

    TEST(complex , real){
        EXPECT_DOUBLE_EQ(Complex(1 , 2).real() , 1);
        EXPECT_DOUBLE_EQ(Complex(2 , 3).real() , 2);
    }

    TEST(complex , imaginary){
        EXPECT_DOUBLE_EQ(Complex(3,3).imaginary() , 3);
        EXPECT_DOUBLE_EQ(Complex(4,-4).imaginary() , -4);
    }

    TEST(complex , operator_equal){
        ASSERT_EQ(Complex(1 , 1) , Complex(1 ,1));
    }

    TEST(complex, operator_mult){
        ASSERT_EQ(Complex(1 , 2) * Complex(2 ,3) , Complex(-4 , 7));
    }

    TEST(complex , operator_plus){
        ASSERT_EQ(Complex(1 , 1) + Complex(2 , 2) , Complex(3 , 3));
    }

    TEST(complex , complex_conjugate){
        EXPECT_DOUBLE_EQ(Complex(1 , 1).conjugate().real() , 1);
        EXPECT_DOUBLE_EQ(Complex(1 , 1).conjugate().imaginary() , -1);
    }


    
}