#pragma once

#include <unordered_map>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <cmath>
#include <iostream>

template <typename T>
class SparseVector {
private:
    std::unordered_map<size_t, T> elements; // Stores non-zero elements
    size_t size; // Total size of the vector

public:
    // Constructor
    SparseVector(size_t size) : size(size) {}

    // Get the size of the vector
    size_t getSize() const {
        return size;
    }

    // Get a value at a specific index (read-only)
    T get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        auto it = elements.find(index);
        return (it != elements.end()) ? it->second : T(0);
    }

    // Set a value at a specific index
    void set(size_t index, const T& value) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (value != T(0)) {
            elements[index] = value;
        } else {
            elements.erase(index); // Remove zero values to maintain sparsity
        }
    }

    // Access operator (read/write)
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    // Access operator (read-only)
    const T operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        auto it = elements.find(index);
        return (it != elements.end()) ? it->second : T(0);
    }

    // Binary operations
    SparseVector<T> operator+(const SparseVector<T>& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vector sizes must match");
        }
        SparseVector<T> result(size);
        for (const auto& [index, value] : elements) {
            result.elements[index] = value;
        }
        for (const auto& [index, value] : other.elements) {
            result.elements[index] += value;
        }
        return result;
    }

    SparseVector<T> operator*(const T& scalar) const {
        SparseVector<T> result(size);
        for (const auto& [index, value] : elements) {
            result.elements[index] = value * scalar;
        }
        return result;
    }

    // Element-wise operations
    SparseVector<T> operator^(const T& exponent) const {
        SparseVector<T> result(size);
        for (const auto& [index, value] : elements) {
            result.elements[index] = std::pow(value, exponent);
        }
        return result;
    }

    // Dot product
    T dot(const SparseVector<T>& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vector sizes must match");
        }
        T result = T(0);
        for (const auto& [index, value] : elements) {
            auto it = other.elements.find(index);
            if (it != other.elements.end()) {
                result += value * it->second;
            }
        }
        return result;
    }

    // Print function
    void print() const {
        std::cout << "SparseVector: { ";
        for (const auto& [index, value] : elements) {
            std::cout << "(" << index << ": " << value << ") ";
        }
        std::cout << "} Size: " << size << std::endl;
    }

    // Iterator for non-zero elements
    class Iterator {
    private:
        typename std::unordered_map<size_t, T>::const_iterator it;

    public:
        explicit Iterator(typename std::unordered_map<size_t, T>::const_iterator it) : it(it) {}

        Iterator& operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }

        const std::pair<const size_t, T>& operator*() const {
            return *it;
        }
    };

    Iterator begin() const {
        return Iterator(elements.cbegin());
    }

    Iterator end() const {
        return Iterator(elements.cend());
    }

};