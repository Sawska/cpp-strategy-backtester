#pragma once 
#include "Types.hpp"
#include <vector>
#include <optional>

class IExecutionHandler {
public:
    virtual ~IExecutionHandler() = default;

    virtual std::optional<Execution> onOrder(const Order& order,const Tick& marketTick) = 0;

    virtual const std::vector<Execution>& getExecutions() const = 0;
};