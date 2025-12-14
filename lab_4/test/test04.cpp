#include <gtest/gtest.h>
#include <sstream>
#include "../include/point.h"
#include "../include/romb.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/array.h"

// Тесты для Point
TEST(PointTest, CreateAndCompare) {
    Point<int> p1(5, 10);
    EXPECT_EQ(p1.x, 5);
    EXPECT_EQ(p1.y, 10);
    
    Point<int> p2(5, 10);
    Point<int> p3(1, 2);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// Тесты для Romb
TEST(RombTest, AreaCalculation) {
    Romb<double> r;
    double area = r.area();
    EXPECT_GT(area, 0);
}

TEST(RombTest, Centroid) {
    Romb<double> r;
    Point<double> center = r.centroid();
    EXPECT_EQ(center.x, 0.0);
    EXPECT_EQ(center.y, 0.0);
}

TEST(RombTest, IsCorrect) {
    Romb<double> r;
    EXPECT_TRUE(r.isCorrect());
}

// Тесты для Pentagon
TEST(PentagonTest, AreaCalculation) {
    Pentagon<double> p;
    double area = p.area();
    EXPECT_GT(area, 0);
}

TEST(PentagonTest, Centroid) {
    Pentagon<double> p;
    Point<double> center = p.centroid();
    EXPECT_NEAR(center.x, 0.0, 1e-10);
    EXPECT_NEAR(center.y, 0.0, 1e-10);
}

TEST(PentagonTest, IsCorrect) {
    Pentagon<double> p;
    EXPECT_TRUE(p.isCorrect());
}

// Тесты для Hexagon
TEST(HexagonTest, AreaCalculation) {
    Hexagon<double> h;
    double area = h.area();
    EXPECT_GT(area, 0);
}

TEST(HexagonTest, Centroid) {
    Hexagon<double> h;
    Point<double> center = h.centroid();
    EXPECT_NEAR(center.x, 0.0, 1e-10);
    EXPECT_NEAR(center.y, 0.0, 1e-10);
}

TEST(HexagonTest, IsCorrect) {
    Hexagon<double> h;
    EXPECT_TRUE(h.isCorrect());
}

// Тесты для Array
TEST(ArrayTest, BasicOperations) {
    Array<int> arr;
    
    arr.push_back(100);
    arr.push_back(200);
    arr.push_back(300);
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
    
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 300);
}

// Тесты для Array с фигурами
TEST(ArrayFigureTest, AddFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<Romb<double>>());
    figures.push_back(std::make_shared<Pentagon<double>>());
    figures.push_back(std::make_shared<Hexagon<double>>());
    
    EXPECT_EQ(figures.size(), 3);
    EXPECT_GT(figures.total_area(), 0);
}

TEST(ArrayFigureTest, RemoveFigure) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<Romb<double>>());
    figures.push_back(std::make_shared<Pentagon<double>>());
    
    double area_before = figures.total_area();
    figures.remove(0);
    double area_after = figures.total_area();
    
    EXPECT_LT(area_after, area_before);
    EXPECT_EQ(figures.size(), 1);
}

// Тесты для полиморфизма
TEST(PolymorphismTest, BaseClass) {
    std::shared_ptr<Figure<double>> fig = std::make_shared<Romb<double>>();
    Point<double> center = fig->centroid();
    double area = fig->area();
    
    EXPECT_GT(area, 0);
    EXPECT_EQ(center.x, 0.0);
}

TEST(PolymorphismTest, OperatorDouble) {
    std::shared_ptr<Figure<double>> fig = std::make_shared<Romb<double>>();
    double area = static_cast<double>(*fig);
    EXPECT_GT(area, 0);
}

// Тесты для разных типов
TEST(ScalarTypesTest, DifferentTypes) {
    EXPECT_NO_THROW({
        Romb<int> r_int;
        EXPECT_GT(r_int.area(), 0);
    });
    
    EXPECT_NO_THROW({
        Pentagon<float> p_float;
        EXPECT_GT(p_float.area(), 0);
    });
}

// Тесты клонирования
TEST(CloneTest, RombClone) {
    auto original = std::make_shared<Romb<double>>();
    auto cloned = original->clone();
    
    EXPECT_EQ(original->area(), cloned->area());
    EXPECT_TRUE(*original == *cloned);
}

// Тесты сравнения
TEST(EqualityTest, SameFigures) {
    Romb<double> r1;
    Romb<double> r2;
    EXPECT_TRUE(r1 == r2);
}
