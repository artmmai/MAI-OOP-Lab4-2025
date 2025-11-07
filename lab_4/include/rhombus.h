#pragma once
#include "figure.h"
#include <cmath>
#include <iostream>

template<typename T>
class Rhombus : public Figure<T> {
public:
    Rhombus() : Figure<T>(4) {}

    bool isCorrect() const {
        double d[4];
        for(int i = 0; i < 4; ++i){
            int j = (i+1)%4;
            double dx = this->points[i].get_x() - this->points[j].get_x();
            double dy = this->points[i].get_y() - this->points[j].get_y();
            if (std::sqrt(dx * dx + dy * dy) < this->EPS){
                return false;
            }
    }

    void print() const {
        std::cout << "Rhombus: ";
        for(int i=0;i<4;i++)
            std::cout << "(" << this->points[i].x << "," << this->points[i].y << ") ";
        std::cout << "\n";
    }

};
