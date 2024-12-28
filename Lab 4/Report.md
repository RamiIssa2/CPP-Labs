# Лабораторная работа №4 по курсу «Программирование на C++»

## Работа с разреженными векторами и матрицами

В случае, когда подавляющее большинство элементов вектора или матрицы равны нулю, имеет смысл использовать структуры данных, которые существенно экономят память за счёт того, что нулевые элементы не сохраняются.

## Решение

Код разделён на 4 файла:

- **SparseVector.h**
- **SparseMatrix.h**
- **main.cpp**
- **compare.cpp**

---

### SparseVector.h

В этом файле класс `SparseVector` определён с двумя свойствами:

- **`elements`:** использует `std::unordered_map` для хранения элементов вектора типа `T`.
- **`size`:** размер вектора.

```cpp
template <typename T>
class SparseVector {
private:
    std::unordered_map<size_t, T> elements; // Stores non-zero elements
    size_t size; // Total size of the vector
```

А также функции класса `SparseVector`:

- Конструктор

```cpp
// Constructor
SparseVector(size_t size) : size(size) {}
```

- Функция для получения размера вектора

```cpp
// Get the size of the vector
size_t getSize() const {
    return size;
}
```

- Функция для получения значения по определённому индексу

```cpp
// Get a value at a specific index (read-only)
T get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    auto it = elements.find(index);
    return (it != elements.end()) ? it->second : T(0);
}
```

- Функция для установки значения по определённому индексу

```cpp
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
```

- Оператор доступа

```cpp
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
```

- Бинарные операции:
  - Оператор сложения
  ```cpp
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
  ```
  - Оператор умножения
  ```cpp
  SparseVector<T> operator*(const T& scalar) const {
      SparseVector<T> result(size);
      for (const auto& [index, value] : elements) {
          result.elements[index] = value * scalar;
      }
      return result;
  }
  ```
- Поэлементные операции:
  - Оператор возведения в степень
  ```cpp
  SparseVector<T> operator^(const T& exponent) const {
      SparseVector<T> result(size);
      for (const auto& [index, value] : elements) {
          result.elements[index] = std::pow(value, exponent);
      }
      return result;
  }
  ```
- Функция скалярного произведения

```cpp
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
```

- Функция вывода

```cpp
// Print function
void print() const {
    std::map<size_t, T> sorted_elements(elements.begin(), elements.end()); // Use std::map for sorted traversal

    std::cout << "SparseVector: { ";
    for (const auto& [index, value] : sorted_elements) {
        std::cout << "(" << index << ": " << value << ") ";
    }
    std::cout << "} Size: " << size << std::endl;
}
```

- Класс итератора для ненулевых элементов

```cpp
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
```

---

### SparseMatrix.h

В этом файле класс `SparseMatrix` определён с тремя свойствами:

- **`elements`:** использует два вложенных `std::unordered_map` для хранения элементов матрицы типа `T`.
- **`rows`:** количество строк в матрице.
- **`cols`:** количество столбцов в матрице.

```cpp
template <typename T>
class SparseMatrix {
private:
    std::unordered_map<size_t, std::unordered_map<size_t, T>> elements; // Non-zero elements stored as {row -> {col -> value}}
    size_t rows, cols; // Dimensions of the matrix
```

А также функции класса `SparseMatrix`:

- Конструктор

```cpp
// Constructor
SparseMatrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}
```

- Геттеры для размеров матрицы

```cpp
// Getters for dimensions
size_t getRows() const {
    return rows;
}

size_t getCols() const {
    return cols;
}
```

- Функция для получения значения

```cpp
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
```

- Функция для установки значения

```cpp
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
```

- Функция для транспонирования матрицы

```cpp
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
```

- Оператор сложения

```cpp
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
```

- Оператор умножения на скаляр

```cpp
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
```

- Оператор умножения матриц

```cpp
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
```

- Оператор возведения матрицы в степень

```cpp
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
```

- Функция для вычисления обратной матрицы

```cpp
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
```

- Функция вывода

```cpp
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
```

---

### main.cpp

В этом файле протестированы определённые классы `SparseVector` и `SparseMatrix` с их функциями:

- **Тестирование SparseVector:**

```cpp
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
```

**Вывод:**

```plaintext
Testing SparseVector
Vector elements:
SparseVector: { (1: 10) (3: 20) } Size: 5

Vector multiplied by scalar 2:
SparseVector: { (1: 20) (3: 40) } Size: 5

Vector added to itself:
SparseVector: { (1: 20) (3: 40) } Size: 5
Dot product of vec with itself: 500
Exponentiation of vec with ^2:
SparseVector: { (1: 100) (3: 400) } Size: 5
```

- **Тестирование SparseMatrix:**

```cpp
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
```

**Вывод:**

```plaintext
Testing SparseMatrix
Matrix elements:
SparseMatrix: 3x3
(0, 0): 1
(0, 1): 2
(1, 1): 3
(2, 2): 4

Transpose of the matrix:
SparseMatrix: 3x3
(0, 0): 1
(1, 0): 2
(1, 1): 3
(2, 2): 4

Matrix multiplied by scalar 2:
SparseMatrix: 3x3
(0, 0): 2
(0, 1): 4
(1, 1): 6
(2, 2): 8

Matrix added to itself:
SparseMatrix: 3x3
(0, 0): 2
(0, 1): 4
(1, 1): 6
(2, 2): 8

Matrix multiplied by itself:
SparseMatrix: 3x3
(0, 0): 1
(0, 1): 8
(1, 1): 9
(2, 2): 16

Matrix raised to power 2:
SparseMatrix: 3x3
(0, 0): 1
(0, 1): 8
(1, 1): 9
(2, 2): 16

Inverse of the matrix:
SparseMatrix: 3x3
(0, 0): 1
(0, 1): -0.666667
(1, 1): 0.333333
(2, 2): 0.25
```

- **Тестирование SparseMatrix #2:**

```cpp
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
```

**Вывод:**

```plaintext
Testing SparseMatrix #2
Matrix elements:
SparseMatrix: 3x3
(0, 0): -3
(0, 1): 2
(0, 2): -1
(1, 0): 6
(1, 1): -6
(1, 2): 7
(2, 0): 3
(2, 1): -4
(2, 2): 4
Inverse of the matrix:
SparseMatrix: 3x3
(0, 1): 0.333333
(0, 2): -0.666667
(1, 0): 0.25
(1, 1): 0.75
(1, 2): -1.25
(2, 0): 0.5
(2, 1): 0.5
(2, 2): -0.5

Matrix multiplied by its inverse (to make sure that it works):
SparseMatrix: 3x3
(0, 0): 1
(1, 1): 1
(2, 2): 1
```

---
