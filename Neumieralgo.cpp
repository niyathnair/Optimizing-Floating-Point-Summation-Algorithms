#include <iostream>
#include <vector>
#include <cmath>

// Function to compute the sum using single precision arithmetic
float SinglePrecisionSum(const std::vector<float>& numbers) {
    float sum = 0.0f;
    for (const auto& number : numbers) {
        sum += number;
    }
    return sum;
}

// Neumaier Summation Algorithm
double NeumaierSummation(const std::vector<double>& numbers) {
    double sum = numbers[0];
    double compensation = 0.0;

    for (size_t i = 1; i < numbers.size(); ++i) {
        double corrected_number = numbers[i] - compensation;
        double temp_sum = sum + corrected_number;
        compensation = (std::abs(sum) >= std::abs(corrected_number)) ?
                       (sum - temp_sum) + corrected_number : (corrected_number - temp_sum) + sum;
        sum = temp_sum;
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

    // Compute the sum using Neumaier summation algorithm
    double neumaier_result = NeumaierSummation(std::vector<double>(numbers.begin(), numbers.end()));
    std::cout << "Neumaier Summation Result: " << neumaier_result << std::endl;

    // Compare the results and explain why Neumaier summation is better
    if (std::abs(neumaier_result - single_precision_result) < 1e-5) {
        std::cout << "Neumaier summation provides better accuracy compared to regular summation." << std::endl;
    } else {
        std::cout << "Regular summation may introduce significant rounding errors, leading to loss of accuracy." << std::endl;
    }

    return 0;
}
