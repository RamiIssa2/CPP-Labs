#pragma once

#include <unordered_map>
#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <iostream>

template <typename T>
class SparseMatrix {
private:
    std::unordered_map<size_t, std::unordered_map<size_t, T>> elements; // Non-zero elements stored as {row -> {col -> value}}
    size_t rows, cols; // Dimensions of the matrix

public:
    // Constructor
    SparseMatrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}

};