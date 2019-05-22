// Copyright 2019 govyadkin <mgovyadkin@gmail.com>

#include <gtest/gtest.h>

#include <polynomial.hpp>

TEST(Polinom, ConstructAssign) {
    const std::vector<int> v{ 7, 6, 5, 4, 3, 2, 1, 0 };
    Polinom<int> a(v);

    EXPECT_EQ(v[0], a[7]);
    EXPECT_EQ(v[7], a[0]);

    Polinom<int> d(2);
    d[0] = 6;
    d[1] = 1;

    ASSERT_EQ(d.Degree(), 1);
    EXPECT_EQ(d[0], 6);
    EXPECT_EQ(d[1], 1);
    EXPECT_FALSE(d == a);

    Polinom<int> e(a);

    ASSERT_EQ(d.Degree(), 1);
    EXPECT_EQ(e, a);

    d[0] = d[1] = 3;

    EXPECT_EQ(d[0], 3);
    EXPECT_EQ(d[1], 3);
}

TEST(Polinom, Append) {
    Polinom<int> a(2);
    a[0] = 6;
    a[1] = 1;
    Polinom<int> b(a);
    b += a;

    EXPECT_EQ(b[0], 12);
    EXPECT_EQ(b[1], 2);

    Polinom<int> c = a + b;

    EXPECT_EQ(c[0], 18);
    EXPECT_EQ(c[1], 3);
    EXPECT_FALSE(b == c);
}

TEST(Polinom, Mult) {
    std::vector<int> v{ 2, 1, 0 };
    Polinom<int> a;
    Polinom<int> c(v);
    c *= a;

    EXPECT_EQ(a, c);

    Polinom<int> b(v);
    a = b * 5;
    b *= 5;

    EXPECT_EQ(b[0], 0);
    EXPECT_EQ(b[2], 10);
    EXPECT_EQ(b[0], a[0]);
    EXPECT_EQ(b[2], a[2]);

    a *= b;

    ASSERT_EQ(a.Degree(), 4);
    EXPECT_EQ(a[0], 0);
    EXPECT_EQ(a[1], 0);
    EXPECT_EQ(a[2], 25);
    EXPECT_EQ(a[3], 100);
    EXPECT_EQ(a[4], 100);

    b = b * a;

    ASSERT_EQ(b.Degree(), 6);
    EXPECT_EQ(b[0], 0);
    EXPECT_EQ(b[1], 0);
    EXPECT_EQ(b[2], 0);
    EXPECT_EQ(b[3], 125);
    EXPECT_EQ(b[4], 750);
    EXPECT_EQ(b[5], 1500);
    EXPECT_EQ(b[6], 1000);
}

TEST(Polinom, Division) {
    std::vector<double> v{ 3, 2, 1, 0 };
    std::vector<double> v2{ 3, 2, 1 };
    Polinom<double> a(v);
    Polinom<double> b(v2);

    EXPECT_EQ(a, (b * (a / b)) + (a % b));

    std::vector<int> v3{ 5, 2, 1, 0 };
    std::vector<int> v4{ 2, 1 };
    Polinom<int> c(v3);
    Polinom<int> d(v4);

    auto e = (c / d);
    ASSERT_EQ(e[0], 0);
    ASSERT_EQ(e[1], 0);
    ASSERT_EQ(e[2], 2);
    EXPECT_EQ(c, (d * (c / d)) + (c % d));
}

TEST(Polinom, Value) {
    std::vector<int> v{ 2, 1, 0 };
    Polinom<int> a(v);
    EXPECT_EQ(a.Count(2), 10);
}
