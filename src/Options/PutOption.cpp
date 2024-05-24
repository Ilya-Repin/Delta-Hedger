#include "PutOption.hpp"

namespace options {

PutOption::PutOption(double strike, double maturity) : strike_(strike), maturity_(maturity) {
}

double PutOption::Payoff(double stockAtMaturity) const {
  if (stockAtMaturity < GetStrike()) {
    return GetStrike() - stockAtMaturity;
  } else {
    return 0.0;
  }
}

double PutOption::Price(const model::BlackScholesModel &bsm) const {
  double S = bsm.GetStockPrice();
  double K = strike_;
  double sigma = bsm.GetVolatility();
  double r = bsm.GetRiskFreeRate();
  double T = maturity_ - bsm.GetDate();

  double numerator = std::log(S / K) + (r + sigma * sigma * 0.5) * T;
  double denominator = sigma * std::sqrt(T);

  double d1 = numerator / denominator;
  double d2 = d1 - denominator;

  return K * std::exp(-r * T) * math_utils::NormalCDF(-d2) - S * math_utils::NormalCDF(-d1);
}

double PutOption::Delta(const model::BlackScholesModel &bsm) const {
  double S = bsm.GetStockPrice();
  double K = strike_;
  double sigma = bsm.GetVolatility();
  double r = bsm.GetRiskFreeRate();
  double T = maturity_ - bsm.GetDate();

  double numerator = std::log(S / K) + (r + sigma * sigma * 0.5) * T;
  double denominator = sigma * std::sqrt(T);

  double d1 = numerator / denominator;

  return -(math_utils::NormalCDF(-d1));
}
} // options
