# Lab Assignment #4 for the C++ Programming Course

## Working with Sparse Vectors and Matrices

When the overwhelming majority of elements in a vector or matrix are equal to zero, it makes sense to use data structures that significantly save memory by not storing the zero elements.

### **Task:**

Develop template classes for storing sparse vectors and 2D matrices. To do this:

1. **Propose data structures** for storing the values of the original vectors and matrices. _(Hint: Using hash tables is a good idea)_. Consider the need for supporting custom iterators.

2. **Implement a set of unary and binary operations** for vectors and matrices, including:

   - Transposition
   - Addition
   - Vector multiplication (recall linear algebra)
   - Matrix inversion
   - Matrix exponentiation _(provide two options: with an integer and a floating-point exponent)_.
     - Think about how to handle matrix exponentiation: exponentiation is only applicable to square matrices. Should a separate class be created for square and rectangular matrices, or is there an alternative solution?
   - Multiplication of a vector and a matrix

3. **Implement element-wise operations** for vector and matrix elements:

   - Arithmetic operations with scalar values
   - Element-wise exponentiation

4. **Compare performance** of your proposed storage and processing approach for sparse matrices with the performance of performing the same operations on vectors and matrices stored using the standard `vector` container.

5. **Document the results** in the form of a report or a README file if the code is uploaded to GitHub.
