#include "DeltaHedger.hpp"

namespace hedger {

DeltaHedger::DeltaHedger(std::vector<std::shared_ptr<options::Option>> &portfolio,
                         std::shared_ptr<model::BlackScholesModel> model,
                         std::size_t amount_steps)
    : portfolio_options_(portfolio), black_scholes_model_(std::move(model)), steps_amount_(amount_steps) {

}

double DeltaHedger::Hedge() {
  double start = black_scholes_model_->GetDate();
  double T = start;

  for (const auto &option : portfolio_options_) {
    T = std::max(T, option->GetMaturity());
  }

  double S0 = black_scholes_model_->GetStockPrice();
  std::random_device rd;

  std::mt19937 random_generator(rd());

  std::vector<double> price_path = black_scholes_model_->GeneratePricePath(T, steps_amount_, random_generator);

  double dt = (T - start) / static_cast<double>(steps_amount_);

  double charge = 0.0;
  for (const auto &option : portfolio_options_) {
    charge += CalculateCharge(S0, option);
  }

  double stock_quantity = 0.0;
  for (const auto &option : portfolio_options_) {
    stock_quantity += SelectStockQuantity(start, S0, option);
  }

  double bank_balance = charge - stock_quantity * S0;

  for (std::size_t i = 0; i < steps_amount_ - 1; ++i) {
    double balance_with_interest = bank_balance * std::exp(black_scholes_model_->GetRiskFreeRate() * dt);

    double S = price_path[i];
    double date = start + dt * static_cast<double>(i + 1);

    double to_remove = 0;

    for (auto option = portfolio_options_.begin(); option != portfolio_options_.end();) {
      if (date - (*option)->GetMaturity() >= 0.0) {
        to_remove += (*option)->Payoff(S);

        option = portfolio_options_.erase(option);
      } else {
        ++option;
      }
    }

    double new_stock_quantity = 0.0;
    for (const auto &option : portfolio_options_) {
      new_stock_quantity += SelectStockQuantity(date, S, option);
    }

    double costs = (new_stock_quantity - stock_quantity) * S;

    bank_balance = balance_with_interest - costs - to_remove;
    stock_quantity = new_stock_quantity;
  }

  double balance_with_interest = bank_balance * std::exp(black_scholes_model_->GetRiskFreeRate() * dt);

  double S = price_path.at(steps_amount_ - 1);

  double stock_value = stock_quantity * S;
  double payout = 0.0;

  for (const auto &option : portfolio_options_) {
    payout += option->Payoff(S);
  }

  return balance_with_interest + stock_value - payout;
}

double DeltaHedger::CalculateCharge(double stock_price, std::shared_ptr<options::Option> option) const {
  black_scholes_model_->SetStockPrice(stock_price);

  return option->Price(*black_scholes_model_);
}

double DeltaHedger::SelectStockQuantity(double date, double stockPrice, std::shared_ptr<options::Option> option) const {
  black_scholes_model_->SetStockPrice(stockPrice);
  black_scholes_model_->SetDate(date);

  return option->Delta(*black_scholes_model_);
}
} // hedger
