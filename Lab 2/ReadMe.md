# Lab Assignment #2 for the C++ Programming Course

## Task Description:

You need to design a class that implements the storage of data related to a class instance in dynamic memory. This could be, for example, a representation of integers, where, in addition to an int value, the string representation of the number (e.g., 22 and "twenty-two") is also stored. (This example is conditional.)

For this class, you need to implement all necessary constructors, including copy and move constructors, as well as a destructor. All constructors and the destructor should "report" their calls, for example:

    std::cout << "Copy constructor" << std::endl;

The same applies to the overloaded assignment operator (two variants: without and with move semantics).

## Requirements:

- Class Definition:
  Place the class definition in a header file (`.hpp`).
  Implement class methods in a separate `.cpp` file.

- Program Implementation:
  Write a separate `.cpp` module to work with instances of the developed class. This program must demonstrate:
  1. Creation of both static and dynamic class instances.
  2. Use of a standard C-style vector to handle instances. Write a function to process this vector.
  3. Passing class instances to functions and returning an instance from a function, including by reference.
  4. Working with the developed class by creating vectors and lists of class instances using the standard `std::vector` and `std::list`, with lengths between 5 and 10.

## Tasks to Demonstrate:

- Analyze the creation and destruction processes of class instances in different examples.
- Ensure all constructors, destructors, and overloaded assignment operators produce output to confirm their invocation.

## Deliverables:

1. A report summarizing the work done.
2. Output results from program runs, including logs from constructors, destructors, and overloaded operators.
3. Conclusions based on program execution results.
