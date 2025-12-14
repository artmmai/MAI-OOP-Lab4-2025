#pragma once
#include <concepts>
#include <type_traits>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
    T x, y;

    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}

    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};
