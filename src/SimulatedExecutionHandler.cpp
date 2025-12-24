#include "backtester/SimulatedExecutionHandler.hpp"
#include <string>

SimulatedExecutionHandler::SimulatedExecutionHandler(double feeRate) 
    : _feeRate(feeRate) {}

std::optional<Execution> SimulatedExecutionHandler::onOrder(const Order& order, const Tick& marketTick) {    
    Execution exec;
    exec.timestamp = marketTick.timestamp; 
    exec.symbol = order.symbol;
    exec.side = order.side;
    exec.price = marketTick.price;
    exec.quantity = order.quantity;
    
    exec.fee = exec.price * exec.quantity * _feeRate;
    
    exec.orderId = "SIM_" + std::to_string(marketTick.timestamp);

    _executions.push_back(exec);

    return exec;
}

const std::vector<Execution>& SimulatedExecutionHandler::getExecutions() const {
    return _executions;
}