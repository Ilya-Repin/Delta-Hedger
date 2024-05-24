#pragma once

#include "Option.hpp"

namespace options {

class PutOption : public Option {
 public:
  PutOption(double strike, double maturity);

  double GetStrike() const {
    return strike_;
  }

  void SetStrike(double strike) {
    strike_ = strike;
  }

  double GetMaturity() const {
    return maturity_;
  }

  void SetMaturity(double maturity) {
    maturity_ = maturity;
  }

  double Payoff(double stockAtMaturity) const;
  double Price(const model::BlackScholesModel &bsm) const;
  double Delta(const model::BlackScholesModel &bsm) const;

 private:
  double maturity_;
  double strike_;
};
} // options
