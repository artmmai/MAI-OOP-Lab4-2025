#pragma once
#include "hexagon.h"
#include "pentagon.h"
#include "point.h"
#include "figure.h"
#include "rhombus.h"
#include <memory>
#include <iostream>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t size;
    size_t capacity;

void expand() {
        size_t newCap = capacity == 0 ? 1 : capacity * 2;
        std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCap);
        for(size_t i=0; i<size; ++i)
            newData[i] = std::move(data[i]); 
        data = std::move(newData);
        capacity = newCap;
    }

public:
    Array() : size(0), capacity(0) {}

    Array(const Array& other) : size(other.size), capacity(other.capacity) {
        data = std::make_unique<T[]>(capacity);
        for(size_t i=0;i<size;++i)
            data[i] = other.data[i];
    }

    Array(Array&& other) noexcept : data(std::move(other.data)), size(other.size), capacity(other.capacity) {
        other.size = 0;
        other.capacity = 0;
    }

    Array& operator=(const Array& other){
        if(this != &other){
            data = std::make_unique<T[]>(other.capacity);
            size = other.size;
            capacity = other.capacity;
            for(size_t i = 0;i < size;++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if(this != &other){
            data = std::move(other.data);
            size = other.size;
            capacity = other.capacity;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void push_back(const T& val) {
        if(size == capacity) expand();
        data[size++] = val;
    }

    void remove(size_t idx){
        if(idx >= size) throw std::out_of_range("Index out of range");
        for(size_t i = idx;i < size-1;++i)
            data[i] = std::move(data[i+1]);
        --size;
    }

    T& operator[](size_t idx){
        if(idx>=size) throw std::out_of_range("Index out of range");
        return data[idx];
    }

    const T& operator[](size_t idx) const{
        if(idx>=size) throw std::out_of_range("Index out of range");
        return data[idx];
    }

    size_t getSize() const { return size; }

    void Array::printAll() const {
    if (size == 0) {
        std::cout << "No figures in array.\n";
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        std::cout << "\n=== Figure " << i << " (" << arr[i]->getName() << ") ===\n";

        size_t n = arr[i]->getPointCount();
        std::cout << "Points:\n";
        for (size_t j = 0; j < n; ++j) {
            const Point &p = arr[i]->getPoint(j);
            std::cout << "  (" << p.get_x() << ", " << p.get_y() << ")\n";
        }

        Point center = arr[i]->getCenter();
        double area = static_cast<double>(*arr[i]);

        std::cout << "Center: (" << center.get_x() << ", " << center.get_y() << ")\n";
        std::cout << "Area: " << area << "\n";
    }
}

    double totalArea() const {
        double sum = 0;
        for(size_t i = 0;i < size;++i)
            sum += double(*data[i]);
        return sum;
    }
};

// Явная инстанциация
template class Array<int>;
template class Array<Rhombus<int>>;
template class Array<Pentagon<int>>;
template class Array<Hexagon<int>>;
template class Array<std::shared_ptr<Figure<int>>>;