#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>

template <typename T>
class Array {
    std::shared_ptr<T[]> data;
    size_t _size = 0;
    size_t _capacity = 0;

    void resize_if_needed() {
        if (_size >= _capacity) {
            size_t new_cap = (_capacity == 0) ? 1 : _capacity * 2;
            auto new_data = std::shared_ptr<T[]>(new T[new_cap]);
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = std::move(data[i]);
            }
            data = std::move(new_data);
            _capacity = new_cap;
        }
    }

   public:
    Array() : _capacity(10), data(new T[10]) {}

    Array(const Array& other)
        : _size(other._size), _capacity(other._capacity), data(new T[other._capacity]) {
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array(Array&& other) noexcept
        : _size(other._size), _capacity(other._capacity), data(std::move(other.data)) {
        other._size = 0;
        other._capacity = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            data = std::shared_ptr<T[]>(new T[_capacity]);
            for (size_t i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            data = std::move(other.data);
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    void push_back(const T& item) {
        resize_if_needed();
        data[_size] = item;
        ++_size;
    }

    void push_back(T&& item) {
        resize_if_needed();
        data[_size] = std::move(item);
        ++_size;
    }

    size_t size() const { return _size; }

    T& operator[](size_t i) {
        if (i >= _size) throw std::out_of_range("Array index out of range");
        return data[i];
    }

    const T& operator[](size_t i) const {
        if (i >= _size) throw std::out_of_range("Array index out of range");
        return data[i];
    }

    void remove(size_t index) {
        if (index >= _size) throw std::out_of_range("Invalid index");
        for (size_t i = index; i < _size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --_size;
    }

    double total_area() const {
        double total = 0.0;
        for (size_t i = 0; i < _size; ++i) {
            total += data[i]->area();
        }
        return total;
    }
};
