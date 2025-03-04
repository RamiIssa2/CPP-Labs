#pragma once

#include <unordered_map>
#include <map>
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

    // Getters for dimensions
    size_t getRows() const {
        return rows;
    }

    size_t getCols() const {
        return cols;
    }

    // Access element (read-only)
    T get(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        auto rowIt = elements.find(row);
        if (rowIt != elements.end()) {
            auto colIt = rowIt->second.find(col);
            return (colIt != rowIt->second.end()) ? colIt->second : T(0);
        }
        return T(0);
    }

    // Set element value
    void set(size_t row, size_t col, const T& value) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        if (value != T(0)) {
            elements[row][col] = value;
        } else {
            // Remove entry if value is zero to maintain sparsity
            auto rowIt = elements.find(row);
            if (rowIt != elements.end()) {
                rowIt->second.erase(col);
                if (rowIt->second.empty()) {
                    elements.erase(row);
                }
            }
        }
    }

    // Transpose the matrix
    SparseMatrix<T> transpose() const {
        SparseMatrix<T> result(cols, rows);
        for (const auto& [row, colMap] : elements) {
            for (const auto& [col, value] : colMap) {
                result.set(col, row, value);
            }
        }
        return result;
    }

    // Addition with another SparseMatrix
    SparseMatrix<T> operator+(const SparseMatrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match");
        }
        SparseMatrix<T> result(rows, cols);
        for (const auto& [row, colMap] : elements) {
            for (const auto& [col, value] : colMap) {
                result.set(row, col, value);
            }
        }
        for (const auto& [row, colMap] : other.elements) {
            for (const auto& [col, value] : colMap) {
                result.set(row, col, result.get(row, col) + value);
            }
        }
        return result;
    }

    // Scalar multiplication
    SparseMatrix<T> operator*(const T& scalar) const {
        SparseMatrix<T> result(rows, cols);
        for (const auto& [row, colMap] : elements) {
            for (const auto& [col, value] : colMap) {
                result.set(row, col, value * scalar);
            }
        }
        return result;
    }

    // Matrix multiplication
    SparseMatrix<T> operator*(const SparseMatrix<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");
        }
        SparseMatrix<T> result(rows, other.cols);
        for (const auto& [row, colMap] : elements) {
            for (const auto& [col, value] : colMap) {
                auto it = other.elements.find(col);
                if (it != other.elements.end()) {
                    for (const auto& [k, otherValue] : it->second) {
                        result.set(row, k, result.get(row, k) + value * otherValue);
                    }
                }
            }
        }
        return result;
    }

    // Matrix exponentiation (only for square matrices)
    SparseMatrix<T> operator^(size_t exponent) const {
        if (rows != cols) {
            throw std::invalid_argument("Matrix exponentiation is only defined for square matrices");
        }

        SparseMatrix<T> result(rows, cols);
        SparseMatrix<T> base(*this);

        // Initialize result as the identity matrix
        for (size_t i = 0; i < rows; ++i) {
            result.set(i, i, T(1));
        }

        // Exponentiation by squaring
        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            exponent /= 2;
        }

        return result;
    }

    // Inverse of a square matrix (assuming non-singular)
    SparseMatrix<T> inverse() const {
        if (rows != cols) {
            throw std::invalid_argument("Matrix inversion is only defined for square matrices");
        }

        SparseMatrix<T> identity(rows, cols);
        SparseMatrix<T> result(*this);

        // Initialize identity matrix
        for (size_t i = 0; i < rows; ++i) {
            identity.set(i, i, T(1));
        }

        // Gaussian elimination for sparse matrices
        for (size_t i = 0; i < rows; ++i) {
            // Find pivot
            if (result.get(i, i) == T(0)) {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }

            T pivot = result.get(i, i);

            // Normalize pivot row
            for (size_t j = 0; j < cols; ++j) {
                result.set(i, j, result.get(i, j) / pivot);
                identity.set(i, j, identity.get(i, j) / pivot);
            }

            // Eliminate other rows
            for (size_t k = 0; k < rows; ++k) {
                if (k != i) {
                    T factor = result.get(k, i);
                    for (size_t j = 0; j < cols; ++j) {
                        result.set(k, j, result.get(k, j) - factor * result.get(i, j));
                        identity.set(k, j, identity.get(k, j) - factor * identity.get(i, j));
                    }
                }
            }
        }

        return identity;
    }

    // Print the matrix
    void print() const {
        std::map<size_t, std::map<size_t, T>> sorted_elements;

        // Convert unordered_map to nested map for sorted traversal
        for (const auto& [row, colMap] : elements) {
            for (const auto& [col, value] : colMap) {
                sorted_elements[row][col] = value;
            }
        }

        // Print the sorted elements
        std::cout << "SparseMatrix: " << rows << "x" << cols << std::endl;
        for (const auto& [row, colMap] : sorted_elements) {
            for (const auto& [col, value] : colMap) {
                std::cout << "(" << row << ", " << col << "): " << value << std::endl;
            }
        }
    }

};