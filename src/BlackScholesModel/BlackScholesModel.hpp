#pragma once

#include "MathUtils/MathUtils.hpp"

#include "vector"

namespace model {

class BlackScholesModel {
 public:
  BlackScholesModel(double stock_price,
                    double date,
                    double risk_free_rate,
                    double volatility,
                    double drift);

  ~BlackScholesModel() = default;

  double GetStockPrice() const;
  double GetDate() const;
  double GetRiskFreeRate() const;
  double GetVolatility() const;
  double GetDrift() const;

  void SetStockPrice(double price);
  void SetDate(double date);
  void SetRiskFreeRate(double risk_free_rate);
  void SetVolatility(double volatility);
  void SetDrift(double drift);

  std::vector<double> GeneratePricePath(double to_date, std::size_t steps_amount, std::mt19937 &random_generator) const;

 private:
  double stock_price_;
  double date_;
  double risk_free_rate_;
  double volatility_;
  double drift_;
};
} // model
