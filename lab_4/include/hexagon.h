#pragma once
#include "figure.h"
#include <cmath>
#include <iostream>

template<typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon() : Figure<T>(6) {}

    bool isCorrect() const {
        double d[6];
        for(int i=0;i<6;i++){
            int j=(i+1)%6;
            double dx=this->points[i].x-this->points[j].x;
            double dy=this->points[i].y-this->points[j].y;
            d[i]=std::sqrt(dx*dx+dy*dy);
        }
        for(int i=1;i<6;i++) if(std::abs(d[i]-d[0])>1e-6) return false;
        return true;
    }

    void print() const  {
        std::cout << "Hexagon: ";
        for(int i=0;i<6;i++)
            std::cout << "(" << this->points[i].x << "," << this->points[i].y << ") ";
        std::cout << "\n";
    }

    operator double() const {
        double area=0;
        for(int i=0;i<6;i++){
            int j=(i+1)%6;
            area+=this->points[i].x*this->points[j].y - this->points[j].x*this->points[i].y;
        }
        return std::abs(area)/2.0;
    }
};
