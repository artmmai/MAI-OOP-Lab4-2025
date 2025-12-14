#pragma once
#include <iostream>
#include <memory>
#include "point.h"

template <Scalar T>
class Figure {
   public:
    virtual ~Figure() = default;
    virtual Point<T> centroid() const = 0;
    virtual double area() const = 0;
    virtual std::unique_ptr<std::unique_ptr<Point<T>>[]> getVertices(size_t& count) const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual std::shared_ptr<Figure<T>> clone() const = 0;
    virtual operator double() const { return area(); }
    virtual void print_vertices() const = 0;
    virtual void read_from_stream(std::istream& is) = 0;
};

template <Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.read_from_stream(is);
    return is;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print_vertices();
    return os;
}
