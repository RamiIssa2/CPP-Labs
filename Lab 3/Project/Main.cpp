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

    // Create a list from the top n elements
    list<Number> list1(temp.begin(), temp.begin() + n);
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

    // Create a list from the smallest n elements
    list<Number> list2(temp.begin(), temp.begin() + n);
    return list2;
}

void removeElementsFromVector(vector<Number>& vec, const list<Number>& lst) {
    vec.erase(remove_if(vec.begin(), vec.end(), [&](const Number& num) {
        // Check if num matches an element in the list (based on value for precise comparison)
        return any_of(lst.begin(), lst.end(), [&](const Number& listNum) {
            return num.getValue() == listNum.getValue(); // Match based on value
        });
    }), vec.end());
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

        // Define n
        int n = 30;

        // Form list1 with top n largest elements
        list<Number> list1 = getTopNLargest(v1, n);

        // Output the contents of list1 for verification
        cout << "\nTop " << n << " largest elements from v1 in list1:\n";

        // Form list2 with smallest n elements from v2
        list<Number> list2 = getSmallestNElements(v2, n);

        // Output the contents of list2 for verification
        cout << "\nSmallest " << n << " elements from v2 in list2:\n";
        
        // Remove elements in list1 from v1
        removeElementsFromVector(v1, list1);

        // Remove elements in list2 from v2
        removeElementsFromVector(v2, list2);

        // Output the sizes of v1 and v2 after removal
        cout << "\nSize of v1 after removing elements in list1: " << v1.size() << endl;
        cout << "Size of v2 after removing elements in list2: " << v2.size() << endl;
    } catch (const out_of_range& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}