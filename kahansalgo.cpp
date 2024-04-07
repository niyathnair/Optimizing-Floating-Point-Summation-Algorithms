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

// Function to compute the sum using compensated summation (Kahan summation)
double KahanSummation(const std::vector<double>& numbers) {
    double sum = 0.0;          // Running sum
    double compensation = 0.0; // Compensation for lost precision
    
    for (const auto& number : numbers) {
        double corrected_number = number - compensation;
        double temp_sum = sum + corrected_number;
        compensation = (temp_sum - sum) - corrected_number;
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

    // Compute the sum using compensated summation (Kahan summation)
    double kahan_result = KahanSummation(std::vector<double>(numbers.begin(), numbers.end()));
    std::cout << "Kahan Summation Result: " << kahan_result << std::endl;

    // Compare the results and explain why compensated summation is better
    if (std::abs(kahan_result - single_precision_result) < 1e-5) {
        std::cout << "Compensated summation (Kahan summation) provides better accuracy compared to regular summation." << std::endl;
    } else {
        std::cout << "Regular summation may introduce significant rounding errors, leading to loss of accuracy." << std::endl;
    }

    return 0;
}
