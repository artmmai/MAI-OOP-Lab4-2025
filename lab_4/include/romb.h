#pragma once
#include <cmath>
#include <iostream>
#include <memory>
#include "figure.h"

template <Scalar T>
class Romb : public Figure<T> {
    std::unique_ptr<Point<T>> p1_, p2_, p3_, p4_;

    double distance(const Point<T>& p1, const Point<T>& p2) const {
        T dx = p1.x - p2.x;
        T dy = p1.y - p2.y;
        return std::sqrt(dx * dx + dy * dy);
    }

   public:
    Romb() : p1_(std::make_unique<Point<T>>(2, 0)),
             p2_(std::make_unique<Point<T>>(0, 3)),
             p3_(std::make_unique<Point<T>>(-2, 0)),
             p4_(std::make_unique<Point<T>>(0, -3)) {}

    Romb(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4)
        : p1_(std::make_unique<Point<T>>(x1, y1)),
          p2_(std::make_unique<Point<T>>(x2, y2)),
          p3_(std::make_unique<Point<T>>(x3, y3)),
          p4_(std::make_unique<Point<T>>(x4, y4)) {}

    Romb(const Romb& other)
        : p1_(std::make_unique<Point<T>>(*other.p1_)),
          p2_(std::make_unique<Point<T>>(*other.p2_)),
          p3_(std::make_unique<Point<T>>(*other.p3_)),
          p4_(std::make_unique<Point<T>>(*other.p4_)) {}

    Romb(Romb&& other) noexcept
        : p1_(std::move(other.p1_)),
          p2_(std::move(other.p2_)),
          p3_(std::move(other.p3_)),
          p4_(std::move(other.p4_)) {}

    Romb& operator=(const Romb& other) {
        if (this != &other) {
            p1_ = std::make_unique<Point<T>>(*other.p1_);
            p2_ = std::make_unique<Point<T>>(*other.p2_);
            p3_ = std::make_unique<Point<T>>(*other.p3_);
            p4_ = std::make_unique<Point<T>>(*other.p4_);
        }
        return *this;
    }

    Romb& operator=(Romb&& other) noexcept {
        if (this != &other) {
            p1_ = std::move(other.p1_);
            p2_ = std::move(other.p2_);
            p3_ = std::move(other.p3_);
            p4_ = std::move(other.p4_);
        }
        return *this;
    }

    Point<T> centroid() const override {
        T center_x = (p1_->x + p2_->x + p3_->x + p4_->x) / 4;
        T center_y = (p1_->y + p2_->y + p3_->y + p4_->y) / 4;
        return Point<T>(center_x, center_y);
    }

    double area() const override {
        double d1 = distance(*p1_, *p3_);
        double d2 = distance(*p2_, *p4_);
        return (d1 * d2) / 2.0;
    }

    bool isCorrect() const {
        const double EPS = 1e-6;
        
        // Проверка на совпадающие точки
        if (distance(*p1_, *p2_) < EPS || distance(*p2_, *p3_) < EPS ||
            distance(*p3_, *p4_) < EPS || distance(*p4_, *p1_) < EPS) {
            return false;
        }
        
        // Проверка равенства всех сторон ромба
        double side1 = distance(*p1_, *p2_);
        double side2 = distance(*p2_, *p3_);
        double side3 = distance(*p3_, *p4_);
        double side4 = distance(*p4_, *p1_);
        
        return (std::fabs(side1 - side2) < EPS) &&
               (std::fabs(side2 - side3) < EPS) &&
               (std::fabs(side3 - side4) < EPS) &&
               (side1 > EPS) && (area() > EPS);
    }

    std::unique_ptr<std::unique_ptr<Point<T>>[]> getVertices(size_t& count) const override {
        count = 4;
        auto verts = std::make_unique<std::unique_ptr<Point<T>>[]>(count);
        verts[0] = std::make_unique<Point<T>>(*p1_);
        verts[1] = std::make_unique<Point<T>>(*p2_);
        verts[2] = std::make_unique<Point<T>>(*p3_);
        verts[3] = std::make_unique<Point<T>>(*p4_);
        return verts;
    }

    bool operator==(const Figure<T>& other) const override {
        const Romb<T>* rh = dynamic_cast<const Romb<T>*>(&other);
        return rh && *p1_ == *rh->p1_ && *p2_ == *rh->p2_ && 
               *p3_ == *rh->p3_ && *p4_ == *rh->p4_;
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Romb<T>>(*this);
    }

    void print_vertices() const override {
        std::cout << "Points:\n";
        std::cout << "  (" << p1_->x << ", " << p1_->y << ")\n";
        std::cout << "  (" << p2_->x << ", " << p2_->y << ")\n";
        std::cout << "  (" << p3_->x << ", " << p3_->y << ")\n";
        std::cout << "  (" << p4_->x << ", " << p4_->y << ")\n";
    }

    void read_from_stream(std::istream& is) override {
        T x1, y1, x2, y2, x3, y3, x4, y4;
        if (!(is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
            throw std::runtime_error("Invalid input for Romb");
        }
        p1_ = std::make_unique<Point<T>>(x1, y1);
        p2_ = std::make_unique<Point<T>>(x2, y2);
        p3_ = std::make_unique<Point<T>>(x3, y3);
        p4_ = std::make_unique<Point<T>>(x4, y4);
    }
};