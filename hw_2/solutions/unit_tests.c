#include "gtest/gtest.h"
#include "solutions.h"

namespace {
      
    TEST(Example,TestAddOne) {
        ASSERT_EQ(add_one(0),1);
    }


    
    TEST(HW2,Running_Total) {
        ASSERT_EQ(Running_Total(1),  1);
        ASSERT_EQ(Running_Total(1),  2);
        ASSERT_EQ(Running_Total(5),  7);
        ASSERT_EQ(Running_Total(-3), 4);      
    }

    TEST(HW2,Reverse_in_place) {
        int x[] = {10,20,30,40,50};
        Reverse_in_place(x,5);
        ASSERT_EQ(x[0],50);
        ASSERT_EQ(x[1],40);       
        ASSERT_EQ(x[2],30);   
        ASSERT_EQ(x[3],20);   
        ASSERT_EQ(x[4],10);                            
    }

    TEST(HW2,Reverse) {
        int x[] = {10,20,30,40,50};
        int * y = Reverse(x,5);
        ASSERT_EQ(y[0],50);
        ASSERT_EQ(y[1],40);       
        ASSERT_EQ(y[2],30);   
        ASSERT_EQ(y[3],20);   
        ASSERT_EQ(y[4],10);  
        free(y);
    }

    TEST(HW2,num_instances) {
        int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
        ASSERT_EQ(num_instance(a,10,1), 3);
    }

    Point negate(Point p) {
        return { -p.x, -p.y, -p.z };
    }
    TEST(HW2,map) {
        Point a[] = { { 1,2,3 }, { 2,3,4 } };
        Point * b = map (a,2,negate);
        for(int i=0; i<2; i++) {
            ASSERT_EQ(b[i].x,-a[i].x);
            ASSERT_EQ(b[i].y,-a[i].y);
            ASSERT_EQ(b[i].z,-a[i].z);
        }
        free(b);
    }   
}
