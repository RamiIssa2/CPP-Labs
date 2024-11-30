#include "Number.cpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <unordered_set>

using namespace std;

// Function to generate a random vector of Numbers
vector<Number> createRandomVector() {
    // Random number generator setup
    random_device rd; // Seed
    mt19937 gen(rd()); // Mersenne Twister generator
    uniform_int_distribution<> sizeDist(500, 1000); // Size between 500 and 1000
    uniform_int_distribution<> valueDist(1, 1000); // Random values between 1 and 1,000

    // Generate a random size
    int size = sizeDist(gen);

    // Create the vector
    vector<Number> v1(size);

    // Set to track already-used values
    unordered_set<int> usedValues;

    // Lambda function to generate unique values
    auto uniqueNumberGenerator = [&]() -> Number {
        int randomValue;
        do {
            randomValue = valueDist(gen); // Generate a random number
        } while (usedValues.find(randomValue) != usedValues.end()); // Ensure uniqueness

        usedValues.insert(randomValue); // Track the new value
        return Number(randomValue);    // Create and return a Number object
    };

    // Populate the vector using std::generate
    generate(v1.begin(), v1.end(), uniqueNumberGenerator);

    return v1;
}

// Function to create a subrange vector
vector<Number> createSubrange(const vector<Number>& v1, int b, int e) {
    // Ensure bounds are valid
    if (b < 0 || e > v1.size() || b >= e) {
        throw out_of_range("Invalid range for subrange creation.");
    }

    vector<Number> v2(e - b); // Create a vector with the required size
    copy(v1.begin() + b, v1.begin() + e, v2.begin()); // Copy the subrange into v2
    return v2;
}

// Function to extract top n largest elements from v1 and form a list
list<Number> getTopNLargest(const vector<Number>& v1, int n) {
    if (n > v1.size() || n < 0) {
        throw out_of_range("Invalid value of n for top N largest elements.");
    }

    // Create a copy of v1 for sorting
    vector<Number> temp(v1);

    // Sort the largest n elements in descending order
    partial_sort(temp.begin(), temp.begin() + n, temp.end(), [](const Number& a, const Number& b) {
        return a.getValue() > b.getValue(); // Sort by value descending
    });

    // Create the list
    list<Number> list1(n);

    // Get the largest n elements from v1
    copy_if(v1.begin(), v1.end(), list1.begin(), [temp, n](const Number& num) {
        return num.getValue() >= temp[n - 1].getValue();
    });

    return list1;
}

// Function to extract smallest n elements from v2 and form a list
list<Number> getSmallestNElements(const vector<Number>& v2, int n) {
    if (n > v2.size() || n < 0) {
        throw out_of_range("Invalid value of n for smallest N elements.");
    }

    // Create a copy of v2 for partial sorting
    vector<Number> temp(v2);

    // Find the smallest n elements
    partial_sort(temp.begin(), temp.begin() + n, temp.end(), [](const Number& a, const Number& b) {
        return a.getValue() < b.getValue(); // Sort by value ascending
    });

    // Create the list
    list<Number> list2(n);

    // Get the smallest n elements from v2
    copy_if(v2.begin(), v2.end(), list2.begin(), [temp, n](const Number& num) {
        return num.getValue() <= temp[n - 1].getValue();
    });

    return list2;
}

// Function to remove elements from a vector that are in the list
void removeElementsFromVector(vector<Number>& vec, const list<Number>& lst) {
    vec.erase(remove_if(vec.begin(), vec.end(), [&](const Number& num) {
        // Check if num matches an element in the list (based on value for precise comparison)
        return any_of(lst.begin(), lst.end(), [&](const Number& listNum) {
            return num.getValue() == listNum.getValue(); // Match based on value
        });
    }), vec.end());
}

// Function to rearrange list by median
void rearrangeListByMedian(list<Number>& lst) {
    if (lst.empty()) {
        throw invalid_argument("List is empty. Cannot rearrange by median.");
    }

    // Step 1: Copy list to a vector for random access
    vector<Number> temp(lst.begin(), lst.end());

    // Step 2: Sort the vector to find the median
    sort(temp.begin(), temp.end(), [](const Number& a, const Number& b) {
        return a.getValue() < b.getValue(); // Sort ascending
    });

    // Step 3: Find the median element
    int medianIndex = temp.size() / 2;
    int medianValue = temp[medianIndex].getValue(); // Median value

    // Step 4: Partition the list based on the median value
    auto partitionPoint = partition(lst.begin(), lst.end(), [medianValue](const Number& num) {
        return num.getValue() > medianValue; // Greater than median
    });

    // Re-sort the second partition to maintain relative order
    lst.splice(lst.end(), lst, partitionPoint, lst.end());
}

// Function to remove odd elements form a list
void removeOddElements(list<Number>& lst) {
    // Remove elements where value is odd
    lst.remove_if([](const Number& num) {
        return num.getValue() % 2 != 0; // Check if value is odd
    });
}

// Function to create common elements vector v3 from the vectors v1 and v2
vector<Number> createCommonElementsVector(const vector<Number>& v1, const vector<Number>& v2) {
    // Create the vector
    vector<Number> v3;
    
    // Check v1 for common elements with v2 and add them to v3
    copy_if(v1.begin(), v1.end(), back_inserter(v3), [&](const Number& num) {
        return any_of(v2.begin(), v2.end(), [&](const Number& vectorNum) {
            return num.getValue() == vectorNum.getValue(); // Match based on value
        });
    });

    return v3;
}

// Function to Equalize List Sizes
void equalizeListSizes(list<Number>& list1, list<Number>& list2) {
    if (list1.size() > list2.size()) {
        auto it = list1.begin();
        std::advance(it, list1.size() - list2.size()); // Move iterator forward by the difference
        list1.erase(list1.begin(), it); // Erase the first `n` elements
    } else if (list2.size() > list1.size()) {
        auto it = list2.begin();
        std::advance(it, list2.size() - list1.size()); // Move iterator forward by the difference
        list2.erase(list2.begin(), it); // Erase the first `n` elements
    }
}

// Function to Create list3
list<pair<Number, Number>> formList3(const list<Number>& list1, const list<Number>& list2) {
    list<pair<Number, Number>> list3;

    // Use std::transform to create pairs
    transform(list1.begin(), list1.end(), list2.begin(), back_inserter(list3),
              [](const Number& num1, const Number& num2) {
                  return make_pair(num1, num2); // Pair elements from list1 and list2
              });

    return list3;
}

int main() {

    try {
        // Generate vector v1
        vector<Number> v1 = createRandomVector();

        // Output the contents of v1 for verification
        cout << "Generated vector v1 with " << v1.size() << " elements.\n";
        
        // Define subrange bounds (last 200 elements)
        int b = v1.size() - 200;
        int e = v1.size();

        // Create vector v2 from subrange of v1
        vector<Number> v2 = createSubrange(v1, b, e);

        // Output the contents of v2 for verification
        cout << "\nCreated vector v2 with " << v2.size() << " elements (subrange).\n";

        // Define n for list1
        int n1 = 30;

        // Form list1 with top n largest elements
        list<Number> list1 = getTopNLargest(v1, n1);

        // Output the contents of list1 for verification
        cout << "\nTop " << n1 << " largest elements from v1 in list1:\n";

        // Define n for list2
        int n2 = 30;

        // Form list2 with smallest n elements from v2
        list<Number> list2 = getSmallestNElements(v2, n2);

        // Output the contents of list2 for verification
        cout << "\nSmallest " << n2 << " elements from v2 in list2:\n";
        
        // Remove elements in list1 from v1
        removeElementsFromVector(v1, list1);

        // Remove elements in list2 from v2
        removeElementsFromVector(v2, list2);

        // Output the sizes of v1 and v2 after removal
        cout << "\nSize of v1 after removing elements in list1: " << v1.size() << endl;
        cout << "Size of v2 after removing elements in list2: " << v2.size() << endl;

        // Rearrange list1 based on the median
        rearrangeListByMedian(list1);

        // Output the rearranged list1
        cout << "\nList1 rearranged by median value of size " << list1.size() << ".\n";
        
        // Remove odd elements from list2
        removeOddElements(list2);

        // Output the updated list2
        cout << "\nList2 after removing odd elements of size " << list2.size() << ".\n";
        
        // Create v3 with common elements of v1 and v2
        vector<Number> v3 = createCommonElementsVector(v1, v2);

        // Output the contents of v3
        cout << "\nVector v3 (common elements of v1 and v2) of size " << v3.size() << ".\n";

        // Equalize the sizes of list1 and list2 using std::advance
        equalizeListSizes(list1, list2);

        // Form list3 with pairs from list1 and list2 using std::transform
        list<pair<Number, Number>> list3 = formList3(list1, list2);

        // Output the contents of list3
        cout << "\nList3 (pairs of elements from list1 and list2) of size " << list3.size() << ":\n";
        for (const auto& [num1, num2] : list3) {
            cout << "(" << num1 << ", " << num2 << ")\n";
        }
    } catch (const out_of_range& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}