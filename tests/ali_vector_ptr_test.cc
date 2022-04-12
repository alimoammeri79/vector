#include "ali_vector.h"
#include <cctype>
#include <gtest/gtest.h>

struct T {
    int x;

    T(const int input) : x(input)
    {}
};

constexpr std::size_t size {10};
constexpr std::size_t capacity {size*2};

TEST(VectorTest, DefaultConstructor) {
    ali::vector<T> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, Constructors) {
    ali::vector<T> v(size);
    EXPECT_EQ(v.size(), size);
    EXPECT_EQ(v.capacity(), capacity);

    ali::vector<T> v2(size, 6);
    EXPECT_EQ(v2.size(), size);
    EXPECT_EQ(v2.capacity(), capacity);
    EXPECT_EQ(v2[5].x, 6);

    ali::vector<T> v3{1, 2 ,3 ,4};
    EXPECT_EQ(v3.size(), 4);
    EXPECT_EQ(v3[1].x, 2);
}

TEST(VectorTest, CopyConstructor) {
    ali::vector<int> v{1, 2, 3};
    ali::vector<int> v2{v};
    EXPECT_EQ(v == v2, true);
}

TEST(VectorTest, MoveConstructor) {
    ali::vector<T> v{1, 2, 3};
    ali::vector<T> v2{std::move(v)};
    EXPECT_EQ(v.empty(), true);
    EXPECT_EQ(v2[1].x, 2);
}

TEST(VectorTest, Clear) {
    ali::vector<T> v{1, 2, 3};
    v.clear();
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, PushBack) {
    ali::vector<T> v{1, 2, 3};
    v.push_back(T{4});
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[3].x, 4);
}

TEST(VectorTest, PopBack) {
    ali::vector<T> v{1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
}

TEST(VectorTest, Empty) {
    ali::vector<T> v{1, 2, 3};
    ali::vector<T> v2;
    EXPECT_EQ(v.empty(), false);
    EXPECT_EQ(v2.empty(), true);
}

TEST(VectorTest, Assigment) {
    ali::vector<T> v{1, 2, 3};
    ali::vector<T> v2;
    v2 = v;
    for(std::size_t i{0}; i < v.size(); ++i)
        EXPECT_EQ(v[i].x, v2[i].x);
}

TEST(VectorTest, MoveAssigment) {
    ali::vector<T> v{1, 2, 3};
    ali::vector<T> v2{v};
    ali::vector<T> v3;
    v3 = std::move(v);
    
    for(std::size_t i{0}; i < v3.size(); ++i)
        EXPECT_EQ(v3[i].x, v2[i].x);

    EXPECT_EQ(v.empty(), true);
}

TEST(VectorTest, ConstDerefence) {
    const ali::vector<T> v{1, 2, 3};
    EXPECT_EQ(v[2].x, 3);
}

