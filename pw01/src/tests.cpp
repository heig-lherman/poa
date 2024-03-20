#include <gtest/gtest.h>
#include <iostream>
#include "Matrix.hpp"
#include "Utils.hpp"

TEST(Matrix, DifferentModulus) {
    auto m1 = Matrix(2, 2, 3);
    auto m2 = Matrix(2, 2, 5);
    ASSERT_THROW(m1.add(m2), std::invalid_argument);
}

TEST(Matrix, ZeroModulus) {
    ASSERT_THROW(new Matrix(2, 2, 0), std::invalid_argument);
}

TEST(Matrix, StringDisplayEmpty) {
    auto empty = Matrix(0, 0, 1);
    std::stringstream res;
    res << empty;
    ASSERT_EQ(res.str(), "[]\n");
}

TEST(Matrix, StringDisplay) {
    auto m = Matrix(2, 2, 10);
    std::stringstream res;
    res << m;
    ASSERT_EQ(res.str(), "4 6 \n6 3 \n");
}

TEST(Matrix, AddStatic) {
    auto m1 = Matrix(2, 2, 10);
    std::stringstream m1res;
    m1res << m1;
    auto m2 = Matrix(2, 2, 10);
    std::stringstream m2res;
    m2res << m2;
    auto res = m1.addStatic(m2);
    std::stringstream out;
    out << res;
    ASSERT_EQ(m1res.str(), (std::stringstream{} << m1).str());
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_EQ(out.str(), "3 4 \n1 4 \n");
}

TEST(Matrix, SubtractStatic) {
    auto m1 = Matrix(2, 2, 10);
    std::stringstream m1res;
    m1res << m1;
    auto m2 = Matrix(2, 2, 10);
    auto res = m1.subtractStatic(m2);
    std::stringstream out;
    out << res;
    ASSERT_EQ(out.str(), "2 5 \n6 6 \n");
}

TEST(Matrix, MultiplyStatic) {
    auto m1 = Matrix(2, 2, 10);
    std::stringstream m1res;
    m1res << m1;
    auto m2 = Matrix(2, 2, 10);
    std::stringstream m2res;
    m2res << m2;
    auto res = m1.multiplyStatic(m2);
    std::stringstream out;
    out << res;
    ASSERT_EQ(m1res.str(), (std::stringstream{} << m1).str());
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_EQ(out.str(), "0 9 \n0 4 \n");
}

TEST(Matrix, EmptyAnyOperation) {
    auto m1 = Matrix(0, 0, 10);
    auto m2 = Matrix(4, 3, 10);
    m1.add(m2);
    // std::cout << m1 << m2 << std::endl;
    std::stringstream out;
    out << m1;
    ASSERT_EQ(out.str(), "7 1 8 \n8 9 4 \n7 8 4 \n5 7 6 \n");
}

TEST(Matrix, AddDynamic) {
    auto m1 = Matrix(2, 2, 10);
    std::stringstream m1res;
    m1res << m1;
    auto m2 = Matrix(2, 2, 10);
    std::stringstream m2res;
    m2res << m2;
    auto res = m1.addDynamic(m2);
    std::stringstream out;
    out << *res;
    ASSERT_EQ(m1res.str(), (std::stringstream{} << m1).str());
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_EQ(out.str(), "2 2 \n5 2 \n");
    delete res;
}

TEST(Matrix, SubtractDynamic) {
    auto m1 = Matrix(2, 2, 10);
    std::stringstream m1res;
    m1res << m1;
    auto m2 = Matrix(2, 2, 10);
    std::stringstream m2res;
    m2res << m2;
    auto res = m1.subtractDynamic(m2);
    std::stringstream out;
    out << *res;
    ASSERT_EQ(m1res.str(), (std::stringstream{} << m1).str());
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_EQ(out.str(), "3 0 \n7 7 \n");
    delete res;
}

TEST(Matrix, MultiplyDynamic) {
    auto m1 = Matrix(2, 2, 10);
    std::stringstream m1res;
    m1res << m1;
    auto m2 = Matrix(2, 2, 10);
    std::stringstream m2res;
    m2res << m2;
    auto res = m1.multiplyDynamic(m2);
    std::stringstream out;
    out << *res;
    ASSERT_EQ(m1res.str(), (std::stringstream{} << m1).str());
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_EQ(out.str(), "0 6 \n0 1 \n");
    delete res;
}

TEST(Matrix, AddSelf) {
    auto m1 = Matrix(2, 2, 10);
    auto m2 = Matrix(2, 2, 10);
    std::stringstream m2res;
    m2res << m2;
    m1.add(m2);
    std::stringstream m1res;
    m1res << m1;
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_NE(m1res.str(), m2res.str());
}

TEST(Matrix, SubtractSelf) {
    auto m1 = Matrix(1, 2, 10);
    auto m2 = Matrix(3, 4, 10);
    std::stringstream m2res;
    m2res << m2;
    auto& res = m1.subtract(m2);
    std::stringstream m1res;
    m1res << m1;
    std::stringstream out;
    out << res;
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_EQ(m1res.str(), out.str());
}

TEST(Matrix, MultiplySelf) {
    auto m1 = Matrix(4, 3, 10);
    auto m2 = Matrix(3, 4, 10);
    std::stringstream m2res;
    m2res << m2;
    auto& res = m1.multiply(m2);
    std::stringstream m1res;
    m1res << m1;
    std::stringstream out;
    out << res;
    ASSERT_EQ(m2res.str(), (std::stringstream{} << m2).str());
    ASSERT_EQ(m1res.str(), out.str());
}

TEST(FloorMod, Positive) {
    ASSERT_EQ(floorMod(5, 3), 2);
}

TEST(FloorMod, Negative) {
    ASSERT_EQ(floorMod(-5, 3), 1);
}

TEST(FloorMod, Zero) {
    ASSERT_EQ(floorMod(0, 3), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
