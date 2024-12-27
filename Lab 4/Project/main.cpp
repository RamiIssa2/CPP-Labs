#include "SparseVector.h"
#include "SparseMatrix.h"
#include <iostream>

int main() {
    // Testing SparseVector
    std::cout << "Testing SparseVector" << std::endl;
    SparseVector<int> vec(5);

    // Setting and getting values
    vec.set(1, 10);
    vec.set(3, 20);
    vec.set(4, 0); // Setting to zero should remove the element

    std::cout << "Vector elements:" << std::endl;
    vec.print();

    // Scalar multiplication
    std::cout << "\nVector multiplied by scalar 3:" << std::endl;
    SparseVector<int> vec_scaled = vec * 3;
    vec_scaled.print();

    // Matrix addition
    std::cout << "\nVector added to itself:" << std::endl;
    SparseVector<int> vec_sum = vec + vec;
    vec_sum.print();

    std::cout << "\nDot product of vec with itself: " << vec.dot(vec) << std::endl;

    std::cout << "\nExponentiation of vec with ^2:" << std::endl;
    SparseVector<int> vec_exp = vec ^ 2;
    vec_exp.print();

    // Testing SparseMatrix
    std::cout << "\nTesting SparseMatrix" << std::endl;
    SparseMatrix<double> mat(3, 3);

    // Setting matrix values
    mat.set(0, 0, 1.0);
    mat.set(0, 1, 2.0);
    mat.set(1, 1, 3.0);
    mat.set(2, 2, 4.0);

    std::cout << "Matrix elements:" << std::endl;
    mat.print();

    // Transpose
    std::cout << "\nTranspose of the matrix:" << std::endl;
    SparseMatrix<double> mat_trans = mat.transpose();
    mat_trans.print();

    // Scalar multiplication
    std::cout << "\nMatrix multiplied by scalar 2:" << std::endl;
    SparseMatrix<double> mat_scaled = mat * 2.0;
    mat_scaled.print();

    // Matrix addition
    std::cout << "\nMatrix added to itself:" << std::endl;
    SparseMatrix<double> mat_sum = mat + mat;
    mat_sum.print();

    // Matrix multiplication
    std::cout << "\nMatrix multiplied by itself:" << std::endl;
    SparseMatrix<double> mat_prod = mat * mat;
    mat_prod.print();

    // Matrix exponentiation
    std::cout << "\nMatrix raised to power 2:" << std::endl;
    SparseMatrix<double> mat_exp = mat ^ 2;
    mat_exp.print();

    // Inverse (only applicable for invertible square matrices)
    try {
        std::cout << "\nInverse of the matrix:" << std::endl;
        SparseMatrix<double> mat_inv = mat.inverse();
        mat_inv.print();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Testing SparseMatrix #2
    std::cout << "\nTesting SparseMatrix #2" << std::endl;
    SparseMatrix<double> mat2(3, 3);

    // Setting matrix values
    mat2.set(0, 0, -3.0);
    mat2.set(0, 1, 2.0);
    mat2.set(0, 2, -1.0);
    mat2.set(1, 0, 6.0);
    mat2.set(1, 1, -6.0);
    mat2.set(1, 2, 7.0);
    mat2.set(2, 0, 3.0);
    mat2.set(2, 1, -4.0);
    mat2.set(2, 2, 4.0);

    std::cout << "Matrix elements:" << std::endl;
    mat2.print();

    // Inverse (only applicable for invertible square matrices)
    try {
        std::cout << "\nInverse of the matrix:" << std::endl;
        SparseMatrix<double> mat2_inv = mat2.inverse();
        mat2_inv.print();

        std::cout << "\nMatrix multiplied by its inverse (to make sure that it works):" << std::endl;
        SparseMatrix<double> mat2_prod = mat2 * mat2_inv;
        mat2_prod.print();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}