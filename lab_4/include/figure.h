#pragma once
#include <cstddef>
#include <stdexcept>
#include <concepts>
#include <memory>

template<class P>
struct Point {
    P x{}, y{};
};

template<class T>
class Figure {
protected:
    std::unique_ptr<Point<T>[]> points;
    size_t nPoints;

public:
    Figure(size_t n) : nPoints(n), points(std::make_unique<Point<T>[]>(n)) {}

    virtual ~Figure() = default;

    // Методы для работы с точками
    Point<T>& getPoint(size_t idx) {
        if (idx >= nPoints) throw std::out_of_range("Invalid point index");
        return points[idx];
    }

    void setPoint(size_t idx, const Point<T>& p) {
        if (idx >= nPoints) throw std::out_of_range("Invalid point index");
        points[idx] = p;
    }

    size_t getSize() const { return nPoints; }

    virtual bool isCorrect() const = 0;
    virtual void print() const = 0;
    virtual operator double() const = 0;
};
