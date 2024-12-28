# Лабораторная работа №4 по курсу «Программирование на C++»

## Работа с разреженными векторами и матрицами

В случае, когда подавляющее большинство элементов вектора или матрицы равны нулю, имеет смысл использовать структуры данных, которые существенно экономят память за счёт того, что нулевые элементы не сохраняются.

## Решение

Код разделён на 4 файла:

- **SparseVector.h**
- **SparseMatrix.h**
- **main.cpp**
- **compare.cpp**

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
