#pragma once
#include "figure.h"
#include <cmath>
#include <iostream>

template<typename T>
class Pentagon : public Figure<T> {
public:
    Pentagon() : Figure<T>(5) {}

    bool isCorrect() const override {
        double d[5];
        for(int i=0;i<5;i++){
            int j=(i+1)%5;
            double dx=this->points[i].x-this->points[j].x;
            double dy=this->points[i].y-this->points[j].y;
            d[i]=std::sqrt(dx*dx+dy*dy);
        }
        for(int i=1;i<5;i++) if(std::abs(d[i]-d[0])>1e-6) return false;
        return true;
    }

    void print() const override {
        std::cout << "Pentagon: ";
        for(int i=0;i<5;i++)
            std::cout << "(" << this->points[i].x << "," << this->points[i].y << ") ";
        std::cout << "\n";
    }

    operator double() const override {
        double area=0;
        for(int i=0;i<5;i++){
            int j=(i+1)%5;
            area+=this->points[i].x*this->points[j].y - this->points[j].x*this->points[i].y;
        }
        return std::abs(area)/2.0;
    }
};
