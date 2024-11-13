#include <iostream>
#include <chrono>

using namespace std; // Enables direct use of names in the std namespace

int main() {
    const int numIterations = 1000000; // Number of iterations

    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    // Loop to be timed
    long long sum = 0;
    for (int i = 0; i < numIterations; ++i) {
        sum += i; // Simple operation to add up the numbers
    }

    // End the timer
    auto end = chrono::high_resolution_clock::now();

    // Calculate the elapsed time in microseconds
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken by the loop: " << duration.count() << " microseconds\n";

    // Display the result of the loop calculation (optional)
    cout << "Sum: " << sum << '\n';

    return 0;
}
