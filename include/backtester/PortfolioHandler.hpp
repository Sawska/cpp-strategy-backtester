#pragma once
#include "PortfolioInterface.hpp" 
#include <map>
#include <string>

class PortfolioHandler : public IPortfolioHandler {
public:
    explicit PortfolioHandler(double initialCash);

    void onExecution(const Execution& exec) override;
    double getCash() const override;
    double getPosition(const std::string& symbol) const override;
    double getTotalValue(const std::map<std::string, double>& currentPrices) const override;

private:
    double _cash;
    std::map<std::string, double> _positions;
};