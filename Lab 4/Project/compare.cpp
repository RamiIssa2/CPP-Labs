#include <iostream>
#include "sparseVector.h"
#include "SparseMatrix.h"
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <vector>
using namespace std;

/*               Vector Functions               */
// Function to create a random dense vector
vector<int> createDenseVector(int size, float sparsity) {

    vector<int> veector(size);

    for (int i = 0; i < size; ++i) {
            if (static_cast<float>(rand()) / RAND_MAX > sparsity) { // Fill with non-zero values based on sparsity
                veector[i] = rand() % 10 + 1; // Random values from 1 to 10
            }
        }

    return veector;

}

// Function to measure the time for an operation on a dense vector
template<typename Func>
double measureDenseVectorOperation(const vector<int>& vecA,
    const vector<int>& vecB,
    Func operation) {

    auto start = std::chrono::high_resolution_clock::now();
    operation(vecA, vecB);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count(); // Return time in milliseconds

}

// Function to measure the time for an operation on a sparse vector
template<typename Func>
double measureSparseVectorOperation(const SparseVector<int>& vecA,
    const SparseVector<int>& vecB,
    Func operation) {

    auto start = std::chrono::high_resolution_clock::now();
    operation(vecA, vecB);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count(); // Return time in milliseconds

}

// Addition operation for dense vector
std::vector<int> addDenseVectors(const std::vector<int>& vecA, const std::vector<int>& vecB) {

    std::vector<int> result(vecA.size());

    for (size_t i = 0; i < vecA.size(); ++i) {
        result[i] = vecA[i] + vecB[i];
    }

    return result;

}

// Addition operation for sparse vector
SparseVector<int> addSparseVectors(const SparseVector<int>& vecA, const SparseVector<int>& vecB) {

    return vecA + vecB; // Use overloaded + operator

}

// Dot product operation for dense vector
int dotProductDenseVectors(const std::vector<int>& vecA, const std::vector<int>& vecB) {

    int result = 0;

    for (size_t i = 0; i < vecA.size(); ++i) {
        result += vecA[i] * vecB[i];
    }

    return result;
}

// Dot product operation for sparse vector
int dotProductSparseVectors(const SparseVector<int>& vecA, const SparseVector<int>& vecB) {

    return vecA.dot(vecB); // Use dot product function

}

// Multiplication by scalar operation for dense vector
std::vector<int> multiplyDenseVectorByScalar(const std::vector<int>& vecA, const std::vector<int>& vecB) {

    int scalar = rand();
    std::vector<int> result(vecA.size());

    for (size_t i = 0; i < vecA.size(); ++i) {
        result[i] = vecA[i] * scalar;
    }

    return result;

}

// Multiplication by scalar operation for sparse vector
SparseVector<int> multiplySparseVectorByScalar(const SparseVector<int>& vecA, const SparseVector<int>& vecB) {

    int scalar = rand();

    return vecA * scalar; // Use overloaded * operator

}



/*               Matrix Functions               */
// Function to create a random dense matrix
std::vector<std::vector<int>> createDenseMatrix(int rows, int cols, float sparsity) {

    std::vector<std::vector<int>> mat(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (static_cast<float>(rand()) / RAND_MAX > sparsity) { // Fill with non-zero values based on sparsity
                mat[i][j] = rand() % 10 + 1; // Random values from 1 to 10
            }
        }
    }
    
    return mat;

}

// Function to measure the time for an operation on a dense matrix
template<typename Func>
double measureDenseMatrixOperation(const std::vector<std::vector<int>>& matA,
    const std::vector<std::vector<int>>& matB,
    Func operation) {

    auto start = std::chrono::high_resolution_clock::now();
    operation(matA, matB);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count(); // Return time in milliseconds

}

// Function to measure the time for an operation on a sparse matrix
template<typename Func>
double measureSparseMatrixOperation(const SparseMatrix<int>& matA,
    const SparseMatrix<int>& matB,
    Func operation) {
        
    auto start = std::chrono::high_resolution_clock::now();
    operation(matA, matB);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count(); // Return time in milliseconds

}

// Addition operation for dense matrix
std::vector<std::vector<int>> addDenseMatrices(const std::vector<std::vector<int>>& matA,
    const std::vector<std::vector<int>>& matB) {

    int rows = matA.size();
    int cols = matA[0].size();
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matA[i][j] + matB[i][j];
        }
    }

    return result;

}

// Addition operation for sparse matrix
SparseMatrix<int> addSparseMatrices(const SparseMatrix<int>& matA, const SparseMatrix<int>& matB) {

    return matA + matB; // Use overloaded + operator

}

// Multiplication operation for dense matrix
std::vector<std::vector<int>> multiplyDenseMatrices(const std::vector<std::vector<int>>& matA,
    const std::vector<std::vector<int>>& matB) {

    int rowsA = matA.size();
    int colsA = matA[0].size();
    int colsB = matB[0].size();

    // Ensure the number of columns in A equals the number of rows in B
    if (colsA != matB.size()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    std::vector<std::vector<int>> result(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }

    return result;

}

// Multiplication operation for sparse matrix
SparseMatrix<int> multiplySparseMatrices(const SparseMatrix<int>& matA, const SparseMatrix<int>& matB) {

    return matA * matB;

}

// Multiplication by scalar operation for dense matrix
std::vector<std::vector<int>> multiplyDenseMatrixByScalar(const std::vector<std::vector<int>>& matA, 
    const std::vector<std::vector<int>>& matB) {

    int scalar = rand();
    int rows = matA.size();
    int cols = matA[0].size();

    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matA[i][j] * scalar;
        }
    }

    return result;

}

// Multiplication by scalar operation for sparse matrix
SparseMatrix<int> multiplySparseMatrixByScalar(const SparseMatrix<int>& matA, const SparseMatrix<int>&  matB) {

    int scalar = rand();
    return matA * scalar;

}


int main() {
    const float sparsity = 0.99; // 99% sparse


    std::cout << "\n====== Vector Testing ========\n";

    int size = 10000;

    // Create dense vectors
    vector<int> denseVA = createDenseVector(size, sparsity);
    vector<int> denseVB = createDenseVector(size, sparsity);

    // Create sparse vectors
    SparseVector<int> sparseVectorA (size);
    SparseVector<int> sparseVectorB(size);

    for (int i = 0; i < size; ++i) {
            if (denseVA[i] != 0) sparseVectorA.set(i, denseVA[i]);
            if (denseVB[i] != 0) sparseVectorB.set(i,  denseVB[i]);
    }


    // Measure time for addition on dense vector
    double denseVAddTime = measureDenseVectorOperation(denseVA, denseVB, addDenseVectors);
    std::cout << "Dense Vector Addition Time: " << std::fixed << std::setprecision(2) << denseVAddTime << " ms | ";

    // Measure time for addition on sparse vector
    double sparseVAddTime = measureSparseVectorOperation(sparseVectorA, sparseVectorB, addSparseVectors);
    std::cout << "Sparse Vector Addition Time: " << std::fixed << std::setprecision(2) << sparseVAddTime << " ms \n";

    // Measure time for dot product on dense vector
    double denseVDotTime = measureDenseVectorOperation(denseVA, denseVB, dotProductDenseVectors);
    std::cout << "Dense Vector dot product Time: " << std::fixed << std::setprecision(2) << denseVDotTime << " ms | ";

    // Measure time for dot product on sparse vector
    double sparseVDotTime = measureSparseVectorOperation(sparseVectorA, sparseVectorB, dotProductSparseVectors);
    std::cout << "Sparse Vector Dot Product Time: " << std::fixed << std::setprecision(2) << sparseVDotTime << " ms\n";

    // Measure time for multiplication by scalar on dense vector
    double denseVSMultTime = measureDenseVectorOperation(denseVA, denseVB, multiplyDenseVectorByScalar);
    std::cout << "Dense Vector Multiplication by scalar Time: " << std::fixed << std::setprecision(2) << denseVSMultTime << " ms | ";

    // Measure time for multiplication by scalar on sparse vector
    double sparseVSMultTime = measureSparseVectorOperation(sparseVectorA, sparseVectorB, multiplySparseVectorByScalar);
    std::cout << "Sparse Vector Multiplication by Scalar Time: " << std::fixed << std::setprecision(2) << sparseVSMultTime << " ms \n";


    std::cout << "\n====== Matrix Testing ========\n";

    const int rows = 1000;
    const int cols = 1000;

    // Create dense matrices
    auto denseMatrixA = createDenseMatrix(rows, cols, sparsity);
    auto denseMatrixB = createDenseMatrix(rows, cols, sparsity);

    // Create sparse matrices
    SparseMatrix<int> sparseMatrixA(rows, cols);
    SparseMatrix<int> sparseMatrixB(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (denseMatrixA[i][j] != 0) sparseMatrixA.set(i, j, denseMatrixA[i][j]);
            if (denseMatrixB[i][j] != 0) sparseMatrixB.set(i, j, denseMatrixB[i][j]);
        }
    }

    // Measure time for addition on dense matrix
    double denseMAddTime = measureDenseMatrixOperation(denseMatrixA, denseMatrixB, addDenseMatrices);
    std::cout << "Dense Matrix Addition Time: " << std::fixed << std::setprecision(2) << denseMAddTime << " ms | ";

    // Measure time for addition on sparse matrix
    double sparseMAddTime = measureSparseMatrixOperation(sparseMatrixA, sparseMatrixB, addSparseMatrices);
    std::cout << "Sparse Matrix Addition Time: " << std::fixed << std::setprecision(2) << sparseMAddTime << " ms\n";

    // Measure time for multiplication on dense matrix
    double denseMMultTime = measureDenseMatrixOperation(denseMatrixA, denseMatrixB, multiplyDenseMatrices);
    std::cout << "Dense Matrix Multiplication Time: " << std::fixed << std::setprecision(2) << denseMMultTime << " ms | ";

    // Measure time for multiplication on sparse matrix
    double sparseMMultTime = measureSparseMatrixOperation(sparseMatrixA, sparseMatrixB, multiplySparseMatrixByScalar);
    std::cout << "Sparse Matrix Multiplication Time: " << std::fixed << std::setprecision(2) << sparseMMultTime << " ms\n";

    // Measure time for multiplication by scalar on dense matrix
    double denseMSMultTime = measureDenseMatrixOperation(denseMatrixA, denseMatrixB, multiplyDenseMatrixByScalar);
    std::cout << "Dense Matrix Multiplication by scalar Time: " << std::fixed << std::setprecision(2) << denseMSMultTime << " ms | ";

    // Measure time for multiplication by scalar on sparse matrix
    double sparseMSMultTime = measureSparseMatrixOperation(sparseMatrixA, sparseMatrixB, multiplySparseMatrices);
    std::cout << "Sparse Matrix Multiplication by scalar Time: " << std::fixed << std::setprecision(2) << sparseMSMultTime << " ms\n";

    return 0;
}