#include "fraction.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, Basics) {
        Fraction a = (Fraction) { 2, 3 },
                 b = (Fraction) { 4, 5 };
        EXPECT_EQ(add(a,b).num,22);
        EXPECT_EQ(add(a,b).den,15);
        EXPECT_EQ(multiply(a,b).num,8);
        EXPECT_EQ(multiply(a,b).den,15);
        Fraction c = (Fraction) { 21, 33 };
        EXPECT_EQ(reduce(c).num,7);
        EXPECT_EQ(reduce(c).den,11);
        Fraction d = (Fraction) { -21, 33 };
        EXPECT_EQ(reduce(d).num,-7);
        EXPECT_EQ(reduce(d).den,11);
        Fraction e = (Fraction) { 21 , -33};
        EXPECT_EQ(reduce(e).num , -7);
        EXPECT_EQ(reduce(e).den , 11);
        Fraction f = (Fraction) { -21 , -33};
        EXPECT_EQ(reduce(f).num , 7);
        EXPECT_EQ(reduce(f).den , 11);
        Fraction g = (Fraction) { 0 , -1};
        EXPECT_EQ(reduce(g).num , 0);
        EXPECT_EQ(reduce(g).den , 1);
        Fraction h = (Fraction) { 0 , 0};
        EXPECT_EQ(reduce(h).num , 0);
        EXPECT_EQ(reduce(h).den , 0);
        Fraction i = (Fraction) { -1 , 0};
        EXPECT_EQ(reduce(i).num ,1);
        EXPECT_EQ(reduce(i).den , 0);
    }

}
