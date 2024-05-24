#include "src/DeltaHedger/DeltaHedger.hpp"

#include <iostream>

int main() {

  double stock_price, date, risk_free_rate, volatility, drift;

  std::cout << "Enter stock price: " << std::endl;
  std::cin >> stock_price;
  std::cout << "Enter date: " << std::endl;
  std::cin >> date;
  std::cout << "Enter risk free rate: " << std::endl;
  std::cin >> risk_free_rate;
  std::cout << "Enter volatility: " << std::endl;
  std::cin >> volatility;
  std::cout << "Enter drift: " << std::endl;
  std::cin >> drift;

  auto model = std::make_shared<model::BlackScholesModel>(stock_price,
                                                          date,
                                                          risk_free_rate,
                                                          volatility, drift);

  int options_amount = 0;

  std::cout << "Enter size of portfolio: " << std::endl;
  std::cin >> options_amount;

  std::vector<std::shared_ptr<options::Option>> portfolio;
  portfolio.reserve(options_amount);

  int i = 0;

  while (i < options_amount) {
    std::cout << "Enter option type: " << std::endl;
    std::string type;
    std::cin >> type;

    if (type == "CALL") {
      double strike, maturity;

      std::cout << "Enter strike: " << std::endl;
      std::cin >> strike;
      std::cout << "Enter maturity: " << std::endl;
      std::cin >> maturity;

      portfolio.push_back(std::make_shared<options::CallOption>(strike, maturity));
      std::cout << "Option added!" << std::endl;
      ++i;
    } else if (type == "PUT") {
      double strike, maturity;

      std::cout << "Enter strike: " << std::endl;
      std::cin >> strike;
      std::cout << "Enter maturity: " << std::endl;
      std::cin >> maturity;

      portfolio.push_back(std::make_shared<options::PutOption>(strike, maturity));
      std::cout << "Option added!" << std::endl;
      ++i;
    } else {
      std::cout << "Unknown type of option!" << std::endl;
    }
  }

  int steps = 0;

  std::cout << "Enter amount of steps: " << std::endl;
  std::cin >> steps;

  hedger::DeltaHedger hedger(portfolio, model, steps);

  std::cout << "Simulation started..." << std::endl;

  double result = hedger.Hedge();

  std::cout << "Result = " << result << std::endl;

  return 0;
}
