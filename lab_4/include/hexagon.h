#pragma once
#include <cmath>
#include <iostream>
#include <memory>
#include "figure.h"

template <Scalar T>
class Hexagon : public Figure<T> {
    std::unique_ptr<Point<T>> p1_, p2_, p3_, p4_, p5_, p6_;

    double distance(const Point<T>& p1, const Point<T>& p2) const {
        T dx = p1.x - p2.x;
        T dy = p1.y - p2.y;
        return std::sqrt(dx * dx + dy * dy);
    }

   public:
    Hexagon() {
        double R = 1.0;
        p1_ = std::make_unique<Point<T>>(T(R * std::cos(0)), T(R * std::sin(0)));
        p2_ = std::make_unique<Point<T>>(T(R * std::cos(M_PI / 3)), T(R * std::sin(M_PI / 3)));
        p3_ = std::make_unique<Point<T>>(T(R * std::cos(2 * M_PI / 3)), T(R * std::sin(2 * M_PI / 3)));
        p4_ = std::make_unique<Point<T>>(T(R * std::cos(M_PI)), T(R * std::sin(M_PI)));
        p5_ = std::make_unique<Point<T>>(T(R * std::cos(4 * M_PI / 3)), T(R * std::sin(4 * M_PI / 3)));
        p6_ = std::make_unique<Point<T>>(T(R * std::cos(5 * M_PI / 3)), T(R * std::sin(5 * M_PI / 3)));
    }

    Hexagon(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4, T x5, T y5, T x6, T y6)
        : p1_(std::make_unique<Point<T>>(x1, y1)),
          p2_(std::make_unique<Point<T>>(x2, y2)),
          p3_(std::make_unique<Point<T>>(x3, y3)),
          p4_(std::make_unique<Point<T>>(x4, y4)),
          p5_(std::make_unique<Point<T>>(x5, y5)),
          p6_(std::make_unique<Point<T>>(x6, y6)) {}

    Hexagon(const Hexagon& other)
        : p1_(std::make_unique<Point<T>>(*other.p1_)),
          p2_(std::make_unique<Point<T>>(*other.p2_)),
          p3_(std::make_unique<Point<T>>(*other.p3_)),
          p4_(std::make_unique<Point<T>>(*other.p4_)),
          p5_(std::make_unique<Point<T>>(*other.p5_)),
          p6_(std::make_unique<Point<T>>(*other.p6_)) {}

    Hexagon(Hexagon&& other) noexcept
        : p1_(std::move(other.p1_)),
          p2_(std::move(other.p2_)),
          p3_(std::move(other.p3_)),
          p4_(std::move(other.p4_)),
          p5_(std::move(other.p5_)),
          p6_(std::move(other.p6_)) {}

    Hexagon& operator=(const Hexagon& other) {
        if (this != &other) {
            p1_ = std::make_unique<Point<T>>(*other.p1_);
            p2_ = std::make_unique<Point<T>>(*other.p2_);
            p3_ = std::make_unique<Point<T>>(*other.p3_);
            p4_ = std::make_unique<Point<T>>(*other.p4_);
            p5_ = std::make_unique<Point<T>>(*other.p5_);
            p6_ = std::make_unique<Point<T>>(*other.p6_);
        }
        return *this;
    }

    Hexagon& operator=(Hexagon&& other) noexcept {
        if (this != &other) {
            p1_ = std::move(other.p1_);
            p2_ = std::move(other.p2_);
            p3_ = std::move(other.p3_);
            p4_ = std::move(other.p4_);
            p5_ = std::move(other.p5_);
            p6_ = std::move(other.p6_);
        }
        return *this;
    }

    Point<T> centroid() const override {
        T center_x = (p1_->x + p2_->x + p3_->x + p4_->x + p5_->x + p6_->x) / 6;
        T center_y = (p1_->y + p2_->y + p3_->y + p4_->y + p5_->y + p6_->y) / 6;
        return Point<T>(center_x, center_y);
    }

    double area() const override {
        double area = 0.0;
        area += p1_->x * p2_->y - p2_->x * p1_->y;
        area += p2_->x * p3_->y - p3_->x * p2_->y;
        area += p3_->x * p4_->y - p4_->x * p3_->y;
        area += p4_->x * p5_->y - p5_->x * p4_->y;
        area += p5_->x * p6_->y - p6_->x * p5_->y;
        area += p6_->x * p1_->y - p1_->x * p6_->y;
        return std::abs(area) / 2.0;
    }

    bool isCorrect() const {
        const double EPS = 1e-6;
        
        // Проверка на совпадающие точки
        Point<T>* points[] = {p1_.get(), p2_.get(), p3_.get(), p4_.get(), p5_.get(), p6_.get()};
        for (int i = 0; i < 6; ++i) {
            for (int j = i + 1; j < 6; ++j) {
                if (distance(*points[i], *points[j]) < EPS) {
                    return false;
                }
            }
        }

        // Проверка равенства всех сторон
        double side1 = distance(*p1_, *p2_);
        double side2 = distance(*p2_, *p3_);
        double side3 = distance(*p3_, *p4_);
        double side4 = distance(*p4_, *p5_);
        double side5 = distance(*p5_, *p6_);
        double side6 = distance(*p6_, *p1_);

        return (std::fabs(side1 - side2) < EPS) &&
               (std::fabs(side2 - side3) < EPS) &&
               (std::fabs(side3 - side4) < EPS) &&
               (std::fabs(side4 - side5) < EPS) &&
               (std::fabs(side5 - side6) < EPS) &&
               (side1 > EPS) && (area() > EPS);
    }

    std::unique_ptr<std::unique_ptr<Point<T>>[]> getVertices(size_t& count) const override {
        count = 6;
        auto verts = std::make_unique<std::unique_ptr<Point<T>>[]>(count);
        verts[0] = std::make_unique<Point<T>>(*p1_);
        verts[1] = std::make_unique<Point<T>>(*p2_);
        verts[2] = std::make_unique<Point<T>>(*p3_);
        verts[3] = std::make_unique<Point<T>>(*p4_);
        verts[4] = std::make_unique<Point<T>>(*p5_);
        verts[5] = std::make_unique<Point<T>>(*p6_);
        return verts;
    }

    bool operator==(const Figure<T>& other) const override {
        const Hexagon<T>* h = dynamic_cast<const Hexagon<T>*>(&other);
        return h && *p1_ == *h->p1_ && *p2_ == *h->p2_ && *p3_ == *h->p3_ && 
               *p4_ == *h->p4_ && *p5_ == *h->p5_ && *p6_ == *h->p6_;
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Hexagon<T>>(*this);
    }

    void print_vertices() const override {
        std::cout << "Points:\n";
        std::cout << "  (" << p1_->x << ", " << p1_->y << ")\n";
        std::cout << "  (" << p2_->x << ", " << p2_->y << ")\n";
        std::cout << "  (" << p3_->x << ", " << p3_->y << ")\n";
        std::cout << "  (" << p4_->x << ", " << p4_->y << ")\n";
        std::cout << "  (" << p5_->x << ", " << p5_->y << ")\n";
        std::cout << "  (" << p6_->x << ", " << p6_->y << ")\n";
    }

    void read_from_stream(std::istream& is) override {
        T x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
        if (!(is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x6 >> y6)) {
            throw std::runtime_error("Invalid input for Hexagon");
        }
        p1_ = std::make_unique<Point<T>>(x1, y1);
        p2_ = std::make_unique<Point<T>>(x2, y2);
        p3_ = std::make_unique<Point<T>>(x3, y3);
        p4_ = std::make_unique<Point<T>>(x4, y4);
        p5_ = std::make_unique<Point<T>>(x5, y5);
        p6_ = std::make_unique<Point<T>>(x6, y6);
    }
};