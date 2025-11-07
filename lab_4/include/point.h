#pragma once
#include <iostream>

template <typename T>

class Point {
    T x;
    T y;
public:
    Point() : x(0), y(0) {}
    Point(T _x, T _y) : x(_x), y(_y) {}

    T get_x() const { return x; }
    T get_y() const { return y; }
    void set_x(T _x) { x = _x; }
    void set_y(T _y) { y = _y; }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};
