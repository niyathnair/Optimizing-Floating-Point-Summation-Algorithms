#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent an interval
struct Interval {
    double lower;
    double upper;

    Interval(double lower_, double upper_) : lower(lower_), upper(upper_) {}

    // Interval addition
    Interval operator+(const Interval& other) const {
        return Interval(lower + other.lower, upper + other.upper);
    }

    // Interval subtraction
    Interval operator-(const Interval& other) const {
        return Interval(lower - other.upper, upper - other.lower);
    }

    // Interval multiplication
    Interval operator*(const Interval& other) const {
        double products[4] = { lower * other.lower, lower * other.upper,
                               upper * other.lower, upper * other.upper };
        double min = products[0];
        double max = products[0];
        for (int i = 1; i < 4; ++i) {
            if (products[i] < min) min = products[i];
            if (products[i] > max) max = products[i];
        }
        return Interval(min, max);
    }

    // Interval division
    Interval operator/(const Interval& other) const {
        if (other.lower <= 0.0 && other.upper >= 0.0) {
            std::cerr << "Error: Division by an interval containing zero." << std::endl;
            return Interval(0.0, 0.0);
        }
        double recip_lower = 1.0 / other.upper;
        double recip_upper = 1.0 / other.lower;
        return (*this) * Interval(recip_lower, recip_upper);
    }
};

// Function to compute the sum using single precision arithmetic
float SinglePrecisionSum(const std::vector<float>& numbers) {
    float sum = 0.0f;
    for (const auto& number : numbers) {
        sum += number;
    }
    return sum;
}

// Function to compute the sum using interval arithmetic
Interval IntervalSummation(const std::vector<double>& numbers) {
    Interval sum(0.0, 0.0);
    for (const auto& number : numbers) {
        sum = sum + Interval(number, number);
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

    // Compute the sum using interval arithmetic
    Interval interval_result = IntervalSummation(std::vector<double>(numbers.begin(), numbers.end()));
    std::cout << "Interval Summation Result: [" << interval_result.lower << ", " << interval_result.upper << "]" << std::endl;

    return 0;
}
