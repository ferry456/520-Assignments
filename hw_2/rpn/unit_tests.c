#include "gtest/gtest.h"
#include "rpn.h"

namespace {

    TEST(HW2,RPN_BASICS) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_push(1.0);
        rpn_add();
        rpn_multiply();
        rpn_negate();
        ASSERT_EQ(rpn_pop(),-1.5);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_ERRORS) {
        
        rpn_push(0.5);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_pop();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_add();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_multiply();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_negate();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);                                
        rpn_free();

        rpn_init();
        rpn_pop();
        ASSERT_EQ(rpn_error(), POP_ERROR);
        rpn_free();

        rpn_init();
        rpn_negate();
        ASSERT_EQ(rpn_error(), UNARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_add();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_multiply();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);  
        rpn_free();

        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(DBL_MAX);
        rpn_add();
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1.0);
        rpn_push(3.0);
        rpn_div();
        ASSERT_EQ(rpn_pop(), 1.0/3.0);
        rpn_free(); 

        rpn_init();
        rpn_push(0);
        rpn_push(1);
        rpn_div();
        ASSERT_EQ(rpn_error(), DIVIDE_BY_ZERO_ERROR);
        rpn_free();

        rpn_init();
        for (double i = 0.0; i < 180.0; i++){
            rpn_push(i);
        }
        rpn_pop();
        rpn_div();
        ASSERT_EQ(rpn_pop(),177.0/178.0);
        rpn_free();       

    }    

}
