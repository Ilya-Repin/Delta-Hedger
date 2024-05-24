#include "MathUtils.hpp"

namespace {
  constexpr double a0 = 2.50662823884;
  constexpr double a1 = -18.61500062529;
  constexpr double a2 = 41.39119773534;
  constexpr double a3 = -25.44106049637;
  constexpr double b1 = -8.47351093090;
  constexpr double b2 = 23.08336743743;
  constexpr double b3 = -21.06224101826;
  constexpr double b4 = 3.13082909833;
  constexpr double c0 = 0.3374754822726147;
  constexpr double c1 = 0.9761690190917186;
  constexpr double c2 = 0.1607979714918209;
  constexpr double c3 = 0.0276438810333863;
  constexpr double c4 = 0.0038405729373609;
  constexpr double c5 = 0.0003951896511919;
  constexpr double c6 = 0.0000321767881768;
  constexpr double c7 = 0.0000002888167364;
  constexpr double c8 = 0.0000003960315187;

}

namespace math_utils {

std::vector<double> GenerateUniformRandomNumbers(std::size_t n, std::mt19937 &random_generator) {
  std::vector<double> randoms;
  randoms.reserve(n);

  for (std::size_t i = 0; i < n; ++i) {
    double num = (random_generator() + 0.5) / (random_generator.max() + 1.0);
    randoms.push_back(num);
  }

  return randoms;
}

std::vector<double> GenerateNormalRandomNumbers(std::size_t n, std::mt19937 &random_generator) {

  std::vector<double> numbers = GenerateUniformRandomNumbers(n, random_generator);

  for (std::size_t i = 0; i < n; ++i) {
    numbers[i] = NormalINV(numbers[i]);
  }

  return numbers;
}

double EvaluatePolynomialByHorner(std::initializer_list<double> coefficients, double x) {
  double result = 0;

  for (double coefficient : std::ranges::reverse_view(coefficients)) {
    result = coefficient + x * result;
  }

  return result;
}

double NormalCDF(double x) {
  const double ROOT_2_PI = std::sqrt(2.0 * std::numbers::pi);

  if (x < 0) {
    return 1 - NormalCDF(-x);
  }

  double k = 1 / (1 + 0.2316419 * x);
  double poly = EvaluatePolynomialByHorner({0.0, 0.319381530, -0.356563782, 1.781477937, -1.821255978, 1.330274429}, k);

  double approx = 1.0 - 1.0 / ROOT_2_PI * std::exp(-0.5 * x * x) * poly;

  return approx;
}

double NormalINV(double x) {
  double y = x - 0.5;

  if (y < 0.42 && y > -0.42) {
    double r = y * y;

    return y * EvaluatePolynomialByHorner({a0, a1, a2, a3}, r) / EvaluatePolynomialByHorner({1.0, b1, b2, b3, b4}, r);
  } else {
    double r = y < 0.0 ? x : 1.0 - x;

    double s = std::log(-std::log(r));
    double t = EvaluatePolynomialByHorner({c0, c1, c2, c3, c4, c5, c6, c7, c8}, s);

    return (x > 0.5 ? t : -t);
  }
}
} // math_utils
