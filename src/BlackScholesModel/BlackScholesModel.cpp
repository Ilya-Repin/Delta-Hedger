#include "BlackScholesModel.hpp"

namespace model {

BlackScholesModel::BlackScholesModel(double stock_price,
                                     double date,
                                     double risk_free_rate,
                                     double volatility,
                                     double drift) :
    stock_price_(stock_price),
    date_(date),
    risk_free_rate_(risk_free_rate),
    volatility_(volatility),
    drift_(drift) {
}

double BlackScholesModel::GetStockPrice() const {
  return stock_price_;
}

double BlackScholesModel::GetDate() const {
  return date_;
}

double BlackScholesModel::GetRiskFreeRate() const {
  return risk_free_rate_;
}

double BlackScholesModel::GetVolatility() const {
  return volatility_;
}

double BlackScholesModel::GetDrift() const {
  return drift_;
}

void BlackScholesModel::SetStockPrice(double price) {
  stock_price_ = price;
}

void BlackScholesModel::SetDate(double date) {
  date_ = date;
}

void BlackScholesModel::SetRiskFreeRate(double risk_free_rate) {
  risk_free_rate_ = risk_free_rate;
}

void BlackScholesModel::SetVolatility(double volatility) {
  volatility_ = volatility;
}

void BlackScholesModel::SetDrift(double drift) {
  drift_ = drift;
}

std::vector<double> BlackScholesModel::GeneratePricePath(double to_date,
                                                         std::size_t steps_amount,
                                                         std::mt19937 &random_generator) const {
  std::vector<double> path(steps_amount, 0.0);

  std::vector<double> epsilon = math_utils::GenerateNormalRandomNumbers(steps_amount, random_generator);

  double dt = (to_date - date_) / static_cast<double>(steps_amount);

  double a = (drift_ - volatility_ * volatility_ * 0.5) * dt;
  double b = volatility_ * std::sqrt(dt);

  double current_log_s = std::log(stock_price_);

  for (int i = 0; i < steps_amount; i++) {
    double d_log_s = a + b * epsilon[i];
    double log_s = current_log_s + d_log_s;

    path[i] = std::exp(log_s);
    current_log_s = log_s;
  }

  return path;
}
} // model
