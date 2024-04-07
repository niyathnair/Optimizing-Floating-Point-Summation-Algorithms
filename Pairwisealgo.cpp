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

// Pairwise Summation Algorithm
double PairwiseSummation(const std::vector<double>& numbers) {
    std::vector<double> partial_sums;
    partial_sums.reserve(numbers.size() / 2 + numbers.size() % 2); // Reserve space for partial sums
    
    for (size_t i = 0; i < numbers.size(); i += 2) {
        double sum = numbers[i];
        if (i + 1 < numbers.size()) {
            sum += numbers[i + 1];
        }
        partial_sums.push_back(sum);
    }

    return NeumaierSummation(partial_sums);
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

    // Compute the sum using Pairwise summation algorithm
    double pairwise_result = PairwiseSummation(std::vector<double>(numbers.begin(), numbers.end()));
    std::cout << "Pairwise Summation Result: " << pairwise_result << std::endl;

    // Compare the results and explain why Neumaier and Pairwise summations are better
    if (std::abs(neumaier_result - single_precision_result) < 1e-5) {
        std::cout << "Neumaier summation provides better accuracy compared to regular summation." << std::endl;
    } else {
        std::cout << "Regular summation may introduce significant rounding errors, leading to loss of accuracy." << std::endl;
    }

    if (std::abs(pairwise_result - single_precision_result) < 1e-5) {
        std::cout << "Pairwise summation provides better accuracy compared to regular summation." << std::endl;
    } else {
        std::cout << "Regular summation may introduce significant rounding errors, leading to loss of accuracy." << std::endl;
    }

    return 0;
}
