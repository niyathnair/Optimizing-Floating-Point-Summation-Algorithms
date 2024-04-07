#include <iostream>
#include <vector>
// #include <omp.h>

// Function to compute the sum using single precision arithmetic
float SinglePrecisionSum(const std::vector<float>& numbers) {
    float sum = 0.0f;
    for (const auto& number : numbers) {
        sum += number;
    }
    return sum;
}

// Function to compute the sum of an array in parallel using OpenMP
double ParallelSummation(const std::vector<double>& numbers) {
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (size_t i = 0; i < numbers.size(); ++i) {
        sum += numbers[i];
    }

    return sum;
}

int main() {
    // Generate a large vector of numbers
    std::vector<float> numbers;
    for (int i = 1; i <= 1000000; ++i) {
        numbers.push_back(1.0f / i); // Adding decreasing values to highlight precision issues
    }

    // Compute the sum using single precision arithmetic
    float single_precision_result = SinglePrecisionSum(numbers);
    std::cout << "Single Precision Sum: " << single_precision_result << std::endl;

    // Compute the sum in parallel
    double parallel_result = ParallelSummation(std::vector<double>(numbers.begin(), numbers.end()));
    std::cout << "Parallel Summation Result: " << parallel_result << std::endl;

    return 0;
}
