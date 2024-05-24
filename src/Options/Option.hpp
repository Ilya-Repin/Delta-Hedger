#pragma once

#include "BlackScholesModel/BlackScholesModel.hpp"
#include "MathUtils/MathUtils.hpp"

namespace options {

class Option {
 public:
  virtual ~Option() = default;

  virtual double GetMaturity() const = 0;
  virtual void SetMaturity(double maturity) = 0;

  virtual double GetStrike() const = 0;
  virtual void SetStrike(double strike) = 0;

  virtual double Payoff(double stockAtMaturity) const = 0;
  virtual double Price(const model::BlackScholesModel &bsm) const = 0;
  virtual double Delta(const model::BlackScholesModel &bsm) const = 0;
};
} // options
