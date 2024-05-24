#include "CallOption.hpp"

namespace options {

CallOption::CallOption(double strike, double maturity) : strike_(strike), maturity_(maturity) {
}

double CallOption::Payoff(double stockAtMaturity) const {
  if (stockAtMaturity > GetStrike()) {
    return stockAtMaturity - GetStrike();
  } else {
    return 0.0;
  }
}

double CallOption::Price(const model::BlackScholesModel &bsm) const {
  double S = bsm.GetStockPrice();
  double K = GetStrike();
  double sigma = bsm.GetVolatility();
  double r = bsm.GetRiskFreeRate();
  double T = GetMaturity() - bsm.GetDate();

  double numerator = std::log(S / K) + (r + sigma * sigma * 0.5) * T;
  double denominator = sigma * std::sqrt(T);

  double d1 = numerator / denominator;
  double d2 = d1 - denominator;

  return S * math_utils::NormalCDF(d1) - K * std::exp(-r * T) * math_utils::NormalCDF(d2);
}

double CallOption::Delta(const model::BlackScholesModel &bsm) const {
  double S = bsm.GetStockPrice();
  double K = GetStrike();
  double sigma = bsm.GetVolatility();
  double r = bsm.GetRiskFreeRate();
  double T = GetMaturity() - bsm.GetDate();

  double numerator = std::log(S / K) + (r + sigma * sigma * 0.5) * T;
  double denominator = sigma * std::sqrt(T);

  double d1 = numerator / denominator;

  return math_utils::NormalCDF(d1);
}
} // options
