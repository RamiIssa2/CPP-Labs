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
    uniform_int_distribution<> valueDist(1, 1000000); // Random values between 1 and 1,000,000

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

int main() {

    // Generate vector v1
    vector<Number> v1 = createRandomVector();

    // Output the contents of v1 for verification
    cout << "Generated vector v1 with " << v1.size() << " elements:\n";
    for (const auto& num : v1) {
        cout << num << "\n";
    }

    return 0;
}