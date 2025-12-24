#include "backtester/portfolio/PortfolioHandler.hpp"

PortfolioHandler::PortfolioHandler(double initialCash) 
    : _cash(initialCash) {}

void PortfolioHandler::onExecution(const Execution& exec) {
    double cost = exec.price * exec.quantity;

    if (exec.side == Side::Buy) {
        _cash -= cost;
        _cash -= exec.fee; 
        _positions[exec.symbol] += exec.quantity;
    } 
    else if (exec.side == Side::Sell) {
        _cash += cost;
        _cash -= exec.fee;
        _positions[exec.symbol] -= exec.quantity;
    }
}

double PortfolioHandler::getCash() const {
    return _cash;
}

double PortfolioHandler::getPosition(const std::string& symbol) const {
    auto it = _positions.find(symbol);
    if (it != _positions.end()) {
        return it->second;
    }
    return 0.0;
}

double PortfolioHandler::getTotalValue(const std::map<std::string, double>& currentPrices) const {
    double total = _cash;

    for (const auto& [symbol, qty] : _positions) {
        if (currentPrices.count(symbol)) {
            total += qty * currentPrices.at(symbol);
        }
    }
    return total;
}