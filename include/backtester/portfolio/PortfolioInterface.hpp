#pragma once
#include "backtester/core/Types.hpp"
#include <map>
#include <string>

class IPortfolioHandler {
public:
    virtual ~IPortfolioHandler() = default;

    virtual void onExecution(const Execution& exec) = 0;

    virtual double getCash() const = 0;

    virtual double getPosition(const std::string& symbol) const = 0;

    virtual double getTotalValue(const std::map<std::string, double>& currentPrices) const = 0;
};