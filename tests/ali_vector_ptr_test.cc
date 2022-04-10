#include "ali_vector.h"
#include <cctype>
#include <gtest/gtest.h>

TEST(VectorTest, DefaultConstructor) {
    ali::vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, Constructor) {
    ali::vector<int> v(10);
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v[5], 0);

    ali::vector<int> v2(10, 6);
    EXPECT_EQ(v2.size(), 10);
    EXPECT_EQ(v2[5], 6);

    ali::vector<int> v3{1, 2 ,3 ,4};
    EXPECT_EQ(v3.size(), 4);
    EXPECT_EQ(v3[1], 2);
}

TEST(VectorTest, CopyConstructor) {
    ali::vector<int> v{1, 2, 3};
    ali::vector<int> v2{v};
    
    EXPECT_EQ(v == v2, true);
}

TEST(VectorTest, Clear) {
    ali::vector<int> v{1, 2, 3};
    v.clear();
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, PushBack) {
    ali::vector<int> v{1, 2, 3};
    v.push_back(4);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, PopBack) {
    ali::vector<int> v{1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
}

TEST(VectorTest, Empty) {
    ali::vector<int> v{1, 2, 3};
    ali::vector<int> v2;
    EXPECT_EQ(v.empty(), false);
    EXPECT_EQ(v2.empty(), true);
}

