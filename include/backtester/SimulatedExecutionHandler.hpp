#pragma once
#include "ExecutionHandler.hpp"

class SimulatedExecutionHandler : public IExecutionHandler {
public:
    explicit SimulatedExecutionHandler(double feeRate = 0.0);

    std::optional<Execution> onOrder(const Order& order, const Tick& marketTick) override;
    
    const std::vector<Execution>& getExecutions() const override;

private:
    double _feeRate;
    std::vector<Execution> _executions;
};