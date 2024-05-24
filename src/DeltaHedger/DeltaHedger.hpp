#pragma once

#include "BlackScholesModel/BlackScholesModel.hpp"
#include "Options/CallOption.hpp"
#include "Options/PutOption.hpp"

#include <vector>
#include <memory>
#include <cmath>

namespace hedger {

class DeltaHedger {
 public:
  DeltaHedger(std::vector<std::shared_ptr<options::Option>> &portfolio,
              std::shared_ptr<model::BlackScholesModel> model,
              std::size_t amount_steps);

  double Hedge();

  void SetToHedge(std::vector<std::shared_ptr<options::Option>> &options) {
    portfolio_options_ = options;
  }

  void SetBlackScholesModel(std::shared_ptr<model::BlackScholesModel> model) {
    black_scholes_model_ = std::move(model);
  }

  void SetAmountSteps(std::size_t amount_steps) {
    steps_amount_ = amount_steps;
  }

 private:
  double CalculateCharge(double stock_price, std::shared_ptr<options::Option> option) const;

  double SelectStockQuantity(double date, double stock_price, std::shared_ptr<options::Option> option) const;

  std::vector<std::shared_ptr<options::Option>> portfolio_options_;

  std::shared_ptr<model::BlackScholesModel> black_scholes_model_;

  std::size_t steps_amount_;
};
} // hedger
