#pragma once

#include <vector>
#include <string>
#include <numbers>
#include <random>
#include <ranges>
#include <stdexcept>

namespace math_utils {

std::vector<double> GenerateUniformRandomNumbers(std::size_t n, std::mt19937 &random_generator);
std::vector<double> GenerateNormalRandomNumbers(std::size_t n, std::mt19937 &random_generator);

double NormalCDF(double x);
double NormalINV(double x);

} // math_utils
