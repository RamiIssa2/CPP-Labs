#include "Number.cpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>

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

    // Populate the vector with random Number objects
    generate(v1.begin(), v1.end(), [&]() {
        return Number(valueDist(gen));
    });

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

int main() {

    // Generate vector v1
    vector<Number> v1 = createRandomVector();

    // Output the contents of v1 for verification
    cout << "Generated vector v1 with " << v1.size() << " elements.\n";
    
    // Define subrange bounds (last 200 elements)
    int b = v1.size() - 200;
    int e = v1.size();

    // Create vector v2 from subrange of v1
    try {
        vector<Number> v2 = createSubrange(v1, b, e);

        // Output the contents of v2 for verification
        cout << "\nCreated vector v2 with " << v2.size() << " elements (subrange):\n";
        for (const auto& num : v2) {
            cout << num << "\n";
        }
    } catch (const out_of_range& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}