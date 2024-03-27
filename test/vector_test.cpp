#include <cstdlib>
#include <initializer_list>
#include <gtest/gtest.h>

#define private public
#include "../include/vector.h"

TEST(Vector_Construct, Empty) {
    Vector v;
    const int n = 3;
    
    ASSERT_EQ(v.get_dimension(), n);
    for(int i = 0; i < n; ++i){
        ASSERT_EQ(v.data[i], 0);
    }
}

TEST(Vector_Construct, N_dimension) {
    for(int i = 0; i < 100; ++i){
        Vector v(i);
        ASSERT_EQ(v.get_dimension(), i);
        for(int j = 0; j < i; ++j){
            ASSERT_EQ(v.data[j], 0);
        }
    }
}

TEST(Vector_Construct, Initializer_list) {
    std::initializer_list<int> l = {1, 2, 3, 4, 5, 6};
    
    Vector v(l);

    ASSERT_EQ(l.size(), v.get_dimension());
    
    auto el = l.begin();
    for(std::size_t i = 0; i < v.get_dimension(); ++i){
        ASSERT_EQ(v.data[i], *el);
        ++el;
    }
}

TEST(Vector_Construct, Copy) {
    Vector v1{-1, 0, 1, 303, 4};
    Vector v2(v1);

    ASSERT_EQ(v1, v2);
}


TEST(Arithmetical, Plus) {
    Vector v1{0, 0, 0};
    Vector v2{0, 0, 0};
    Vector v3(4);
    Vector v_tmp(3);

    ASSERT_THROW(v1+v3, vector_dimension_exception);

    v_tmp = v1+v2;
    ASSERT_EQ(v1+v2, v_tmp);
    v1 += v2;
    ASSERT_EQ(v1, v_tmp);


    v1 = Vector{1, 2, 3, 4};
    v2 = Vector{4, 3, 2, 1};
    v3 = Vector{5, 5, 5, 5};

    ASSERT_EQ(v1+v2, v3);
}

TEST(Arithmetical, Minus) {
    Vector v1{0, 0, 0};
    Vector v2{0, 0, 0};
    Vector v3(4);
    Vector v_tmp(3);

    ASSERT_THROW(v1-v3, vector_dimension_exception);

    v_tmp = v1-v2;
    ASSERT_EQ(v1-v2, v_tmp);
    v1 -= v2;
    ASSERT_EQ(v1, v_tmp);

    v1 = Vector{1, 2, 3, 4};
    v2 = Vector{4, 3, 2, 1};
    v3 = Vector{-3, -1, 1, 3};

    ASSERT_EQ(v1-v2, v3);
}

TEST(Arithmetical, Multiplication) {
    Vector v1{0, 0, 0};
    Vector v2{0, 0, 0};
    Vector v3(4);
    Vector v_tmp(3);

    ASSERT_THROW(v1*v3, vector_dimension_exception);

    v_tmp = v1*v2;
    ASSERT_EQ(v1*v2, v_tmp);
    v1 *= v2;
    ASSERT_EQ(v1, v_tmp);

    v1 = Vector{1, 2, 3, 4};
    v2 = Vector{4, 3, 2, 1};
    v3 = Vector{4, 6, 6, 4};

    ASSERT_EQ(v1*v2, v3);
}

TEST(Arithmetical, Division) {
    Vector v1{0, 0, 0};
    Vector v2{0, 0, 0};
    Vector v3(4);

    ASSERT_THROW(v1/v3, vector_dimension_exception);

    v1 = Vector{18, 18, 6, 2};
    v2 = Vector{1, 9, 2, 2};
    v3 = Vector{18, 2, 3, 1};

    ASSERT_EQ(v1/v2, v3);

    v1 /= v2;
    ASSERT_EQ(v1, v3);
}
