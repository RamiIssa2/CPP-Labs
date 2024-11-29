# Lab Assignment #3 for the C++ Programming Course

## Using the Standard Template Library (STL): Containers and Algorithms

The assignment consists of a sequence of interconnected tasks.  
**Main Objective:** For each task, solve the formulated problem as efficiently as possible. For most tasks, except possibly the first, using loops will not be considered a correct solution.

## Tasks:

1. **Create a vector `v1`** with a size between 500 and 1000 elements. The number of elements is unknown until the program runs. The elements of the vector are instances of the class from Lab Work №2, with arbitrary (random) values. If necessary, this class should be updated to handle the tasks of this lab work.

2. **Create a vector `v2`**, placing the last 200 elements of `v1` into it. Consider a generalized solution for arbitrary values of `b` and `e`, which specify the positions of the first and last copied elements.

3. **Form a list `list1`**, placing the first `n` (from 20 to 50) largest elements of `v1` into it. The specified elements should be sorted before being added to the list.

4. **Form a list `list2`**, placing the last `n` (from 20 to 50) smallest elements of `v2` into it. The order of the elements is not important.

5. **Remove the moved elements** from vectors `v1` and `v2`. Adjust the sizes of the vectors after the removal of elements.

6. **For list `list1`**, find the element with the median value. Rearrange the list's elements so that all elements greater than the median are placed at the beginning.

7. **Remove all odd elements** from `list2` (or use another criterion that uniquely divides the instances of your class into two non-overlapping sets).

8. **Create a vector `v3`** from the elements that are present in both `v1` and `v2`.

9. **For lists `list1` and `list2`**, from the list with the larger number of elements, remove the first `n` elements so that both lists have the same size. Form a new list `list3`, which will store pairs:
   `<first element of list1, first element of list2>`, `<second element of list1, second element of list2>`, and so on.

10. **Solve the previous task for vectors `v1` and `v2`** without first resizing the vectors to the same size. There should be no pairs with empty values.

## Deliverables:

Prepare a report and upload it according to the established rules.

**Note on Efficiency**: Efficiency here refers to solutions that use minimal code and avoid unnecessary operations.
