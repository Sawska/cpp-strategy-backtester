#pragma once
#include "backtester/core/Types.hpp"
#include <string>

class IStrategy {
public:
    virtual ~IStrategy() = default;

    virtual Side onTick(const Tick& tick) = 0;

    virtual std::string getName() const = 0;
};