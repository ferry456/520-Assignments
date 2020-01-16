#include<math.h>
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, Basics) {
        Complex a = (Complex) { 2, 3 },
                 b = (Complex) { 4, 5 };
        EXPECT_EQ(add(a,b).real,6);
        EXPECT_EQ(add(a,b).im,8);
        EXPECT_EQ(multiply(a,b).real,-7);
        EXPECT_EQ(multiply(a,b).im,22);
        EXPECT_EQ(magnitude(a) , sqrt(13));
        EXPECT_EQ(negate(a).real,-2);
        EXPECT_EQ(negate(b).real,-4);
        EXPECT_EQ(negate(a).im,-3);
        EXPECT_EQ(negate(b).im,-5);
        Complex c = (Complex) {-5 , 6},
                d = (Complex) {4 , -2};
        EXPECT_EQ(add(c,d).real,-1);
        EXPECT_EQ(add(c,d).im,4);
        EXPECT_EQ(multiply(c,d).real,-8);
        EXPECT_EQ(multiply(c,d).im,34);
        EXPECT_EQ(magnitude(c),sqrt(61));
        EXPECT_EQ(magnitude(d),sqrt(20));
        EXPECT_EQ(negate(c).real,5);
        EXPECT_EQ(negate(d).real,-4);
        EXPECT_EQ(negate(c).im,-6);
        EXPECT_EQ(negate(d).im,2);

    }

}
